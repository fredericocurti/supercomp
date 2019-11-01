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

typedef struct {
    double x;
    double y;
} point;

__device__ double dist(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
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
    int ri; // random index
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    // printf("%d\n", i);
    int cost = 0;
    curand_init(0, i, 0, &st);

    
    // Fill solution with sequential possible N's
    for (int j = 0; j < N; j++) {
        d_solutions[i * N + j] = j;
    }

    for (int j = 1; j < N; j++) {
        ri = (int) ((N - j) * curand_uniform(&st) + j); // (max - min) * curand + min
        
        // if (i == 0) {
        //     printf("--------  RANDOM INDEX: %d -------- \n", ri);
        //     printf("before: swapping index %d(%d) with %d(%d)\n", i * N + j, d_solutions[i * N + j],  i * N + ri, d_solutions[i * N + ri]);
        // }

        swap(&d_solutions[i * N + j], &d_solutions[i * N + ri]);

        // if (i == 0) {
        //     printf("after: index %d(%d) with %d(%d)\n", i * N + j, d_solutions[i * N + j],  i * N + ri, d_solutions[i * N + ri]);
        // }
        
        cost += d_distances[d_solutions[i * N + (j - 1)] * N + d_solutions[i * N + j]];
    }

    // Add cost between first and last
    cost += d_distances[d_solutions[i * N] * N + d_solutions[i * N + (N - 1)]];

    d_costs[i] = cost;

    // if (i == 100) {
    //     print_vec_int(d_solutions, N);
    //     printf("cost: %f\n", d_costs[i]);
    // }
}

int main() {
    // Variable declaration
    int N, min_cost_pos;
    // int SOLUTIONS = 100000;
    int SOLUTIONS = 1024;
    double min_cost;
    point p;
    std::cin >> N;
    thrust::host_vector<point> h_points(N);
    thrust::device_vector<double> d_distances(N * N);
    thrust::device_vector<double> d_costs(SOLUTIONS);
    thrust::device_vector<int> d_solutions(SOLUTIONS * N);
    thrust::device_vector<double>::iterator min_cost_iter;
    // best_cost = numeric_limits<double>::max();

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

    // Find smallest cost for best solution
    min_cost_iter = thrust::min_element(d_costs.begin(), d_costs.end());
    min_cost_pos = min_cost_iter - d_costs.begin();
    min_cost = *min_cost_iter;

    std::cout << "min cost: " << min_cost << " at index: " << min_cost_pos << std::endl;

    std::cout << "best solution: [ ";
    for (int i = min_cost_pos * N; i < (min_cost_pos * N) + N; i++) {
        std::cout << d_solutions[i] << " ";
    }
    std::cout << "]\n";

    std::cout << std::endl;

    // d = chrono::duration_cast<chrono::microseconds>(end - start).count();
    // std::cerr << d << " μs" << endl;
    // std::cout << std::fixed;
    // std::cout << setprecision(5);
    // std::cout << path_dist(best_sol, points) << " 0" << std::endl;

    // std::cout << setprecision(0);
    // for (int i = 0; i < best_sol.size(); i++) {
    //     std::cout << best_sol[i] << " ";
    // }
    // std::cout << endl;
}