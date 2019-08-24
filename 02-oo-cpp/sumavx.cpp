#include "sumavx.hpp"
#include <math.h>
#include <x86intrin.h> //Extensoes SSE
#include "/Users/fredcurti/stdc++.h" //Bibliotecas STD

void ExperimentoSumAvx::experiment_code() {
    __m256d acc = _mm256_setzero_pd();
    sum = 0;
    
    for (int i = 0; i < this->n; i += 4) {
        __m256d vec = _mm256_loadu_pd(&this->v[i]);
        __m256d inv = _mm256_xor_pd(vec, _mm256_set1_pd(-0.0));
        __m256d masked = _mm256_maskload_pd(&this->v[i], _mm256_castpd_si256(inv));
        acc = _mm256_add_pd(masked, acc);
    }

    double* result = (double*)&acc;
    for (int i = 0; i < 4; i++) {
        sum += result[i];
    }

    std::cout << "value for sumavx: " << sum << "\n";
    return;
}