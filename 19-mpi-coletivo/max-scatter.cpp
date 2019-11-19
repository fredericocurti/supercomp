#include <vector>
#include <algorithm>

#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/vector.hpp>
#include <math.h>

namespace mpi = boost::mpi;

int main() {
    mpi::environment env;
    mpi::communicator world;

    std::vector<int> a(10);
    std::vector<int> part;

    if (world.rank() == 0) {    
        for (int i = 0; i < a.size(); i++) {
            a[i] = i;
        }

        std::vector<std::vector<int> > scatter_data(world.size());
        int part_size = ceil(10.0 / world.size());
        for (int i = 0; i < a.size(); i += part_size) {
            scatter_data[i/part_size] = std::vector<int>(a.begin() + i, min(a.begin() + i + part_size, a.end()));
        }

        mpi::scatter(world, scatter_data, part, 0);
    } else {
        mpi::scatter(world, part, 0);
    }
    std::cout << part.size() << "\n";

    std::vector<int> partials(world.size());
    auto m = std::max_element(part.begin(), part.end());
    mpi::gather(world, *m, partials, 0);
    
    if(world.rank() == 0)
        std::cout << "Max " << *std::max_element(partials.begin(), partials.end()) << "\n"; 

}