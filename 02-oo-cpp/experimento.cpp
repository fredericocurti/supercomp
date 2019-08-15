#include "experimento.hpp"
#include <iostream>
#include <math.h>
#include <chrono>
using namespace std;

// A função abaixo é chamada ao criar um objeto ExemploRect
Experimento::Experimento() {
    // std::cout << "Objeto Experimento criado!\n";
}

double* Experimento::gera_entrada(int n) {
    double *v = new double[n];
    for (int i = 0; i < n; i++) {
        v[i] = (double)rand() / RAND_MAX;
    }
    this->v = v;
    this->n = n;
    return v;
}

double Experimento::duration() {
    return this->d;
}

void Experimento::run() {
    chrono::high_resolution_clock::time_point t1, t2;
    t1 = chrono::high_resolution_clock::now();
    this->experiment_code();
    t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = t2 - t1;
    this->d = time_span.count() * 1000;
    //std::cout << "Experimento levou " << this->d << " ms\n";
}

Experimento::operator double() {
    return this->duration();
}

bool Experimento::operator < (Experimento *e) {
    return e->d < this->d && e->n == this->n;
}

bool Experimento::operator < (double d) {
    return this->d < d;
}