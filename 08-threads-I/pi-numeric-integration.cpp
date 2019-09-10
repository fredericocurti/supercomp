#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

static long num_steps = 100000000;
static int N_THREADS = omp_get_max_threads();
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

double pi_threads_raiz(long steps) {
    int i;
    double x, pi, sum = 0.0;
    int n_threads = 4;
    int spt = steps / n_threads; // steps per thread
    std::thread threads[4];
    step = 1.0 / (double)steps;

    for (int i = 0; i < n_threads; i++) {
        threads[i] = std::thread(paralel_sum, &sum, i * spt, (i+1) * spt);
    }

    for (int i = 0; i < n_threads; i++) {
        threads[i].join();
    }

    pi = step * sum;
    return pi;
}

double pi_omp_parallel(long steps) {
    int spt = steps / N_THREADS; // steps per thread
    double *sum = new double[N_THREADS];
    double sum_total = 0;

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = tid * spt;
        int end = (tid + 1) * spt;
        double x = 0;
        sum[tid] = 0;
        for (int i = start; i < end; i++) {
            x = (i + 0.5) * step;
            sum[tid] = sum[tid] + 4.0 / (1.0 + x * x);
        }
    }

    for (int j = 0; j < N_THREADS; j++) {
        sum_total += sum[j];
    }

    return step * sum_total;
}

double pi_omp_parallel_local(long steps) {
    int spt = steps / N_THREADS; // steps per thread
    double *sum = new double[N_THREADS];
    double sum_total = 0;

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = tid * spt;
        int end = (tid + 1) * spt;
        double sum_local = 0;
        double x = 0;
        for (int i = start; i < end; i++) {
            x = (i + 0.5) * step;
            sum_local = sum_local + 4.0 / (1.0 + x * x);
        }
        sum[tid] = sum_local;
    }

    for (int j = 0; j < N_THREADS; j++) {
        sum_total += sum[j];
    }

    return step * sum_total;
}


double pi_omp_parallel_atomic(long steps) {
    int spt = steps / N_THREADS; // steps per thread
    double sum_total = 0;

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = tid * spt;
        int end = (tid + 1) * spt;
        double sum_local = 0;
        double x = 0;
        for (int i = start; i < end; i++) {
            x = (i + 0.5) * step;
            sum_local = sum_local + 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        sum_total += sum_local;
    }

    return step * sum_total;
}

double pi_omp_parallel_critical(long steps) {
    int spt = steps / N_THREADS; // steps per thread
    double sum_total = 0;

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = tid * spt;
        int end = (tid + 1) * spt;
        double sum_local = 0;
        double x = 0;
        for (int i = start; i < end; i++) {
            x = (i + 0.5) * step;
            sum_local = sum_local + 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        sum_total += sum_local;
    }

    return step * sum_total;
}

double pi_omp_parallel_for(long steps) {
    int spt = steps / N_THREADS; // steps per thread
    double sum;
    double x = 0;
    #pragma omp parallel for reduction(+:sum) firstprivate(x)
    for (int i = 0; i < steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    return step * sum;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    double pi_raiz = pi_threads_raiz(num_steps);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "O valor de pi calculado com pi_threads_raiz levou ";
    std::cout.precision(17);
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : " << pi_raiz << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    double pi_nutella = pi_omp_parallel(num_steps);
    end_time = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "O valor de pi calculado com pi_omp_parallel levou ";
    std::cout.precision(17);
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : " << pi_nutella << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    double pi_nutella_local = pi_omp_parallel_local(num_steps);
    end_time = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "O valor de pi calculado com pi_omp_parallel_local levou ";
    std::cout.precision(17);
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : " << pi_nutella_local << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    double pi_nutella_atomic = pi_omp_parallel_atomic(num_steps);
    end_time = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "O valor de pi calculado com pi_omp_parallel_atomic levou ";
    std::cout.precision(17);
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : " << pi_nutella_atomic << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    double pi_nutella_critical = pi_omp_parallel_critical(num_steps);
    end_time = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "O valor de pi calculado com pi_omp_parallel_critical levou ";
    std::cout.precision(17);
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : " << pi_nutella_critical << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    double pi_nutella_for = pi_omp_parallel_for(num_steps);
    end_time = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "O valor de pi calculado com pi_omp_parallel_for levou ";
    std::cout.precision(17);
    std::cout << runtime.count() << " milisegundo(s) e chegou no valor : " << pi_nutella_for << std::endl;
}
