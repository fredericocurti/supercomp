% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Multi-core IV: Tarefas em OpenMP

O uso de tarefas (tasks) para paralelizar códigos apresenta bons resultados em diversas aplicações que não se encaixam exatamente no modelo *fork-join*. Nessa aula exploraremos o uso de tarefas para paralelizar a execução de funções recursivas. 

## Exemplo simples

Escreva um programa usando tarefas (tasks) que irá aleatoriamente gerar uma das duas cadeias de caracteres:

    I think race cars are fun 
    I think car races are fun

Dica: use tarefas para imprimir a parte indeterminada da saída (ou seja, as palavras "race" ou "cars").

Isso é chamado de "Condição da corrida". Ocorre quando o resultado de um programa depende de como o sistema operacional escalona as threads.


Você pode usar:

```cpp
#pragma omp parallel
#pragma omp task
#pragma omp master
#pragma omp single
```

# Uma primeira função recursiva

O código abaixo calcula a [sequência de Fibonacci](https://pt.wikipedia.org/wiki/Sequ%C3%AAncia_de_Fibonacci) usando um algoritmo recursivo. 

```cpp
#include <iostream>

int fib(int n) {
    int x,y;
    if(n<2) return n;
    x=fib(n-1);
    y=fib(n-2);
    return(x+y);
}

int main() {
    int NW=45;
    int f=fib(NW);
    std::cout << f << std::endl;
}
```

### Exercício

Transforme este código em paralelo usando `omp tasks`. Sua nova função deverá se chamar `int fib_par1(int n);` **Dica**: faça com que cada chamada recursiva seja executada como uma tarefa. 

Você pode usar:

```cpp
#pragma omp parallel
#pragma omp task
#pragma omp taskwait
#pragma omp master
```

### Exercício

Compare com o código original. Houve melhora? Por que?

### Exercício

Melhore sua versão paralela para que sejam criadas no máximo `max_threads` tarefas. Como você pode fazer isto? Há melhora de desempenho? Salve sua função com o nome `int fib_par2(int n)`. 

# Cálculo do pi recursivo

A etapa final de nossa aula trabalhará o algoritmo de cálculo do *pi* usando integração numerica novamente, mas agora escrito de maneira recursiva. 

### Exercício

Abra o arquivo *pi_recursivo.cpp* e examine seu conteúdo. Quantos níveis de recursão são feitos? Em outras palavras, quantas chamadas são necessárias até que o `for` seja executado sequencialmente? **Dica**: veja a relação entre `MIN_BLK` e `num_steps`.

### Exercício

A paralelização de código é sempre muito mais fácil quando eliminamos todos os efeitos colaterais. Elimine todas as variáveis globais do código. Crie também uma função `double pi_par_tasks(long num_steps)` que chama a função `double pi_r` com os valores iniciais corretos. 

### Exercício

Agora use `omp task` para paralelizar as chamadas recursivas. 

### Exercício 

Varie o valor de `MIN_BLK` e meça o desempenho do programa. Escreva, junto desse valor, quantas tarefas foram criadas e quantos processadores estiveram ativos durante a execução do programa. 

### Extra

Nosso programa limita o paralelismo via `MIN_BLK`. Como você faria para ele aproveitar ao máximo o número de processadores disponíveis em tempo de execução?
