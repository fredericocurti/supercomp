#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

namespace mpi = boost::mpi;

int main(int argc, char* argv[])
{
    int N = 10;
    mpi::environment env(argc, argv);
    mpi::communicator world;
    std::vector<int> v(N);
    std::vector<int> slice;
    int P = world.size();
    int chunk = N / P;

    if (world.rank() == 0) {
        std::generate(v.begin(), v.end(), std::rand);
        slice = std::vector<int>(v.begin(), v.begin() + chunk);
        for (int i = 1; i < P; i++) {
            world.send(i, 0, std::vector<int>(&v[i * chunk], &v[(i + 1) * chunk]));
        }

    } else {
        world.recv(0, 0, slice);
        std::sort(slice.begin(), slice.end());
        world.send(0, 0, slice);
    }

    
    if (world.rank() == 0) {
        std::vector<int> sorted_slice;
        world.recv(1, 0, sorted_slice);
        v.clear();

        sort(slice.begin(), slice.end());
        std::merge(slice.begin(), slice.end(), sorted_slice.begin(), sorted_slice.end(), std::back_inserter(v));

        for (int i = 0; i < N; i++) {
            std::cout << v[i] << " ";
        }
        std::cout << "\n";
    }

}