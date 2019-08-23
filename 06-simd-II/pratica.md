% Super Computação
% Igor Montagner, Luciano Soares
% 2019/2

# SIMD - Funções intrínsecas

Como você já sabe, programar em Assembly não é nada fácil e os recursos de auto vetorização nem sempre funcionam da forma esperada. Assim podemos chamar as funções intrínsecas que mapeiam diretamente paras as instruções vetoriais em máquina. Um guia com todas as funções intrínsecas disponíveis está disponível [no site da Intel](https://software.intel.com/sites/landingpage/IntrinsicsGuide/)

### Exercício

Leia o código abaixo (arquivo *avx-sub.c*), compile-o e rode. Ele apresenta o resultado esperado?

```cpp
#include <x86intrin.h>
#include <stdio.h>
int main() {

	/* Initialize the two argument vectors */
	__m256 evens = _mm256_set_ps(2.0,4.0,6.0,8.0,10.0,12.0,14.0,16.0);
	__m256 odds = _mm256_set_ps(1.0,3.0,5.0,7.0,9.0,11.0,13.0,15.0);

	/* Compute the difference between the two vectors */
	__m256 result = _mm256_sub_ps(evens, odds);

	/* Display the elements of the result vector */
	float* f = (float*)&result;
	printf("%f %f %f %f %f %f %f %f\n",f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
	return 0;
}
```

### Exercício 

Compile e execute o código abaixo (arquivo *avx-mask.c*). Você consegue explicar seu funcionamento? Mexa com os valores da máscara e confirme suas hipóteses.

```cpp
#include <x86intrin.h>
#include <stdio.h>
int main() {

	float int_array[8] = {100, 200, 300, 400, 500, 600, 700, 800};

	/* Initialize the mask vector */
	__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);

	/* Selectively load data into the vector */
	__m256 result = _mm256_maskload_ps(int_array, mask);

	/* Display the elements of the result vector */
	float* res = (float*)&result;
	printf("%f %f %f %f %f %f %f %f\n",
		res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);

	return 0;
}
```

### Exercício

Complete o código do arquivo *avx-sqrt.cpp*, criando uma versão vetorizada da função que calcula a raiz quadrada de forma linear. Anote abaixo os comando usados para habilitar, desabilitar e alinhar memória para uso com as funções intrínsecas.


### Exercício para entrega

O exercício final desta atividade consiste em implementar a função `soma_positivos` usando funções intrínsicas. Adicione esta implementação aos seus experimentos e compare-a com a função `soma_positivos` compilada **sem vetorização**. 

