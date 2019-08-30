
# Projeto 1: C++ e SIMD

No primeiro projeto de SuperComputação iremos tratar o problema da simulação de física 2D. Faremos uma simulação simplificada em que todo corpo é representado por um retângulo se movimentando em um plano. Neste contexto, técnicas de Super Computação são importantes pois permitem  tanto aumentar o número de corpos na simulação quanto diminuir o intervalo de tempo usando nos cálculos. Apesar de não parecer muito realista, diversos jogos usam esta modelagem para tratar colisões e movimentações dos elementos do jogo. 

Os objetivos deste projeto são

1. implementar um projeto de média complexidade (em termos de especificações técnicas) em C++;
1. estudar efeito de opções de compilação e de vetorização em um projeto mais complexo que as atividades de sala de aula;
1. montar uma comparação de desempenho reprodutível e descritiva.

**Lembrete**: esta atividade deve ser feita de maneira individual. Um documento contendo [Orientações sobre integridade intelectual em atividades de programação](https://tinyurl.com/comp-insper-atividades) (url: https://tinyurl.com/comp-insper-atividades) foi criado pela coordenação e responde algumas dúvidas comuns sobre colaboração em atividades que valem nota. 

# Requisitos de implementação

Nosso modelo de física entenderá que todos os corpos de nossa simulação são retângulos que possuem massa, posição, velocidade e aceleração. Para simplificar nosso modelo, **nossos retângulos não possuem velocidade angular**. Ou seja, eles não giram.

As colisões em nosso modelo seguem duas simplificações. Elas são sempre totalmente elásticas (ou seja, só rebatem sem perder energia cinética). Mais informações sobre colisão elástica podem ser vistas [nesta página](https://pt.wikipedia.org/wiki/Colis%C3%A3o_el%C3%A1stica). 

A segunda simplificação de nossa simulação refere-se ao comportamento dos corpos ao detectar que haverá uma colisão. A cada passo da simulação calculamos a posição do corpo no próximo instante de tempo. Se detectarmos uma colisão iremos somente mudar os vetores de velocidade, mas não os moveremos. Ou seja, **em cada iteração só atualizamos a posição de um corpo se ele não colidir com outro corpo.**

**Atenção**: as contas já estão feitas! Não é necessário derivar expressões nem qualquer talento físico para fazer este projeto. Basta ler a página acima e identificar qual equação se aplica ao nosso caso. 

**Atenção**: colisões são um tema difícil. Tragam suas dúvidas para a aula de terça!

Nosso ambiente de simulação possui tamanho $w \times h$ e coeficiente de atrito $\mu_d > 0$ recebidos como parte da entrada do programa. Colisões com as bordas apenas "rebatem" o retângulo na direção oposta.

Nossa simulação acaba quando o módulo da velocidade de todos os corpos for menor que $0,0001 m/s$. Isso é garantido de acontecer, pois o atrito eventualmente leva todas as velocidades a 0. 



## A entrada

A entrada de seu programa será padronizada e seguirá o seguinte formato. 

```
w h mu_d
N
m wr hr x y vx vy 
.... 
m wr hr x y vx vy 
dt print_freq max_iter
```

* `w`, `h` e `mu_d` se referem ao tamanho do campo de simulação e seu coeficiente de atrito dinâmico.
* `N` é o número de retângulos da simulação. Cada linha subsequente contém um retângulo com as seguintes propriedades:
    * massa `m`
    * largura `wr`
    * altura `hr`
    * posição inicial `(x, y)`
    * velocidade inicial  `(vx, vy)`
* `dt` representa o tamanho do passo de simulação. 
* a cada `print_freq` iterações o estado da simulação é mostrado na saída padrão.
* a simulação deverá rodar até `max_iter` vezes. Note que ela pode acabar antes. 

Note que os retângulos só recebem velocidade inicial, porém a presença de atrito causa uma aceleração neles. 

## A saída

A cada `print_freq` iterações seu programa deverá mostrar o estado atual da simulação no seguinte formato. 

```
iter
x1 y1 vx1 vy1
...
xN yN vxN vyN
--------
```

Quando a simulação terminar você também deverá imprimir o estado final da simulação. Isto pode ocorrer se `max_iter` iterações forem feitas ou se o módulo da velocidade de todos os retângulos for menor que $0,0001 m/s$.


# Avaliação

A avaliação do projeto estará dividida em duas partes: relatório e implementação. Cada uma possui regras específicas e para obter nota final maior que **C** você deverá obter nota maior que **C** em ambas.

## Requisitos de entrega

Os requisitos abaixo são obrigatórios para todos os projetos. Não cumprir qualquer um dos itens implica em nota final **D**.

- [ ] CMakeLists.txt 
- [ ] Relatório feito em Jupyter Notebook (ou software similar). Seu relatório deve conter as seguintes seções: 
    - [ ] Descrição do problema tratado
    - [ ] Descrição dos testes feitos (tamanho de entradas, quantas execuções são feitas, como mediu tempo)
    - [ ] Organização em alto nível de seu projeto.
- [ ] Versão já rodada do relatório exportada para *PDF*
- [ ] README.txt explicando como rodar seus testes
- [ ] Conjunto de testes automatizados (via script Python ou direto no relatório)
- [ ] Respeitar os formatos de entrada e saída definidos na seção anterior

Estes requisitos formam a base de um projeto bem organizado e deverão ser seguidos para todos os projetos de SuperComputação. Eles representam o mínimo para que seu projeto seja **reprodutível**. Ou seja, eles existem para facilitar que outras pessoas possam compilar o seu projeto e reproduzir seus resultados. 

## Relatório

O relatório seguira uma rubrica contendo diversos itens. A nota final de relatório é a média das notas parciais, levando em conta a seguinte atribuição de pontos.

* **I** - 0 pontos: Não fez ou fez algo totalmente incorreto.
* **D** - 4 pontos: Fez o mínimo, mas com diversos pontos para melhora.
* **B** - 7 pontos: Fez o esperado. Não está fantástico, mas tem qualidade. 
* **A+** - 10 pontos: Apresentou alguma inovação ou evolução significativa em relação ao esperado.


![desemepnho](rubrica-desempenho-nova.png)

## Implementação

Sua implementação seguirá a seguinte rubrica. 

* **I**: Não compila. 
* **D**: 
    - o programa retorna o resultado incorreto
    - código bagunçado e impossível de seguir
* **C**: 
    - o programa retorna o resultado correto
    - foi testada ao menos uma opção de compilação diferente de `-O3`
* **B**:
    - foram compiladas versões com e sem auto vetorização.

Os seguintes pontos extras serão distribuídos se o conceito for maior que **C**.

* **1,0**:
    - código apresentado é limpo, simples de entender e bem documentado.
* **2,0**:
    - implementou manualmente vetorização em alguma das funções do programa.

Fique atento à corretude de seu programa! Se ele retornar resultados incorretos nenhuma otimização ou capricho extra faz sentido.