#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
namespace mpi = boost::mpi;

int main(int argc, char* argv[]) {
    mpi::environment env(argc, argv);
    mpi::communicator world;
    
    if (world.rank() == 0) {
        int data;
        world.send(1, 1, 100);
        world.recv(1, 0, data);
        std::cout << "Received " << data << " from 1 \n";
    } else if (world.rank() == 1) { // faltou restrigir com essa condicao
        int data;
        world.send(0, 0, 200);
        world.recv(0, 1, data);
        std::cout << "Received " << data << " from 0 \n";
    }
    return 0;
}