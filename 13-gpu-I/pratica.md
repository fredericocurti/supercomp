% 12 - Introdução a GPGPU
% SuperComp 2019/2
% Igor Montagner, Luciano Soares

Os objetivos desta primeira aula de GPGPU são 

1. Compilar programas para GPU
1. Alocar dados na GPU e transferir dados CPU$\leftrightarrow$GPU
1. Acelerar computações simples baseado no modelo *map-reduce*.

Como visto em aula, programação para GPU requer ferramentas especializadas capazes de gerar código que rode parte na CPU (chamada de *host*) e parte na GPU (chamada de *target*). Nesta parte introdutória usaremos a biblioteca `cuda::thrust`. Ela possui um pequeno conjunto de operações otimizadas para GPU e que podem ser customizadas para diversos propósitos. 

Também vamos focar em usar máquinas pré-configuradas (AWS ou o Monstrão, quando ficar pronto). Instruções de instalação local estão disponíveis no *Anexo 1* deste roteiro.

# Parte 0 - compilação

Neste roteiro iremos calcular algumas estatísticas simples usando séries temporais de preços de ações disponíveis nos arquivos `stocks-google.txt` e `stocks2.csv`.  


# Parte 0 - instalação e compilação usando `nvcc` 

Para compilar programas para rodar na GPU devemos usar o compilador `nvcc`. Ele identifica quais porções do código deverão ser compiladas para a GPU. O restante do código, que roda exclusivamente na CPU, é passado diretamente para um compilador *C++* regular e um único executável é gerado contendo o código para CPU e chamadas inseridas pelo `nvcc` para invocar as funções que rodam na GPU. 

**Exercício**: verifique que sua instalação funciona compilando o arquivo abaixo.

    >$ nvcc -std=c++11 exemplo1-criacao-iteracao.cu -o exemplo1 

Se der tudo certo a execução do programa acima deverá gerar um executável `exemplo1` que roda e produz o seguinte resultado.

```
Host vector: 0 0 12 0 35
Device vector 0 0 0 0 35
```

# Parte 1 - transferência de dados 

Como visto na expositiva, a CPU e a GPU possuem espaços de endereçamento completamente distintos. Ou seja, a CPU não consegue acessar os dados na memória da GPU e vice-versa. A `thrust` disponibiliza somente um tipo de container (`vector`) e facilita este gerenciamento deixando explícito se ele está alocado na CPU (`host`) ou na GPU (`device`).  A cópia CPU$\leftrightarrow$ GPU é feita implicitamente quando criamos um `device_vector` ou quando usamos a operação de atribuição entre `host_vector` e `device_vector`. Veja o exemplo abaixo:

~~~{.cpp}
thrust::host_vector<double> vec_cpu(10); // alocado na CPU

vec1[0] = 20;
vec2[1] = 30;

// aloca vetor na GPU e transfere dados CPU->GPU
thrust::device_vector<double> vec_gpu (vec_cpu); 

//processa vec_gpu

vec_cpu = vec_gpu; // copia dados GPU -> CPU
~~~

A `thrust` usa iteradores em todas as suas funções. Pense em um iterador como um ponteiro para os elementos do array. Porém, um iterador é mais esperto: ele guarda também o tipo do vetor original e suporta operações `++` e `*` para qualquer tipo de dado iterado de maneira transparente. 

Vetores `thrust` aceitam os métodos `v.begin()` para retornar um iterador para o começo do vetor e `v.end()` para um iterador para o fim. Podemos também somar um valor `n` a um iterador. Isto é equivalente a fazer `n` vezes a operação `++`.  Veja abaixo um exemplo de uso das funções `fill` e `sequence` para preencher valores em um vetor de maneira eficiente. 

~~~{.cpp}
thrust::device_vector<int> v(5, 0); // vetor de 5 ints zerado
// v = {0, 0, 0, 0, 0}
thrust::sequence(v.begin(), v.end()); // preenche com 0, 1, 2, ....
// v = {0, 1, 2, 3, 4}
thrust::fill(v.begin(), v.begin()+2, 13); // dois primeiros elementos = 13
// v = {13, 13, 2, 3, 4} 
~~~

Consulte o arquivo *exemplo1-criacao-iteracao.cu* para um exemplo completo de alocação e transferência de dados e do uso de iteradores. 

## Exercício

O fluxo de trabalho "normal" de aplicações usando GPU é receber os dados em um vetor na CPU e copiá-los para a GPU para fazer processamentos. Crie um programa que lê uma sequência de `double`s da entrada padrão em um `thrust::host_vector` e os copia para um `thrust::device_vector`. Teste seu programa com o arquivo *stocks-google.txt*, que contém o preço das ações do Google nos últimos 10 anos. 

## Exercício

A criação de um `device_vector` é demorada. Meça o tempo que a operação de alocação e cópia demora e imprima na saída de erros. (Use `std::chrono`). 

----

Por enquanto nosso programa acima não faz nada. Na próxima seção veremos como fazer 


# Parte 2 - reduções

Uma operação genérica de *redução* transforma um vetor em um único valor. Exemplos clássicos de operações de redução incluem *soma*, *média* e *mínimo/máximo* de um vetor. 

A `thrust` disponibiliza este tipo de operação otimizada em *GPU* usando a função `thrust::reduce`:

~~~{.cpp}
val = thrust::reduce(iter_comeco, iter_fim, inicial, op);
// iter_comeco: iterador para o começo dos dados
// iter_fim: iterador para o fim dos dados
// inicial: valor inicial
// op: operação a ser feita. 
~~~

Um exemplo de uso de redução para computar o máximo pode ser visto [aqui](http://thrust.github.io/doc/group__reductions_ga5e9cef4919927834bec50fc4829f6e6b.html#ga5e9cef4919927834bec50fc4829f6e6b). A lista completa de funções que podem ser usadas no lugar de `op` pode ser vista [neste link](http://thrust.github.io/doc/group__predefined__function__objects.html). 


## Exercício

Continuando o exercício anterior, calcule as seguintes medidas. Não se esqueça de passar o `device_vector` para a sua função `reduce`

1. O preço médio das ações nos últimos 10 anos.
1. O preço médio das ações no último ano (365 dias atrás).
1. O maior e o menor preço da sequência inteira e do último ano. 

Você pode consultar todos os tipos de reduções disponíveis no [site da thrust](https://thrust.github.io/doc/group__reductions.html). 


## Exercício 
Todos os algoritmos da `thrust` podem ser rodados também em *OpenMP* passando como primeiro argumento `thrust::host`. Modifique o seu exercício acima para fazer as mesmas chamadas porém usando *OpenMP* e meça o tempo das duas implementações. Separe o tempo de cópia para GPU e o de execução em sua análise.

## Exercício

Comente os resultado acima. Quando vale a pena paralelizar usando GPU? Compare o tempo de execução na CPU e na GPU e o tempo de cópia.

# Parte 3 - Transformações ponto a ponto

Além de operações de redução também podemos fazer operações ponto a ponto em somente um vetor (como negar todas as componentes ou calcular os quadrados) quanto entre dois vetores (como somar dois vetores componente por componente ou comparar cada elemento com seu correspondente em outro vetor). A `thrust` dá o nome de `transformation` para este tipo de operação. 

~~~{.cpp}
// para operações entre dois vetores iter1 e iter2. resultado armazenado em out
thrust::transform(iter1_comeco, iter1_fim, iter2_comeco, out_comeco, op);
// iter1_comeco: iterador para o começo de iter1
// iter1_fim: iterador para o fim de iter1
// iter2_comeco: iterador para o começo de iter2
// out_comeco: iterador para o começo de out
// op: operação a ser realizada.
~~~

Um exemplo concreto pode ser visto abaixo. O código completo está em `exemplo2-transform.cu`

~~~{.cpp}
thrust::device_vector<double> V1(10, 0);
thrust::device_vector<double> V2(10, 0);
thrust::device_vector<double> V3(10, 0);
thrust::device_vector<double> V4(10, 0);
// inicializa V1 e V2 aqui

//soma V1 e V2
thrust::transform(V1.begin(), V1.end(), V2.begin(), V3.begin(), thrust::plus<double>());

// multiplica V1 por 0.5
thrust::transform(V1.begin(), V1.end(), 
                  thrust::constant_iterator<double>(0.5), 
                  V4.begin(), thrust::multiplies<double>());
~~~

As operações que foram usadas no `reduce` também podem ser usadas em um `transform`. Não se esqueça de consultar [a lista de operações](http://thrust.github.io/doc/group__predefined__function__objects.html) para fazer este exercício.

## Exercício

Vamos agora trabalhar com o arquivo `stocks2.csv`. Ele contém a série histórica de ações da Apple e da Microsoft. Seu objetivo é calcular a diferença média entre os preços das ações AAPL e MSFT.

**Dica**: quebre o problema em duas partes. Primeiro calcule a diferença entre os preços e guarde isto em um vetor. Depois compute a média deste vetor. 

## Exercício extra

Cada chamada a `reduce` e `transform` tem um custo fixo que pode se acumular caso façamos muitas chamadas. Estude como escrever seu programa usando `transform_reduce`. 

# Anexo 1 - instalação local

**Instruções fáceis**: os repositórios oficiais do *Ubuntu* já contém o pacote `nvidia-cuda-toolkit` pronto para instalação via *apt*. A versão disponibilizada não é a mais atual (`9.1.85` vs `10.0`), mas tudo funciona de maneira integrada e não é necessário instalar nada manualmente. Esta versão será suportada pelo curso.

**Instruções não tão fáceis**: Visitar [o site da NVIDIA](https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64), baixar o pacote `.deb` e instalar manualmente. Estas instruções não são difíceis, mas como pode ser necessário instalar novos drivers de vídeo isto pode dar algum trabalho.     
    


<!--
## Transformações customizadas

Além das operações unárias e binárias disponíveis podemos criar também nossas próprias operações. A sintaxe é bastante estranha, mas ainda é mais fácil que usar kernels do *CUDA C*. A operação abaixo calcula soma o valor de dois vetores, elemento a elemento, e divide por um valor especificado pelo usuário. 

\newpage

~~~{.cpp}
struct custom_transform
{
    
    const double param;

    custom_transform(double d): double_param(d) {}

    __host__ __device__
        double operator()(const double& x, const double& y) const { 
            return (x + y)/d;
        }
};
~~~

**Exercício**: reescreva a variância do exercício acima usando uma transformação customizada. Para ter ainda mais desempenho pesquise como usar `thrust::transform_reduce` para fazer, ao mesmo tempo, a transformação e o somatório do reduce.  Meça o tempo de sua implementação e compare com a do exercício anterior, que usa várias chamadas a `transform` e `reduce`. 

**Exercício**: uma informação importante é saber se o valor de uma ação subiu no dia seguinte. Isto seria útil para, por exemplo, fazer um sistema de Machine Learning que decide compra e venda de ações. Porém, gostaria de saber se houve um aumento significativo, ou seja, quero gerar um vetor que possui 1 se o aumento foi maior que 10% e 0 caso contrário. Complemente seu programa para gerar uma 

**Dica**: uma maneira de fazer isto é criar uma transformação customizada. 


**Desafio**: a média móvel é um modelo de análise de séries temporais usado para verificar se a tendência de uma série é de subida ou queda. Ela é calculada usando a média dos últimos $n$ eventos para prever o evento atual. Implemente este modelo nos dados das ações do google usando os últimos 7 dias para prever o dia atual. 
-->
