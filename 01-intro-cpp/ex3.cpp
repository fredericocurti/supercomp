#include <iostream>
#include <chrono>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
using namespace std::chrono;

double* gera_vetor(int n) {
    double *v = new double[n];
    for (int i = 0; i < n; i++) {
        v[i] = (double)rand() / RAND_MAX;
    }
    return v;
}

void print_vetor(double* v, int n) {
    std::cout << '[';
    for(int i = 0; i < n; i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << ']' << std::endl;
    return;
}

void log(double* v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = log(v[i]);
    }
}

void sqrt(double* v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = sqrt(v[i]);
    }
}

void pow3(double* v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = pow(v[i], 3);
    }
}

void pow3mult(double* v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = v[i] * v[i] * v[i];
    }
}

double sum(double* v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i];
    }
    return sum;
}

int main() {
    int n = 100000;
    double* v;
    high_resolution_clock::time_point t1, t2;
    
    

    for (int i = 0; i < 5; i++) {
        v = gera_vetor(n);
        duration<double> d;
        std::cout << "==== vetor n : " << n << " ====== \n";

        t1 = high_resolution_clock::now();
        log(v, n);
        t2 = high_resolution_clock::now();
        d = duration_cast<duration<int,std::milli> >(t2 - t1);
        std::cout << "log: " << d.count() << " s\n";

        t1 = high_resolution_clock::now();
        sqrt(v, n);
        t2 = high_resolution_clock::now();
        d = duration_cast<duration<int,std::milli> >(t2 - t1);
        std::cout << "sqrt: " << d.count() << " s\n";

        t1 = high_resolution_clock::now();
        pow3(v, n);
        t2 = high_resolution_clock::now();
        d = duration_cast<duration<int,std::milli> >(t2 - t1);
        std::cout << "pow3: " << d.count() << " s\n";

        t1 = high_resolution_clock::now();
        pow3mult(v, n);
        t2 = high_resolution_clock::now();
        d = duration_cast<duration<int,std::milli> >(t2 - t1);
        std::cout << "pow3mult: " << d.count() << " s\n";

        t1 = high_resolution_clock::now();
        sum(v, n);
        t2 = high_resolution_clock::now();
        d = duration_cast<duration<int,std::milli> >(t2 - t1);
        std::cout << "sum: " << d.count() << " s\n";

        n *= 10;
    }
    
    return 0;
}


