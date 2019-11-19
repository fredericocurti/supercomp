#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  boost::mpi::environment env{argc, argv};
  boost::mpi::communicator world;
  std::vector<std::string> v;
  
    std::string *s = new std::string[2];
  if (world.rank() == 0) {
        std::vector<std::string> v{"Hello, world!", "Hello, moon!",
    "Hello, sun!", "HH", "DDD", "AA"};
        boost::mpi::scatter(world, v, s, 2, 0);
  } else {
      boost::mpi::scatter(world, v, s, 2, 0);
  }
  
  
  std::cout << world.rank() << ": " << s[0] << " " << s[1] << '\n';
}
