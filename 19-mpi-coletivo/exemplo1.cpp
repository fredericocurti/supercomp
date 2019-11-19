#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;
    
    if (world.rank() == 0) {
        std::string s[2];
        auto r1 = world.irecv(1, 10, s[0]);
        auto r2 = world.irecv(2, 20, s[1]);
        
        r1.wait();
        std::cout << s[0] << "\n" << std::endl;

        r2.wait();        
        std::cout << s[1] << '\n';
    } else if (world.rank() == 1) {
        std::string s = "Hello, world!";
        sleep(2);
        world.send(0, 10, s);
        std::cout << "Fim rank 1 " << std::endl;
    } else if (world.rank() == 2) {
        std::string s = "Hello, moon!";
        sleep(1);
        world.send(0, 20, s); 
        std::cout << "Fim rank 2 " << std::endl;
    }
}
