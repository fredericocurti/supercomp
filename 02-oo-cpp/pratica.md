% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Introdução a C++ II

Neste roteiro iremos usar os conceitos da aula expositiva para 
incrementar o experimento de medição de tempo da aula passada. 
Cada exercício criará uma parte de uma classe `Experimento` que 
guardará as entradas do programa da última aula e seus respectivos 
tempos de execução. 

Ao fim deste roteiro seu programa da última aula terá sido totalmente transformado
em um programa orientado a objetos contendo vários arquivos de código fonte. 

## Orientação a objetos em *C++*

A criação de classes em *C++* é normalmente divida em um arquivo cabeçalho *.hpp* contendo a definição da classe e um arquivo 
*.cpp* contendo a implementação dos métodos declarados no arquivo de cabeçalho. Para usarmos nossa classe em outros arquivos basta incluir o cabeçalho usando o comando `#include`. Veja os exemplos abaixo. 

```cpp
// arquivo exemplo.hpp

#ifndef EXEMPLO_H
#define EXEMPLO_H

class ExemploRect {
    // variáveis declaradas aqui são privadas por padrão
    ;
    public:
        ExemploRect(int, int);
        // variáveis declaradas aqui são públicas
        double w, h;
        double area();
};

#endif
```
\newpage
```cpp
// arquivo exemplo.cpp

#include "exemplo.hpp"
#include <iostream>

// A função abaixo é chamada ao criar um objeto ExemploRect
ExemploRect::ExemploRect(int w, int h) : w(w), h(h) {
    std::cout << "Objeto Exemplo Rect criado!\n";
}

double ExemploRect::area() {
    return w * h; // atributos podem ser acessados diretamente.
}
```

Com isto feito, podemos usar nossa classe da seguinte maneira:

```cpp
#include "exemplo.hpp"

//dentro do main
ExemploRect e(10, 20);
std::cout << e.area() << "\n";

```

A compilação agora deverá levar em conta que nosso programa está espalhado em vários arquivos. A maneira mais simples de fazê-lo é simplesmente incluir todos os arquivos na mesma execução do `g++`:

    > $ g++ main.cpp exemplo.cpp -o main

Isto não é uma boa prática, mas servirá para esta aula. (Re)Veremos boas práticas de compilação na próxima aula. 

### Exercício:

Crie uma classe `Experimento` contendo

* um método `gera_entrada`, que gera um array de tamanho *n*.
* um método `duration`, que retorna o tempo que o experimento levou para rodar. 

Sua classe deverá conter os seguintes atributos públicos:

* array de tamanho *n* alocado dinâmicamente com `new`
* inteiro *n*
* duração do experimento em segundos (tipo `double`).

### Exercício

Adapte sua função `main` para guardar os dados de cada execução em uma instância da classe
`Experimento`.

----

Nossa classe `Experimento` por enquanto só gera as entradas e guarda tempos de execução. Como
temos quatro funções diferentes para rodar, precisamos permitir que isto seja customizado. Esta customização
será feita definindo subclasses de `Experimento` (uma para cada função da aula passada). 

### Exercício:

Crie uma função `virtual` chamada `experiment_code` que não recebe nenhum argumento. Esta função
conterá o código a ser rodado em cada experimento. 

### Exercício:

Crie uma função `void run()` que usa as medições de tempo da aula passada para medir 
quanto tempo `experiment_code` demora para rodar. 

### Exercício:

Crie uma subclasse para cada função a ser testada e implemente a função `experiment_code`. Cada classe
deverá ser implementada em seu próprio para de arquivos *.hpp/.cpp*. Não se esqueça de adaptar seu script de compilação 
para levar isto em conta. 

### Exercício:

Adapte sua função `main` para usar as subclasses de experimento e o método `run()`. Como exercício, só use variáveis do tipo `Experimento` para guardar instâncias das subclasses criadas. 

## Operator overloading

Nossa classe experimento permite a execução dos códigos do experimentos, mas em alguns pontos ainda não é muito prático trabalhar com ela. Vamos sobrescrever alguns operadores para que seja possível comparar instâncias de `Experimento` entre si e com números fracionários. 

### Exercício:

Sobrescreva o operador `double()` para retornar a duração do experimento. 


### Exercício:

Sobrescreva o operador `<` para que sejam possíveis comparações entre duas instâncias de `Experimento` e entre um `Experimento` e um `double`. Consideramos um `Experimento` menor que outro se sua duração é menor **E** se o tamanho de sua entrada é o mesmo. 

### Exercício:

Use as operações acima no seu `main` para listar todos os experimentos que durem menos de *0.1* segundo. 

### Exercício:

Para cada tamanho de vetor rode 10 `Experimento` e modifique seu programa para mostrar o menor e o maior tempo.

## Exemplo de output final no arquivo out.txt

