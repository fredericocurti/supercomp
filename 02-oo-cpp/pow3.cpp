#include "pow3.hpp"
#include <math.h>

void ExperimentoPow::experiment_code() {
    for (int i = 0; i < this->n; i++) {
        this->v[i] = pow(this->v[i], 3);
    }
}