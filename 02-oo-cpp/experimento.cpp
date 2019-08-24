#include "experimento.hpp"
#include <iostream>
#include <math.h>
#include <chrono>
#include <random>
#include <utility>
using namespace std;

Experimento::Experimento() {
    // std::cout << "Objeto Experimento criado!\n";
}

std::vector<double> Experimento::gera_entrada(int n) {
    int seed = 2;
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution(5, sqrt(0.5));
    std::vector<double> v;
    for (int i = 0; i < n; i++) {
        v.push_back(distribution(generator));
    }
    this->v = v;
    this->n = n;
    return v;
}

double Experimento::duration() {
    return this->d;
}

std::pair<double, double> Experimento::run() {
    chrono::high_resolution_clock::time_point t1, t2;
    std::vector<double> times;
    double total_time = 0;
    
    for (int j = 0; j < 10; j++) {
        this->gera_entrada(n);
        t1 = chrono::high_resolution_clock::now();
        this->experiment_code();
        t2 = chrono::high_resolution_clock::now();

        chrono::duration<double> time_span = t2 - t1;
        this->d = time_span.count() * 1000;
        total_time += time_span.count() * 1000;
        times.push_back(time_span.count() * 1000);
    }

    std::cout << "TOTAL TIME: " << total_time << "\n"; 
    double mean = total_time /= 10;
    double stddev = 0;

    for (int i = 0; i < 10; i++) {
        stddev += pow(times[i] - mean, 2);
    }

    stddev = sqrt(stddev / 10);
    times.clear();
    
    return std::make_pair(mean, stddev);
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
