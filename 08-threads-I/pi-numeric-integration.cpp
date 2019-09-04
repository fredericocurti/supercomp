#include <iostream>
#include <chrono>
#include <thread>

static long num_steps = 100000000;
double step;

void paralel_sum(double *sum, int start, int end) {
    int i;
    double x = 0, sum_local = 0;

    for (i = start; i < end; i++) {
        x = (i + 0.5) * step;
        sum_local = sum_local + 4.0 / (1.0 + x * x);
    }

    *sum += sum_local;
}

int main() {
    int i;
    double x, pi, sum = 0.0;
    int N_threads = 4;
    int spt = num_steps / N_threads; // steps per thread
    std::thread threads[4];
    step = 1.0 / (double)num_steps;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Spawn threads
    for (int i = 0; i < N_threads; i++) {
        threads[i] = std::thread(paralel_sum, &sum, i * spt, (i+1) * spt);
    }

    // Wait for them to finish
    for (int i = 0; i < N_threads; i++) {
        threads[i].join();
    }

    // Calculate pi
    pi = step * sum;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    
    std::cout << "O valor de pi calculado com " << num_steps << " passos levou ";
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : ";
    std::cout.precision(17);
    std::cout << pi << std::endl;
}
