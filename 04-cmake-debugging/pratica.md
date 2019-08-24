% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Projetos usando CMake e Debugging

Até o momento todos nossos arquivos eram compilados em uma só linha usando `g++`. Conforme projetos ficam maiores e são divididos em vários módulos isto se torna inviável. Neste roteiro iremos usar o CMake, uma ferramente de gerenciamento de projetos em C++. Também iremos, na parte 2, configurar o VS Code para debugar projetos CMake. 

----

**Atenção**: Usar ferramentas adequadas aumenta consideravelmente a produtividade e também facilita encontrar erros no código. A partir desta aula será obrigatório já ter debugado o programa antes de tirar dúvidas. 

----

## Gerenciamento de projetos com CMake

O [CMake](http://www.cmake.org) é atualmente a ferramenta mais usada para gerenciar projetos C/C++. Um projeto é definido por um arquivo nomeado *CMakeLists.txt* onde é definido nome do projeto, quais dependências são usadas e o quais arquivos serão gerados pelo projeto. Cada arquivo gerado é chamado de *target* na nomenclatura usada pelo CMake e pode ser um executável ou uma biblioteca (estática ou dinâmica). 

Um arquivo *CMakeLists.txt* básico pode conter apenas três linhas (supondo que você tenha um arquivo *hello_world.cpp* que seja um hello world em C++, se não tiver crie :)

```
cmake_minimum_required(version 3.9)
project (projeto_basico)
add_executable(hello hello_world.cpp)
```

Este arquivo somente descreve o projeto. Para efetivamente compilarmos o programa precisamos passar pela fase de *configuração*, em que o *CMake* checa se todas as dependências foram encontradas e se os compiladores necessários estão instalados. Se tudo estiver em ordem podemos gerar um *Makefile* (para Linux) ou um projeto do Visual Studio (para Windows). 

Para fazer a configuração do projeto basta rodar o comando `cmake` mais o caminho para a pasta do projeto. Você só precisará refazer a configuração do projeto se modificar o arquivo *CMakeLists.txt*.  É boa prática fazer a compilação do código em uma pasta separada, como na sequência de comandos abaixo.

    mkdir build
    cd build
    cmake ..

Estes comandos devem ter gerado uma série de arquivos na pasta *build*, incluindo um *Makefile*. Para compilar o projeto basta rodar

    make
    
E um executável de nome *hello* deverá aparecer na pasta *build*. 

Além da criação de executáveis o CMake também permite adicionar opções de compilação específicas para cada *target* com a diretiva `target_compile_options`. No contexto desta matéria isto será especialmente interessante pois o `g++` oferece flags para ativar otimizações que podem melhorar significativamente o desempenho de nosso programa. Portanto, podemos facilmente compilar o mesmo programa com e sem otimizações no mesmo projeto! O exemplo abaixo ativa a flag `O3` no *target* `hello` criado no exemplo anterior. 

    target_compile_definitions(hello O3)

### Exercício

Crie um arquivo *CMakeLists.txt* para sua atividade de C++. Ela deverá criar um target `vector_operations` que compila junto todos as subclasses de `Experimento` e seu `main.cpp`. 

### Exercício

Modifique seu *target* `vector_operations` para que ele use a opção de compilação `O0`.

### Exercício

Crie um novo *target* `vector_O3` que seja igual ao anterior mas que use a opção de compilação `O3`. Compare o desempenho dos dois executáveis em um vetor de tamanho `100000`. 


## Debugando seu projeto 

Agora iremos abrir nosso projeto um ambiente de desenvolvimento em vez de continuar trabalhando na linha de comando. Adotaremos o VSCode como ambiente padrão. 

O VSCode não vem com suporte por padrão a projetos CMake, mas a extensão *Cmake Tools* (de vector-of-bool) possui um bom suporte. Instale-a e carregue o projeto. A extensão possui uma documentação tanto para a etapa de [configuração e compilação](https://vector-of-bool.github.io/docs/vscode-cmake-tools/getting_started.html#configuring-your-project) quanto para [execução dos programas e debugging](https://vector-of-bool.github.io/docs/vscode-cmake-tools/debugging.html). 

Para executar os programas você pode usar a opção "Run in terminal" disponível no menu do botão direito de cada *target*. 

--------

Supondo que a etapa anterior funcionou, vamos agora rodar o nosso programa usando um debugger. Isto permite parar a execução no meio do programa e examinar o valor das variáveis. 

**Passo 0**: colocar um ou mais *breakpoints* no código. Basta clicar ao lado do número da linha. Um círculo vermelho indica que a execução será interrompida quando chegar nesta linha.

**Passo 1**: botão direito no target -> "Run with debugger".

**Passo 2**: quando o programa parar teremos as seguintes opções:

    * **Continue**: roda até o próximo *breakpoint*
    * **Step Over**: roda a linha atual e passa para a próxima.
    * **Step Into**: se a linha atual tem uma chamada de função, continua o debug dentro da função chamada.
    * **Step Out**: executa até o fim da função atual e para logo após o retorno.

**Passo 3**: Também podemos colocar o mouse em cima de cada variável para ver seu valor. O explorador de variáveis (que mostra todas as válidas na função atual) aparece no painel esquerdo, dentro da view *debug*.

Com isto conseguimos executar um programa interativamente e encontrar erros. 

### Exercício

Abra sua atividade e rode-a com o debugger. Pause a execução no meio e verifique os tempos de execução. 


## Exercício final

Faça um commit final de seu projeto. Ele deverá ser formato por vários pares de arquivos *.cpp/.hpp*, um arquivo *main.cpp* e um arquivo *CMakeLists.txt*. Seu projeto deverá compilar duas versões de seu *main.cpp*: uma com otimizações (flag `O3`) e uma sem nenhuma otimização (flag `O0`). 

Além de seu programa, entregue gráficos mostrando as diferenças de tempo entre os dois programas para os seguintes experimentos:

* pow3 e pow3mult (no mesmo gráfico)
* log
* sqrt

Iremos explicar as diferenças de desempenho obtidas nas próximas aula. 