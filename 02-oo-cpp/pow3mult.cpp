#include "pow3mult.hpp"
#include <math.h>

void ExperimentoPow3Mult::experiment_code() {
    for (int i = 0; i < this->n; i++) {
        this->v[i] = this->v[i] * this->v[i] * this->v[i];
    }
}