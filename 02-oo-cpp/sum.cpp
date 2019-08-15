#include "sum.hpp"
#include <math.h>

void ExperimentoSum::experiment_code() {
    sum = 0;
    for (int i = 0; i < this->n; i++) {
        sum += this->v[i];
    }
    return;
}