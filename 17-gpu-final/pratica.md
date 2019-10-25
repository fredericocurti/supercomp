% 16 - Atividade prática
% SuperComputação - 2019/2
% Igor Montagner, Luciano Soares

Nas últimas aulas trabalhamos com GPU usando a biblioteca `thrust` e também kernels feitos diretamente em *CUDA*. Iremos finalizar este módulo com exercícios práticos de implementação. Nesta aula você deverá seguir duas instruções básicas

### iniciar os exercícios a partir de um arquivo vazio

e 

### não copiar e colar código 

É claro que você pode consultar código que já escreveu, mas a ideia é evitar montar um programa Frankstein copiando pedaços de código que nem sempre se conectam da maneira correta. Queremos tentar compreender por completo cada linha de seu código e saber exatamente a razão dela estar onde está. 

Iremos voltar a um exercício que fizemos nas aulas de multi-core: o cálculo do PI usando as técnicas de integração numérica e Monte Carlo. 

## Parte 1 - Integração numérica

Na aula *07-threads-I* paralelizamos um código que fazia o cálculo do *PI* usando *OpenMP*. Neste primeiro exercício iremos converter aquele código para rodar em GPU. Você deverá

1. portar o código em `pi-numeric-integration.cpp` para GPU
1. comparar o tempo gasto para `num_steps = 1000000000`. 
1. comparar com sua implementação usando *OpenMP*

## Parte 2 - Monte Carlo

Na aula *10-reentrancia* paralelizamos um código que usava sorteios aleatórios para calcular o *PI*. Neste exercício você deverá

1. converter `pi_mc.c` para rodar em GPU
1. comparar o tempo gasto para `num_trials = 1000000000` para o sequencial
1. fazer o mesmo para sua versão usando OpenMP

A geração de números aleatórios dentro de um kernel pode ser feita com a biblioteca [cuRAND](https://docs.nvidia.com/cuda/curand/introduction.html#introduction). Um exemplo simples de uso pode ser visto no arquivo *rand.cu* disponibilizado no repositório. 
