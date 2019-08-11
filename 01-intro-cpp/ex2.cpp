#include <iostream>
#include <math.h>
#include <chrono>
using namespace std::chrono;

int main() {
    int n;
    std::cout << "Quantos números cada grupo?" << std::endl;
    std::cin >> n;
    high_resolution_clock::time_point t1, t2;
    t1 = high_resolution_clock::now();
    
    double *g1 = new double[n];
    double *g2 = new double[n];

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < n; i++) {
            std::cout << "Insira um número (grupo " << j+1 << ")" << std::endl;
            if (j == 0) {
                std::cin >> g1[i];
            } else {
                std::cin >> g2[i];
            }
        }
    }

    float sum = 0;
    for (int k = 0; k < n; k++) {
        sum += pow((g1[k] - g2[k]), 2);
    }

    double dist = sqrt(sum);
    
    t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<int,std::milli> >(t2 - t1);

    std::cout << "A distancia euclidiana é: " << dist << std::endl;
    std::cout << "Levou " << time_span.count() << " segundos";
    return 0;
}
