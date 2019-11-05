#include <cuda_runtime.h>
#include "curand.h"
#include "curand_kernel.h"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} point;

__device__ double dist(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

__device__ double cost(int *d_solutions, double *d_distances, int i, int N) {
    double c = 0;
    for (int j = 1; j < N; j++) {
        c += d_distances[d_solutions[i * N + (j - 1)] * N + d_solutions[i * N + j]];
    }
    c += d_distances[d_solutions[i * N] * N + d_solutions[i * N + (N - 1)]];
    return c;
}

__device__ void print_vec_int(int *v, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

__device__ void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

__global__ void distKernel(point *points, double *d_distances, int N) {
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N || j >= N) return;
    d_distances[i * N + j] = dist(points[i], points[j]);
}

__global__ void solKernel(double *d_distances, double *d_costs, int *d_solutions, int N) {
    curandState st;
    double swap_cost = 0; // current cost for 2opt
    double best_cost = 0; // solution cost (smallest)
    int ri; // random index
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    curand_init(0, i, 0, &st);

    // Fill solution with sequential possible N's
    for (int j = 0; j < N; j++) {
        d_solutions[i * N + j] = j;
    }

    // Swap from random indexes to create a new possible solution
    for (int j = 1; j < N; j++) {
        ri = (int) ((N - j) * curand_uniform(&st) + j); // (max - min) * curand + min
        swap(&d_solutions[i * N + j], &d_solutions[i * N + ri]);
        best_cost += d_distances[d_solutions[i * N + (j - 1)] * N + d_solutions[i * N + j]];
    }

    // Add cost between first and last
    best_cost += d_distances[d_solutions[i * N] * N + d_solutions[i * N + (N - 1)]];
    d_costs[i] = best_cost;

    // Swap again for 2opt
    for (int j = 1; j < N; j++) {
        for (int k = j + 1; k < N; k++) {
            swap(&d_solutions[i * N + j], &d_solutions[i * N + k]);
            swap_cost = cost(d_solutions, d_distances, i, N);
            if (swap_cost > best_cost) { // undo
                swap(&d_solutions[i * N + k], &d_solutions[i * N + j]);
            } else { // keep the solution
                best_cost = swap_cost;
            }
        }
    }
    d_costs[i] = best_cost;
}

int main(int argc, char *argv[]) {
    // Variable declaration
    int N, min_cost_pos;
    int SOLUTIONS = atoi(argv[1]);
    double min_cost;
    float msecTotal = 0.0f;
    point p;
    std::cin >> N;
    thrust::host_vector<point> h_points(N);
    thrust::device_vector<double> d_distances(N * N);
    thrust::device_vector<double> d_costs(SOLUTIONS);
    thrust::device_vector<int> d_solutions(SOLUTIONS * N);
    thrust::device_vector<double>::iterator min_cost_iter;
    
    // Read from file
    for (int i = 0; i < h_points.size(); i++) {
        std::cin >> p.x;
        std::cin >> p.y;
        h_points[i] = p;
    }

    // Copy points vector to device
    thrust::device_vector<point> d_points(h_points);

    // Precompute distances in GPU
    dim3 threads_dist(32, 32, 1);
    dim3 grid_dist(ceil(N/threads_dist.x), ceil(N/threads_dist.y), 1);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, NULL);

    distKernel<<<grid_dist, threads_dist>>>(
        thrust::raw_pointer_cast(d_points.data()),
        thrust::raw_pointer_cast(d_distances.data()),
        N
    );

    // Each thread will generate a random solution
    solKernel<<<ceil(SOLUTIONS/1024), 1024>>>(
        thrust::raw_pointer_cast(d_distances.data()),
        thrust::raw_pointer_cast(d_costs.data()),
        thrust::raw_pointer_cast(d_solutions.data()),
        N
    );

    cudaEventRecord(stop, NULL);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&msecTotal, start, stop);

    // Find smallest cost for best solution
    min_cost_iter = thrust::min_element(d_costs.begin(), d_costs.end());
    min_cost_pos = min_cost_iter - d_costs.begin();
    min_cost = *min_cost_iter;

    std::cerr << msecTotal << " ms" << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << min_cost << " 1" << std::endl;
    for (int i = min_cost_pos * N; i < (min_cost_pos * N) + N; i++) {
        std::cout << d_solutions[i] << " ";
    }
    std::cout << "\n";
}