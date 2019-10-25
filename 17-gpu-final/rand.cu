#include "curand.h"
#include "curand_kernel.h"
#include "math.h"

#include <thrust/device_vector.h>
#include <iostream>

__global__ void gerar(int *out, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= n) return;

    curandState st;
    curand_init(0, i, 0, &st);

    // números entre 10 e 40
    int temp = 0;
    for (int k = 0; k < 500; k++) {
        temp += (int) (30 * curand_uniform(&st) + 10);;
    }
    out[i] = temp;

}

int main() {
    thrust::device_vector<int> nums(100000);

    int nblocks = ceil(nums.size() / 1024);

    gerar<<<nblocks, 1024>>>(thrust::raw_pointer_cast(nums.data()), nums.size());

    for (int i =0 ; i< 10; i++) {
        std::cout << nums[i] << "\n";
    }

}
