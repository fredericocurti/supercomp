#include "log.hpp"
#include <math.h>

void ExperimentoLog::experiment_code() {
    for (int i = 0; i < this->n; i++) {
        this->v[i] = log(this->v[i]);
    }
}