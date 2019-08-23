% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Introdução a SIMD

__Objetivos de aprendizado__:

* Conhecer principais pontos da supercomputação
* Programar para arquiteturas vetoriais
* Habilitar auto vetorização e conhecer suas limitações

### Tarefa 1 - Instruções SIMD em Assembly

Nesta primeira tarefa iremos compilar alguns códigos em C++ para Assembly usando 
as opções `-ffast-math -ftree-vectorize -mavx` do `gcc`. Estas opções habilitam a *autovetorização*
de código. Ou sejam elas analisam o código e procuram substituir loops e acessos sequenciais
a vetores por instruções SIMD que façam o mesmo trabalho.

A flag `-mavx` indica que o código de máquina gerado pode utilizar instruções
SIMD da arquitetura *AVX* (e de sua predecessora, SSE), que usa registradores de 128 bits nomeados `%xmm0` 
até `%xmm7` e de 256 bits nomeados `%ymm0` até `%ymm15`. Ou seja, posso armazenar, em um registrador
`%xmm0`

* 16 chars;
* 8 shorts;
* 4 ints;
* 2 longs;
* 4 floats;
* 2 doubles;

Para registradores `%ymm` é só dobrar os valores acima. 

Toda instrução SIMD opera sobre todos os elementos guardados ao mesmo tempo. Ou seja, ao executar uma instrução SIMD de soma de variáveis `int` no registrador `%xmm0` estarei somando **8** variáveis em uma só instrução.

Vamos agora analisar o código Assembly de uma função simples que soma todos
elementos de um vetor. 

\pagebreak

<div class="include code" id="src/tarefa1.cpp" language="cpp"></div>

Primeiro, compile este código para Assembly sem SIMD.

>$ g++ -S -c -O2  tarefa1.cpp -o /dev/stdout | c++filt

Agora, compile o mesmo programa habilitando a autovetorização.

>$ g++ -S -c -O2 -ftree-vectorize -mavx tarefa1.cpp -o /dev/stdout | c++filt

**Discussão 1**: Você consegue identificar onde os códigos diferem? 

R: O segundo código com as flags de autovetorização usam instruções diferentes para as operações de soma (vpaddd ao invés de paddd)

### Tarefa 2 - Autovetorização em loops

Nesta tarefa iremos trabalhar com as opções de autovetorização do `gcc`
para entender como escrever código que possa ser otimizado automaticamente. 

##### Exercício 1

Escreva uma função `main` que gera um vetor de tamanho `10.000.000` contendo números aleatórios uniformemente distribuídos entre `-10` e `10`. Use as funções do cabeçalho `<random>`. 

##### Exercício 2

Escreva uma função `double soma_positivos1(double *a, int n)` que soma todos os números positivos do vetor `a`. Adicione uma chamada a esta função no seu `main` e use as funções do cabeçalho `<chrono>` para medir o tempo de execução da sua função. Neste exercício você deverá usar um `if` para checar se os números são positivos. 

Compile com e sem as otimizações SIMD e verifique se há diferença no tempo de execução.

R: 
- sem SIMD: `[soma_positivos1] sum: 2.61912e+07 T: 44.2223 ms`
- com SIMD: `[soma_positivos1] sum: 2.61912e+07 T: 48.1829 ms`

----------

#### Exercício 3

O auto vetorizador suporta uma série de padrões de codificação relativamente abrangente ([lista completa](https://gcc.gnu.org/projects/tree-ssa/vectorization.html)). Porém, códigos que são vetorizados de maneira idêntica possuem desempenho bastante diferente quanto a vetorização não está habilitada. Faça uma função `double soma_positivos2(double *a, int n)` que faz o mesmo que a função anterior, mas usando agora o operador ternário `(cond)?expr_true:expr_false` ao invés de um `if`. (Se você fez com o operador ternário acima faça com `if`). Houve diferença de desempenho na versão SIMD? E na versão sem SIMD?

- sem SIMD: 

`[soma_positivos1] sum: 2.61912e+07 T: 48.1829 ms`

`[soma_positivos2] sum: 2.61912e+07 T: 48.5576 ms`

- com SIMD:

`[soma_positivos1] sum: 2.61912e+07 T: 6.98338 ms`

`[soma_positivos2] sum: 2.61912e+07 T: 5.4224 ms`

##### Exercício 4

Qual versão da função anterior você usaria se seu código fosse executado em processadores de baixo custo (Intel Celeron) ou muito antigos (mais de 5 anos)? E se o plano for executar em processadores novos? 

- Eu usaria a versão 2 em ambos os processadores, pois aparentemente só de usar o operador ternário foi possível melhor um pouco o desempenho.

\pagebreak

### Tarefa 3 - 	Avaliação de desempenho e opções de compilação

Nas últimas duas tarefas vimos como usar as opções do compilador para gerar instruções SIMD, 
tornando nossos programas mais eficientes. Agora vamos aplicá-las ao nosso exemplo dos experimentos. Você deverá

1. criar 5 executáveis diferentes a partir do seu *main.cpp*
    * `O0` até `O3` - sem otimizações
    * `O3` + flags SIMD
1. criar um jupyter notebook que rode os 5 executáveis e leia os tempos de execução
1. plotar um gráfico para cada experimento contendo os tempos das 5 versões testadas para cada tipo de função rodada. 

Com os resultados do seu gráfico em mãos você deverá responder as seguintes perguntas:

1. A partir de qual tamanho de array o código vetorizado mostra ganhos de desempenho expressivos?
1. Qual é o ganho de desempenho esperado? Leve em conta a arquitetura usada e o tipo de dados usado.
2. Os ganhos de desempenho são consistentes com o esperado?
3. Quais tipos de operações resultam em maior ganho de desempenho?
