% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

Na última aula conseguimos rodar algumas funções em GPU e medir o custo de transferência de dados. Chegamos a conclusão que, para valer a pena usar a GPU, ou precisamos tratar muitos dados ou precisamos fazer tratamentos pesados. 

# Parte 1 - iteradores

Continuando a partir do último item da aula anterior, suponha que você deseja calcular a variância das diferenças. Agora que já temos a média, a fórmula da variância é dada por 

`sum (xi - mean)^2`

## Exercício

Já sabemos tudo o que precisamos para fazer este cálculo. Crie um vetor em que todas as componentes sejam iguais a média (usando `thrust::fill`) e compute a variância usando a fórmula acima. 

------
Apesar do código acima funcionar, ele tem um problema grave: é preciso alocar um vetor inteiro somente para preenchê-lo com valores iguais! Se estivermos trabalhando com muitos dados isto significa diminuir bastante a quantidade de dados que conseguimos tratar antes de acabar com a memória da GPU. Podemos contornar isso usando iteradores, que são vetores gerados dinamicamente pela thrust a partir de um valor único ou a partir de outros vetores. 

## Exercício

Pesquise a documentação de `thrust::constant_iterator` e use-o para substituir a alocação de memória extra no exercício acima. 

# Parte 2 - transformações customizadas

Nosso programa agora tem uma porção de chamadas `transform` e `reduce`. Seria muito conveniente se pudéssemos juntar várias operações em uma só, não? Podemos fazer isto na thrust usando operações customizadas. 

## Operações customizadas - transform

Uma operação customizada permite escrever a função que será aplicada em cada elemento do vetor (ou vetores). Ou seja, no caso da variância poderíamos já criar uma operação que faz a subtração do vetor pela média e já eleva este valor ao quadrado. Depois só precisaríamos fazer um `reduce` para realizar o somatório.


A sintaxe para definir transformações customizadas é um pouco estranha. Ele envolve criar um `struct` que sobrescreve o operador chamada de função (`()`) e adicionar algumas anotações na declaração desta função. Veja abaixo uma transformação customizada que soma `num` em cada elemento de um vetor `double`.

```cpp
struct custom_op {

    double num;
    
    custom_op(double n): num(n) {}

    __host__ __device__ 
    double operator() (double el) {
        return el + num;
    }
}
```

## Exercício

Use uma operação customizada para computar a variância da diferença entre os valores das ações calculados no último item do roteiro anterior. 

## Exercício

Existe diferença de tempo entre as três versões de variância criadas? E de legibilidade? Qual você acharia mais fácil de escrever/ler?

## Exercício

Uma informação importante é saber se o valor de uma ação subiu no dia seguinte. Isto seria útil para, por exemplo, fazer um sistema de Machine Learning que decide compra e venda de ações. Porém, gostaria de saber se houve um aumento significativo, ou seja, quero gerar um vetor que possui 1 se o aumento foi maior que 10% e 0 caso contrário. 

**Dica**: use uma transformação customizada do vetor começando a partir da posição 1 com ele mesmo começando na posição 0. 

# Parte 3 - acesso direto ao vetor

No último exercício tivemos que fazer um "truque" para acessar uma posição vizinha de nosso vetor. Isto pode dificultar o uso dos algoritmos da `thrust` por necessitar código com uma lógica bastante indireta.

Felizmente, podemos ultrapassar esta limitação passando para operações customizadas um ponteiro para memória na GPU! Veja o exemplo abaixo:

```cpp
struct acesso_direto {
    double *pointer_gpu;

    acesso_direto(double *pointer_gpu): pointer_gpu(pointer_gpu) {}

    __host__ __device__
    double operator() (int i) {
        return pointer_gpu[i] + 5;
    }
};

....

auto index = thrust::make_counting_iterator(0);
acesso_direto op(thrust::raw_pointer_cast(vec.data()));
thrust::transform(index, index + vec.size(), vec_out.begin(), op);

....

```

Na transformação acima, `pointer_gpu` é um ponteiro para o vetor alocado na GPU e pode ser acessada diretamente pela função customizada. Note que estamos recebendo o índice a ser processado ao invés do valor. Isto ocorre pois usamos, na chamada de `transform` abaixo um `thrust::counting_iterator`. O exemplo completo está disponível no arquivo `exemplo-pointer-gpu.cu`.

## Exercício

Refaça o código do último exercício da seção anterior usando esta técnica. Funciona tudo corretamente? Não se esqueça de checar se todos os acessos a memória são válidos.

## Exercício

Vamos finalmente introduzir uma ferramenta que quantifica os tempos que nossas funções levam para rodar e o tempo gasto com as chamadas de API do CUDA. Execute o exemplo de transformação com acesso direto usando a ferramenta `nvprof`. Leia a saída e escreva abaixo:

1. quanto tempo foi gasto fazendo alocação de memória (dica: procure por malloc)
2. quanto tempo foi gasto com cópias? (dica: procure por memcpy)

Troque o tamanho do vetor alocado para 1000. Esses tempo mudam significativamente?

# Parte 4 - imagens

Tente refazer o exercício do Quiz 1 usando `thrust` e operações customizadas. 
