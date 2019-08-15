#include "sqrt.hpp"
#include <math.h>

void ExperimentoSqrt::experiment_code() {
    for (int i = 0; i < this->n; i++) {
        this->v[i] = sqrt(this->v[i]);
    }
}