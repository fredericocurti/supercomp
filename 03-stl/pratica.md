% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# Introdução a C++ III

Esta prática consiste primariamente em aprender a usar tipos de dados complexos 
disponibilizados pela STL e pela biblioteca padrão de C++

## Smart Pointers


Uma das grandes dificuldades de desenvolver em C++ é evitar vazamentos de memória (memory leaks). Durante o desenvolvimento do programa é muito usado o recurso de alocação dinâmica de memória, contudo da mesma forma que o programador tem a responsabilidade de alocar a memória, ele tem de desalocar a memória. Os smart pointers são uma estratégia de evitar que você esqueça de desalocar e crie um programa devorador de memória. Os smart pointers percebem que uma memória alocada não é mais acessível e desaloca a memória.


**unique_ptr**: um smart pointer para um único objeto com um dono só. Ou seja, este smart pointer aponta para um objeto que deve ter só um apontamento de cada vez. Ao realizarmos atribuições a variável "dono" do objeto muda. 

**shared_ptr**: Um smart pointer para um único objeto e pode ter vários donos. Ou seja, este smart pointer aponta para um objeto que pode ter vários apontamentos de cada vez. Ao realizarmos atribuições adicionamos uma nova referência a este dado. Quando não existem mais referências o dado é automaticamente liberado usando `delete`

### Exercício

Corrija o uso de memória absurdo do programa abaixo (arquivo *tarefa1.cpp*) usando smart pointers.

```cpp
#include <iostream>

int main() {
  int *ptr = new int(0);
  for(int f=0;f<1024*1024*1024;f++) {
    ptr = new int(f);
  }
  std::cout << "valor final = " << *ptr << std::endl;
  delete ptr;
}
```

\newpage

### Exercício

Corrija o uso de memória absurdo do programa abaixo (arquivo *tarefa2.cpp*) usando smart pointers.

```cpp
#include <iostream>

int foo(int x) {
	int *vec1 = new int[8];
	for(int f=0;f<8;f++) vec1[f]=f*x;
	int *vec2 = vec1;
	int tmp = vec1[0]+vec1[4]+vec1[7]-vec1[5];
	return tmp;
}
int main() {
	long int tmp = 0;
	for(int f=0;f<1024*1024*512;f++)  tmp += foo(f);
	std::cout << tmp << std::endl;
}
```


## Strings e Vector

Neste exercício iremos trabalhar com strings. Faça um programa que lê uma linha de texto (usando `std::getline`) e procure nela todas as ocorrências da palavra "hello". Você deverá implementar uma função

`std::vector<int> find_all(std::string text, std::string term);` 

que devolve um vetor com a posição de todas as ocorrências de `term` em `text`. Sua função `main` deverá mostrar os resultados da busca de maneira bem formatada. 

Para isto será necessário olhar as seguintes documentações:

1. [std::string](http://www.cplusplus.com/reference/string/)
1. [std::string::find](http://www.cplusplus.com/reference/string/string/find/)
1. [std::vector](http://www.cplusplus.com/reference/vector/vector/)

## Exercício final

Faça as seguintes modificações no seu exercício final:

1. troque todas alocações para usar smart pointers
1. utilize `std::array` para guardar os dados gerados em `gera_entrada`. 
1. faça com que a função `gera_entrada` gere os dados segundo uma normal com média 5 e variância 0.5
1. modifique `Experimento::run` para rodar a função `Experimento::experiment_code` 10 vezes. Esta função deverá retornar um `std::pair` com a média e o desvio padrão dos tempos de execução.
1. crie um `std::vector` para guardar os resultados dos experimentos (devolvidos pela função acima). 
1. reorganize sua função `main` para usar estes novos recursos implementados em cima da STL. 