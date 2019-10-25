#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <math.h>
#include <iostream>
#include <iomanip>

__global__ void ingenuo(double *out, double step, long num_steps) {
    long i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= num_steps) return;
    double val = (i + 0.5) * step;
    out[i] = 4.0 / (1.0 + val * val);
}

__global__ void esperto(double *out, double step, long num_steps, long sz) {
    long i = blockIdx.x * blockDim.x + threadIdx.x;

    long start = i * sz;
    long end = (i+1) * sz;
    double sum = 0.0;
    for (int k = start; k < end; k++) {
        if (k >= num_steps) break;
        double val = (k + 0.5) * step;
        sum += 4.0 / (1.0 + val * val);
    }

    out[i] = sum;
}

int main() {
    long num_steps = 1000000000;
    double step = 1.0 / num_steps;

    int nthreads = 1024;
    
    thrust::device_vector<double> ingenuo_data(num_steps);
    int nblocks = ceil(double(num_steps) / nthreads);
    ingenuo<<<nblocks, nthreads>>>(thrust::raw_pointer_cast(ingenuo_data.data()), step, num_steps);
    double pi = step * thrust::reduce(ingenuo_data.begin(), ingenuo_data.end(), 0.0, thrust::plus<double>());
    std::cout << std::setprecision(13);
    std::cout << pi << "\n";
    
    int els_per_thread = 4096;
    thrust::device_vector<double> esperto_data(num_steps/els_per_thread+1, 0);
    int nblocks2 = ceil(double(num_steps)/(nthreads * els_per_thread));
    esperto<<<nblocks2, nthreads>>>(thrust::raw_pointer_cast(esperto_data.data()), step, num_steps, els_per_thread);
    double pi2 = step * thrust::reduce(esperto_data.begin(), esperto_data.end(), 0.0, thrust::plus<double>());
    std::cout << std::setprecision(13);
    std::cout << pi2 << "\n";


    return 0;
}