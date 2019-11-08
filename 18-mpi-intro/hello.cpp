/*
 * fonte: https://www.boost.org/doc/libs/1_67_0/doc/html/mpi/tutorial.html
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <string>
namespace mpi = boost::mpi;

int main(int argc, char* argv[])
{
  mpi::environment env(argc, argv);
  mpi::communicator world;

  std::cout << "I am process " << world.rank() << " of " << world.size()
            << "." << std::endl;
  
  if (world.rank() == 0) {
    world.send(1, 0, std::string("Olá 1!"));
  } else {
    std::string res;
    auto st = world.recv(0, 0, res);
    std::cout << "Recebido de " << st.source() << ":" << res << ";\n";
  }

  return 0;
}
