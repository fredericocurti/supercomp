#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>

#include <iostream>

struct acesso_direto {
    double *pointer_gpu;

    acesso_direto(double *pointer_gpu): pointer_gpu(pointer_gpu) {}

    __host__ __device__
    double operator() (int i) {
        return pointer_gpu[i] + 5;
    }
};


int main() {
    thrust::device_vector<double> vec(1000), vec_out(1000);
    thrust::sequence(vec.begin(), vec.end());
    auto index = thrust::make_counting_iterator(0);
    
    acesso_direto op(thrust::raw_pointer_cast(vec.data()));
    thrust::transform(index, index + vec.size(), vec_out.begin(), op);

    for(int i = 0; i < 1000; i++) {
        std::cout << vec_out[i] << std::endl;
    }


}