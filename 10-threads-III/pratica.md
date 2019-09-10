% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Multi-core II: Introdução a OpenMP

Nesta aula iremos completar nossa atividade de cálculo do *pi*. O seguinte exercício deverá ser entregue como versão final da *Atividade 2*. 

### Exercício

Modifique sua solução para usar as construções `parallel for` e `reduce`. Seus resultados se mantiveram iguais? A quantidade de código diminuiu?

-------------

Nos exercícios abaixo falamos sobre *Fractais*. 

----

**Curiosidade**: fractais são estruturas matemáticas que são definidas por sua auto-similaridade. Eles são úteis para modelar objetos e fenômenos que possuem as mesmas características em escalas completamente diferentes, como nuvens, montanhas e [compressão de arquivos](https://en.wikipedia.org/wiki/Fractal_compression). 

![Exemplos de fractais, Fonte: mathworld.wolfram.com.](http://mathworld.wolfram.com/images/eps-gif/Fractal1_1000.gif){width=250px}

----

### Exercício

O arquivo *mandel.cpp* tem uma implementação que calcula a área abaixo do fractal de Mandelbrot. Foi feita uma tentativa preguiçosa de paralelização usando OpenMP que está dando resultados muito estranhos. Seu trabalho neste exercício é modificar o `#pragma omp` para que ele não permite o compartilhamento indevido de dados entre as threads. 

### Exercício

Apesar do programa agora funcionar, os erros do exercício acima eram causados essencialmente por más práticas de programação. Reestruture o código para que o resultado de suas funções só dependa dos valores passados nos argumentos. Isto costuma implicar na conversão de valores lidos/escritos em variáveis globais para valores passados nos parâmetros da função. Neste exercício você pode mudar o programa extensamente, desde que os resultados continuem os mesmos. 


### Teoria

Dizemos que quando uma função escreve/lê em variáveis globais (ou `static`) ela possui *efeitos colaterais*. Ou seja, após rodar ela modifica o estado do programa. Em comparação, uma função que só depende dos valores passados nos argumentos e não escreve seu resultado (ou valores intermediários) em variáveis globais é dita *sem efeitos colaterais*. Este tipo de função pode ser chamado por várias threads simultâneamente e é uma boa prática de programação paralela criar funções sem efeitos colaterais. 
