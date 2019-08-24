#include "sum.hpp"
#include <math.h>
#include <iostream>

void ExperimentoSum::experiment_code() {
    sum = 0;
    for (int i = 0; i < this->n; i++) {
        sum += this->v[i];
    }
    std::cout << "value for sum: " << sum << "\n";
    return;
}