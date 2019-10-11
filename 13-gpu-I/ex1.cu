#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>
#include <limits>

static double inf = std::numeric_limits<double>::max();

using namespace std::chrono;

int main() {
    thrust::host_vector<double> host;
    std::string line;
    double s;
    high_resolution_clock::time_point start, end;
    
    while (!std::cin.eof()) {
        std::cin >> s;
        host.push_back(s);
    }

    /* na linha abaixo os dados são copiados
       para GPU */
    start = high_resolution_clock::now();
    thrust::device_vector<double> dev(host);    
    end = high_resolution_clock::now();
    double d = duration_cast<milliseconds>(end - start).count();

    std::cerr << "ASSIGN AND COPY TO GPU:" << d << " ms" << std::endl;
    
    // printf("Device vector: ");
    // for (auto i = dev.begin(); i != dev.end(); i++) {
    //     std::cout << *i << " "; // este acesso é lento! -- GPU
    // }

    start = high_resolution_clock::now();
    double sum = thrust::reduce(dev.begin(), dev.end(), 0, thrust::plus<double>());
    double avg = sum/host.size();
    double sum_last_year = thrust::reduce(dev.end() - 365, dev.end(), 0, thrust::plus<double>());
    double avg_last_year = sum_last_year/365;
    double max = thrust::reduce(dev.begin(), dev.end(), 0, thrust::maximum<double>());
    double min = thrust::reduce(dev.begin(), dev.end(), inf, thrust::minimum<double>());
    double max_ly = thrust::reduce(dev.end() - 365, dev.end(), 0, thrust::maximum<double>());
    double min_ly = thrust::reduce(dev.end() - 365, dev.end(), inf, thrust::minimum<double>());
    end = high_resolution_clock::now();
    d = duration_cast<nanoseconds>(end - start).count();
    std::cerr << "OPERATIONS IN GPU:" << d << " ns" << std::endl;

    std::cout << "max: " << max << std::endl;
    std::cout << "min: " << min << std::endl;
    std::cout << "max_ly: " << max_ly << std::endl;
    std::cout << "min_ly: " << min_ly << std::endl;
    std::cout << "avg: " << avg << std::endl;
    std::cout << "avg_ly: " << avg_last_year << std::endl;
    std::cout << "sum: " << sum << std::endl;

    start = high_resolution_clock::now();
    sum = thrust::reduce(thrust::host, host.begin(), host.end(), 0, thrust::plus<double>());
    avg = sum/host.size();
    sum_last_year = thrust::reduce(thrust::host, host.end() - 365, host.end(), 0, thrust::plus<double>());
    avg_last_year = sum_last_year/365;
    max = thrust::reduce(thrust::host, host.begin(), host.end(), 0, thrust::maximum<double>());
    min = thrust::reduce(thrust::host, host.begin(), host.end(), inf, thrust::minimum<double>());
    max_ly = thrust::reduce(thrust::host, host.end() - 365, host.end(), 0, thrust::maximum<double>());
    min_ly = thrust::reduce(thrust::host, host.end() - 365, host.end(), inf, thrust::minimum<double>());
    end = high_resolution_clock::now();
    d = duration_cast<nanoseconds>(end - start).count();
    std::cerr << "OPERATIONS IN CPU:" << d << " ns" << std::endl;

    std::cout << "max: " << max << std::endl;
    std::cout << "min: " << min << std::endl;
    std::cout << "max_ly: " << max_ly << std::endl;
    std::cout << "min_ly: " << min_ly << std::endl;
    std::cout << "avg: " << avg << std::endl;
    std::cout << "avg_ly: " << avg_last_year << std::endl;
    std::cout << "sum: " << sum << std::endl;

}
