#include <stdio.h>
#include <cuda_runtime.h>
#include <stdlib.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <iostream>
#include <chrono>
#include <omp.h>
#include "curand.h"
#include "curand_kernel.h"

static double TRIALS = 100000000;
static int THREADS_PER_BLOCK = 1024;
// static double STEP = 1.0 / (double) STEPS;

__global__ void pi_cuda_mc(double *v, double r, int sz = 0) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    double x, y, test;
    curandState st;
    curand_init(0, i, 0, &st);

    if (sz == 0) {
            // números entre -1 e 1
        x = (double) (2 * curand_uniform(&st) - 1);
        y = (double) (2 * curand_uniform(&st) - 1);

        test = x * x + y * y;
        v[i] = (test <= r * r) ? 1 : 0;
        return;
    } else {
        long start = i * sz;
        long end = (i+1) * sz;
        double sum = 0.0;
        for (int k = start; k < end; k++) {
            x = (double) (2 * curand_uniform(&st) - 1);
            y = (double) (2 * curand_uniform(&st) - 1);
            test = x * x + y * y;
            if (test <= r * r) {
                sum++;        
            }
        }
        v[i] = sum;
    }
    
}

// double pi_omp_parallel_for() {
//     double sum;
//     double x = 0;
//     #pragma omp parallel for reduction(+:sum) firstprivate(x)
//     for (int i = 0; i < STEPS; i++) {
//         x = (i + 0.5) * STEP;
//         sum = sum + 4.0 / (1.0 + x * x);
//     }

//     return STEP * sum;
// }

int ingenuo() {
    thrust::device_vector<double> v(TRIALS);
    double r = 1.0; // radius of circle. Side of squrare is 2*r

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, NULL);
    pi_cuda_mc<<<ceil((double) TRIALS/THREADS_PER_BLOCK), THREADS_PER_BLOCK>>>(
        thrust::raw_pointer_cast(v.data()),
        r
    );

    double Ncirc = thrust::reduce(v.begin(), v.end(), 0.0, thrust::plus<double>());
    double pi = 4 * (Ncirc / TRIALS);

    cudaEventRecord(stop, NULL);
    cudaEventSynchronize(stop);
    float msecTotal = 0.0f;
    cudaEventElapsedTime(&msecTotal, start, stop);

    std::cout << "trials:" << TRIALS << "pi is" << pi << std::endl;
    std::cout << msecTotal << " ms" << std::endl;

    // auto start_time = std::chrono::high_resolution_clock::now();
    // pi = pi_omp_parallel_for();
    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    // std::cout << "Time(omp)" << runtime.count() << std::endl;
    // std::cout << pi << std::endl;
    return 0;
}

int esperto() {
    int els_per_thread = 8192;
    thrust::device_vector<double> v(TRIALS/els_per_thread);
    double r = 1.0; // radius of circle. Side of squrare is 2*r
        
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, NULL);
    pi_cuda_mc<<<ceil((double) TRIALS/(THREADS_PER_BLOCK * els_per_thread)), THREADS_PER_BLOCK>>>(
        thrust::raw_pointer_cast(v.data()),
        r,
        els_per_thread
    );

    double Ncirc = thrust::reduce(v.begin(), v.end(), 0.0, thrust::plus<double>());
    double pi = 4 * (Ncirc / TRIALS);

    cudaEventRecord(stop, NULL);
    cudaEventSynchronize(stop);
    float msecTotal = 0.0f;
    cudaEventElapsedTime(&msecTotal, start, stop);

    std::cout << "trials: " << TRIALS << " pi is " << pi << std::endl;
    std::cout << msecTotal << " ms" << std::endl;

    // auto start_time = std::chrono::high_resolution_clock::now();
    // pi = pi_omp_parallel_for();
    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    // std::cout << "Time(omp)" << runtime.count() << std::endl;
    // std::cout << pi << std::endl;
    return 0;
}

int main(int argc, char **argv) {
    esperto();
}