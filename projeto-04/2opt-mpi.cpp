#include <iostream>
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/vector.hpp>
#include <string>
#include <vector>
#include <limits>
#include <inttypes.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include "aux.hpp"
#include <random>

#define SOLUTIONS 100000

namespace mpi = boost::mpi;
namespace chrono = std::chrono;

/** Returns distance between two points */
double dist(point p1, point p2) {
    return sqrt(pow(p1['x'] - p2['x'], 2) + pow(p1['y'] - p2['y'], 2));
}

/** Swaps two integer elements by reference */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

/** Reads stdin and insert into points, returns the amount of points read */
int read_points(std::vector<point> &points) {
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        point p;
        std::cin >> p['x'];
        std::cin >> p['y'];
        points.push_back(p);
    }
    return N;
}

double calculate_sol_cost(std::vector<int> &solution, std::vector<double> &distances, int N) {
    double c = 0;
    for (int i = 1; i < solution.size(); i++) {
        c += distances[solution[i - 1] * N + solution[i]];
    }
    c += distances[solution[0] * N + solution[N - 1]];
    return c;
}

int main(int argc, char *argv[]) {
    mpi::environment env{argc, argv};
    mpi::communicator world;
    int N, SOLUTIONSPERPROCESS, ri;
    std::vector<double> distances; /** distances array [i * N + j] */
    std::vector<std::vector<int>> solutions(world.size());
    std::vector<double> costs(world.size());
    chrono::high_resolution_clock::time_point start, end;
    
    SOLUTIONSPERPROCESS = SOLUTIONS / world.size();

    MASTER
        std::vector<point> points; /** Points array */
        N = read_points(points); /** Amount of points */
        distances.resize(N * N);
        
        /** Precompute distances in master */
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                distances[i * N + j] = dist(points[i], points[j]);
            }
        }

        /* Start measuring time */
        start = chrono::high_resolution_clock::now();
    END

    mpi::broadcast(world, N, 0);

    WORKER
        distances.resize(N * N);
    END

    mpi::broadcast(world, distances, 0);

    /* initialize random seed */
    srand(world.rank() * time(NULL));
    
    /* Generate SOLUTIONS PER PROCESS SOLUTIONS */
    double best_cost = std::numeric_limits<double>::max();
    std::vector<int> best_solution;

    for (int i = 0; i < SOLUTIONS; i++) {
        std::vector<int> solution;    
        double current_cost = 0;
        double swap_cost = 0;

        /* Fill solutions with sequential points [0-N] */
        for (int i = 0; i < N; i++) {
            solution.push_back(i);
        }

        /* generate random solution */
        for (int j = 1; j < N; j++) {
            ri = (int) rand() % (N - j) + j;
            swap(&solution[j], &solution[ri]);
        }

        current_cost = calculate_sol_cost(solution, distances, N);

        /* Swap again for 2opt */
        for (int j = 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                swap(&solution[j], &solution[k]);
                swap_cost = calculate_sol_cost(solution, distances, N);
                if (swap_cost > current_cost) {         /* undo */
                    swap(&solution[k], &solution[j]);
                } else {                                /* keep the solution */
                    current_cost = swap_cost;
                }
            }
        }

        /* Check if solution is the best and store it */
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_solution = solution;
        }
    }

    // std::cout << "WORKER[" << world.rank() << "]" << " BEST COST: " << best_cost << std::endl;
    mpi::gather(world, best_solution, solutions, 0);
    mpi::gather(world, best_cost, costs, 0);

    MASTER
        //std::cout << "WORKER[" << world.rank() << "]" << std::endl;
        auto smallest = std::min_element(costs.begin(), costs.end());

        /* Stop measuring time */
        end = chrono::high_resolution_clock::now();
        double t = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        /* Output on specified format */
        std::cerr << t << " ms" << std::endl;
        std::cout << std::fixed << std::setprecision(5);
        std::cout << *smallest << " 0" << std::endl;

        for (int i = 0; i < N; i++) {
            std::cout << solutions[smallest - costs.begin()][i] << " ";
        }
        
        std::cout << std::endl;
    END

    return 0;
}