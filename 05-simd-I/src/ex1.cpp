#include <random>
#include <iostream>
#include <chrono>
using namespace std;

double soma_positivos1(double *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) {
            sum += a[i];
        }
    }
    return sum;
}

double soma_positivos2(double *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (a[i] >= 0 ? a[i] : 0);
    }
    return sum;
}


int main () {
    chrono::high_resolution_clock::time_point t1, t2;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-10,10);
    chrono::duration<double> time_span;
    double d;
    int n = 10000000;
    double* vec = new double[n];

    for (int i = 0; i < n; i++) {
        vec[i] = double(distribution(generator));  // generates number in the range 
        // std::cout << dice_roll << std::endl;
    }

    std::cout << "Vector ready\n";

    t1 = chrono::high_resolution_clock::now();
    double s1 = soma_positivos1(vec, n);
    t2 = chrono::high_resolution_clock::now();
    time_span = t2 - t1;
    d = time_span.count() * 1000;
    std::cout << "[soma_positivos1] sum: " << s1 << " T: " << d << " ms\n";

    t1 = chrono::high_resolution_clock::now();
    double s2 = soma_positivos2(vec, n);
    t2 = chrono::high_resolution_clock::now();
    time_span = t2 - t1;
    d = time_span.count() * 1000;
    std::cout << "[soma_positivos2] sum: " << s2 << " T: " << d << " ms\n";
}