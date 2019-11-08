#include <boost/mpi.hpp>
#include <iostream>
#include <string>
namespace mpi = boost::mpi;

int main(int argc, char* argv[])
{
    int N = 1000;
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
    }
    
    auto max = *std::max_element(slice.begin(), slice.end());
    std::cout << "process " << world.rank() << " max: " << max << "\n";

    if (world.rank() > 0) {
        world.send(0, 0, max);
    } else {
        for (int i = 1; i < P; i++) {
            int recv_max;
            std::cout << "alo\n";
            world.recv(i, 0, recv_max);
            if (recv_max > max) {
                max = recv_max;
            }
        }

        std::cout << "max found by" << world.rank() << "was " << max << "\n";
    }

}