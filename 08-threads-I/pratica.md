% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Multi-core I: o modelo *fork-join*

Como visto em aula, o modelo *fork-join* segue três passos básicos:

1. Dividir o problema em pedaços
2. Resolver cada pedaço individualmente
3. Juntar as respostas parciais em um resultado final

Vamos criar uma implementação raiz desse modelo usando threads em C++11. 

## Parte 1 - o cabeçalho `thread`

Nesta parte iremos aprender a criar threads e esperar sua finalização usando C++11 `std::threads`. Veja abaixo um exemplo com as funções que precisaremos usar (arquivo *exemplo1-threads.cpp*).

```cpp
#include <thread>
#include <iostream>

void funcao_rodando_em_paralelo(int a, int *b) {
    std::cout << "a=" << a << std::endl;
    *b = 5;
}


int main() {
    int b = 10;

    // Cria thread e a executa.
    // Primeiro argumento é a função a ser executada.
    
    // Os argumentos em seguida são passados diretamente
    // para a função passada no primeiro argumento.
    std::thread t1(funcao_rodando_em_paralelo, 15, &b);
    
    
    std::cout << "Antes do join b=" << b << std::endl;
    
    // Espera até que a função acabe de executar.
    t1.join();
    
    std::cout << "Depois do join b=" << b << std::endl;
}
```

### Exercício

Compile e roda o programa acima. O resultado é o esperado?
- O resultado numérico é o esperado porém existe uma mistura da saída padrão entre a thread 0 com a thread 1

### Exercício

Modifique o programa acima para criar 4 threads e atribuir a cada uma um *id* de 0 a 3. Cada thread deve executar uma função que imprime "Thread: " + id. 

- Feito, porém a saída continua misturada - precisa de um semáforo

### Exercício

Pesquise como detectar o máximo de threads de hardware e incorpore esta informação no seu programa acima. Ele deverá criar este número de threads.
- Done com array de threads e `std::thread::hardware_concurrency();`

### Exercício

Modifique seu programa acima para retornar um o *id* da thread ao quadrado. Como você faria isto? Como você guardaria essa informação no `main`?
- Passaria um ponteiro para uma array de resultados, e cada thread colocaria nessa array em seu índice correspondente o resultado computado por ela.

### Exercício

Faça sua função `main` mostrar a soma dos quadrados dos valores recebidos no item anterior. 

## Parte 2 - exercício para entrega. 

A segunda atividade também será dividida em pequenos exercícios de acompanhamento. Este primeiro exercício envolverá criar uma implementação paralela do cálculo do *pi*. O arquivo *pi-numeric-integration.cpp* contém uma implementação sequencial usando a técnica de integração numérica vista nos slides. Seu trabalho será:

1. dividir o trabalho desta função em 4 threads, cada uma computando uma parte da sequência
1. salvar os resultados parciais de cada thread em um elemento de um vetor criado no `main`
1. somar os resultados parciais.

Seu programa deverá apresentar resultado similar ao programa sequencial, mas funcionar em aproximadamente um quarto do tempo. Coloque o resultado deste exercício, mais um arquivo *CMakeLists.txt* em um repositório no Github e envie-o no blackboard até **30/09**.