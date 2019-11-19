#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <string>
#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;
    if (world.rank() == 0) {
        std::string s;
        auto r = world.irecv(1, 0, s);
        r.wait();
        std::cout << s << "\n";
    }
    else if (world.rank() == 1) {
        sleep(3);
        std::string s = "Hello async!";
        world.send(0, 0, s);
    }
}
