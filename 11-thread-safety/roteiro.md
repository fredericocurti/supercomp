% 07 - Thread safety
% Super Computação 2018/2
% Igor Montagner, Luciano Soares

Vamos trabalhar hoje com o arquivo *pi_mc.cpp*. Serão testadas duas técnicas diferentes de paralelização neste roteiro e ambas possuem vantagens e desvantagens.

Um código *sem efeitos colaterais* é escrito de tal maneira que toda a informação usada deve ser passada como argumento para nossas funções e toda modificação é feita via um valor retornado. Para transformar código "comum" em código sem efeitos colaterais tipicamente precisamos eliminar variáveis globais e evitar o uso de ponteiros. Não se esqueça de que variáveis `static` também são globais, porém seu escopo é limitado a um arquivo ou função específica. Outro ponto importante é podemos passar a mesma variável como ponteiro para duas funções rodando em threads diferentes. Logo, uma thread poderia modificar o andamento de outra, violando a ideia de efeito colateral. 

# Parte 0: analizando o código existente

Nesta parte do roteiro iremos analisar o código exemplo, testar uma paralelização ingênua e identificar seus possíveis problemas de paralelização.

**Exercício**: Considerando somente o arquivo *pi_mc.c*, existe código com  efeitos colaterais? Faça uma paralelização ingênua deste código. \vspace{1.5em}

**Exercício**: Teste a paralelização ingênua do exercício anterior. Ela retorna os mesmos resultados em todas execuções? Se não, comente por que isto é um problema. \vspace{4em}

**Exercício**: Dado que não encontramos problemas no arquivo *pi_mc.c*, vamos olhar então os arquivos *random.c/h*. 

1. Existe código com efeitos colaterais? Liste as funções encontradas. \vspace{3em}
2. Voltando para *pi_mc.c*, onde são chamadas as funções identificadas acima?\vspace{3em}
3. Agora que você está familiarizado com todo o código, explique por que os resultados são diferentes quando rodamos o código ingenuamente paralelo.\vspace{3em}

Só prossiga após validar as respostas do item anterior com o professor ou com um colega que já tenha finalizado esta parte.

# Parte 1: paralelização das distâncias

Identificamos na parte anterior que a função `drandom` possui efeitos colaterais e estes efeitos colaterais estão atrapalhando a paralelização do código. Note, porém, que os cálculos de distância são independentes desde que os sorteios aleatórios já tenham sido feitos. 

Note que esta implementação é parecida com as funções do cabeçalho `<random>`: temos um estado do gerador de números que é passado para toda função que faz sorteios. Neste caso, o resultado do próximo número sorteado depende dos valores globais `MULTIPLIER`, `ADDEND`, `PMOD` e da variável estática `random_last`.

**Exercício**: modifique o código para que ele use as funções de geração de números aleatórios usando `<random>`. Salve em *pi_mc_random.cpp*.

Vamos agora iniciar a paralelização desse código.

**Exercício**: Modifique *pi_mc_random.cpp* para que o sorteio dos pontos seja feito em um vetor **antes** do `for` que faz os cálculos de distâncias. 

**Exercício**:  É possível paralelizar o `for` que faz o sorteio dos números? E o que faz o cálculo das distâncias? Paralize o que for possível e salve em um arquivo *pi_mc_par1.cpp*


**Exercício**: Houve ganho expressivo de desempenho? Compare com o programa original.

Esta estratégia é muito comum em casos em que a tarefa de interesse pode ser decomposta em uma parte inerentemente sequencial e uma que pode ser paralelizada mas que depende dos resultados da parte sequencial. Se a parte paralelizável for custosa essa estratégia pode trazer ganhos mesmo que o programa não seja inteiramente paralelizável. 

# Parte 2: partes independentes

A segunda estratégia que usaremos é criar um gerador de números aleatórios para cada thread. Ou seja, cada thread precisará:

1. criar um gerador de números aleatórios próprio
1. acumular os resultados na mesma variável de somar pontos. 

Note que esta estratégia não é equivalente ao programa original: cada thread está seguindo uma sequência diferente de números aleatórios. 

**Exercício**: reorganize seu código (partindo de *pi_mc_random.cpp*) para que cada thread crie seu próprio gerador de números aleatórios e faça 1/4 das iterações originais. Salve seu trabalho em *pi_mc_par2.c*

**Exercício**: compare o desempenho com o programa original. 

# Parte 3 - exclusão mútua

Na aula *09* usamos `omp critical` para criar seções de exclusão mútua em que somente uma das threads rode por vez. 

**Exercício**: utilize este recurso para paralelizar o código em *pi_mc_random.cpp*. O código é mais simples que os anteriores?

# Parte 4 - comparação de desempenho final

Compare o desempenho das duas abordagens de paralelização. Elas chegam em bons resultados usando números similares de iterações? Qual é mais fácil de ser entendida?

# Parte 5 - Extra

**Exercício**: Tente modificar seu código para que o autovetorizador possa otimizar o loop do cálculo das distâncias. Você não deve usar OpenMP neste caso. Compare os valores obtidos com o código acima.
