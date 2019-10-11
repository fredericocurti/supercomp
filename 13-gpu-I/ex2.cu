#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>
#include <limits>

static double inf = std::numeric_limits<double>::max();

using namespace std::chrono;

int main() {
    double s;
    thrust::host_vector<double> host_AAPL;
    thrust::host_vector<double> host_MSFT;
    std::string line;
    high_resolution_clock::time_point start, end;
    
    while (!std::cin.eof()) {
        std::cin >> s;
        host_AAPL.push_back(s);
        std::cin >> s;
        host_MSFT.push_back(s);
    }

    /* na linha abaixo os dados são copiados
       para GPU */
    start = high_resolution_clock::now();
    thrust::device_vector<double> dev_AAPL(host_AAPL);    
    thrust::device_vector<double> dev_MSFT(host_MSFT);
    thrust::device_vector<double> dev(host_AAPL.size());
    end = high_resolution_clock::now();
    double d = duration_cast<milliseconds>(end - start).count();
    std::cerr << "ASSIGN AND COPY TO GPU:" << d << " ms" << std::endl;
    
    // printf("Device vector: ");
    // for (auto i = dev.begin(); i != dev.end(); i++) {
    //     std::cout << *i << " "; // este acesso é lento! -- GPU
    // }

    start = high_resolution_clock::now();
    thrust::transform(dev_AAPL.begin(), dev_AAPL.end(), dev_MSFT.begin(), dev.begin(), thrust::minus<double>());
    double avg = thrust::reduce(dev.begin(), dev.end(), 0, thrust::plus<double>());
    avg = avg/host_AAPL.size();

    std::cout << avg << std::endl;

    return 0;
}
