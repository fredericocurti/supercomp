#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include <string>
namespace mpi = boost::mpi;

int main(int argc, char* argv[]) {
    mpi::environment env(argc, argv);
    mpi::communicator world;
    int word = 69;
    int recv_word;

    if (world.rank() == 0) {
        world.send(world.rank() + 1, 0, word);
        auto st = world.recv(world.size() - 1, 0, recv_word);
        std::cout << "Recebido de " << st.source() << ":" << recv_word << ";\n";

    } else { 
        auto status = world.recv(world.rank() - 1, 0, recv_word);
        std::cout << "Recebido de " << status.source() << ":" << recv_word << ";\n";
        if (world.rank() == world.size() - 1) {
            world.send(0, 0, recv_word);
        } else {
            world.send(world.rank() + 1, 0, recv_word);
        }
    }

    return 0;
}