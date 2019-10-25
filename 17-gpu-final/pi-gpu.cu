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

static long STEPS = 1000000000;
static int THREADS_PER_BLOCK = 1024;
static double STEP = 1.0 / (double) STEPS;

__global__ void pi_cuda(double *a, double step) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    double x = (i + 0.5) * step;
    a[i] = 4.0 / (1.0 + x * x);
}

double pi_omp_parallel_for() {
    double sum;
    double x = 0;
    #pragma omp parallel for reduction(+:sum) firstprivate(x)
    for (int i = 0; i < STEPS; i++) {
        x = (i + 0.5) * STEP;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    return STEP * sum;
}

int main(int argc, char **argv) {
    thrust::device_vector<double> v(STEPS);
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, NULL);
    pi_cuda<<<ceil((double) STEPS/THREADS_PER_BLOCK), THREADS_PER_BLOCK>>>(thrust::raw_pointer_cast(v.data()), STEP);
    double sum = thrust::reduce(v.begin(), v.end(), 0.0, thrust::plus<double>());
    double pi = sum * STEP;

    cudaEventRecord(stop, NULL);
    cudaEventSynchronize(stop);
    float msecTotal = 0.0f;
    cudaEventElapsedTime(&msecTotal, start, stop);

    // Compute and print the performance 
    printf("Time= %2.5f\n",msecTotal);
    std::cout << pi << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    pi = pi_omp_parallel_for();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    std::cout << "Time(omp)" << runtime.count() << std::endl;
    std::cout << pi << std::endl;
}
