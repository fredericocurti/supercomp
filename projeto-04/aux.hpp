#include <iostream>
#include <vector>
#include <map>
#include <boost/serialization/map.hpp>

#define MASTER if (world.rank() == 0) {
#define WORKER if (world.rank() > 0) {
#define WORKER_N(N) if (world.rank() == N) {
#define END }

typedef std::map<char, double> point;

void print_vector(std::vector<double> v) {
    std::cout << "[ ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "]" << std::endl;
}

void print_vector(std::vector<point> v) {
    std::cout << "[ ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << "(" << v[i]['x'] << ", " << v[i]['y'] << ") ";
    }
    std::cout << "]" << std::endl;
}

void print_vector(std::vector<int> v) {
    std::cout << "[ ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "]" << std::endl;
}

void print_vector(std::vector<std::vector<int> > v) {
    std::cout << "[";
    for (int i = 0; i < v.size(); i++) {
        std::cout << "[";
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << v[i][j] << " ";    
        }
        std::cout << (i == v.size() -1 ? "]" : "], ");
    }
    std::cout << "]" << std::endl;
}