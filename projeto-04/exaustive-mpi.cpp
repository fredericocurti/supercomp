#include <iostream>
#include <tuple>
#include <vector>
#include <limits>
#include <inttypes.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>
#include <algorithm>
#include <chrono>
#include <iomanip>  
#include <iostream>
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <string>
#include <map>
#include "aux.hpp"

namespace mpi = boost::mpi;
using namespace std::chrono;
using namespace std;
typedef map<char, double> point;

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

double dist(point p1, point p2) {
    return sqrt(pow(p1['x'] - p2['x'], 2) + pow(p1['y'] - p2['y'], 2));
}

double path_dist(vector<double> seq, vector<point> points) {
    double d = dist(points[seq.back()], points[seq[0]]);
    for (int i = 0; i < seq.size() - 1; i++) {
        d += dist(points[seq[i]], points[seq[i+1]]);
    }
    return d;
}

double* backtrack(
    vector<point> &points, double idx, double curr_cost,
    vector<double> &curr_sol, double *best_cost,
    vector<double> &best_seq, vector<bool> &usado,
    vector<double> &distances, int N, mpi::communicator world) {
        
    if (idx == points.size()) {
        curr_cost += distances[curr_sol[0] * N + curr_sol.back()];
        if (curr_cost < *best_cost) {
            best_seq = curr_sol;
            *best_cost = curr_cost;
        }
        return best_cost;
    }

    for (int i = 0; i < points.size(); i++) {
        if (usado[i] == false) {
            usado[i] = true;
            curr_sol[idx] = i;
            double new_cost = curr_cost + distances[curr_sol[idx-1] * N + curr_sol[idx]];

            if (idx == 1) { // only the first depth of recursion calls
                if (i % world.size() == world.rank()) {
                    best_cost = backtrack(points, idx+1, new_cost, curr_sol, best_cost, best_seq, usado, distances, N, world);
                }
            } else {
                best_cost = backtrack(points, idx+1, new_cost, curr_sol, best_cost, best_seq, usado, distances, N, world);
            }

            usado[i] = false;
            curr_sol[idx] = -1;
        }
    }

    return best_cost;
}

int main(int argc, char *argv[]) {
    mpi::environment env{argc, argv};
    mpi::communicator world;
    int N, best_index;
    double d;
    double best_cost = numeric_limits<double>::max();
    vector<point> points;
    vector<bool> usado;
    vector<double> curr_sol;
    vector<double> best_sol;
    vector<double> distances; /** distances array [i * N + j] */
    chrono::high_resolution_clock::time_point start, end;
    vector<double> best_costs(world.size());
    vector<vector<double>> best_sols(world.size());

    MASTER
        N = read_points(points); /** Amount of points */
        points.resize(N);
        usado.resize(N, false);
        curr_sol.resize(N, 0);
        best_sol.resize(N, -1);
        distances.resize(N * N);
        
        /** Precompute distances in master */
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                distances[i * N + j] = dist(points[i], points[j]);
            }
        }

        curr_sol[0] = 0;
        usado[0] = true;

        /* Start measuring time */
        start = chrono::high_resolution_clock::now();
    END

    mpi::broadcast(world, N, 0);
    mpi::broadcast(world, points, 0);
    mpi::broadcast(world, usado, 0);
    mpi::broadcast(world, curr_sol, 0);
    mpi::broadcast(world, best_sol, 0);
    mpi::broadcast(world, distances, 0);
    
    backtrack(points, 1, 0, curr_sol, &best_cost, best_sol, usado, distances, N, world);

    mpi::gather(world, best_cost, best_costs, 0);
    mpi::gather(world, best_sol, best_sols, 0);

    MASTER 
        auto iterator = min_element(best_costs.begin(), best_costs.end());
        best_cost = *iterator;
        best_index = iterator - best_costs.begin();
        best_sol = best_sols[best_index];

        end = chrono::high_resolution_clock::now();
        d = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        std::cerr << d << " ms" << endl;

        std::cout << std::fixed << setprecision(5);
        std::cout << path_dist(best_sol, points) << " 1" << std::endl;

        std::cout << setprecision(0);
        for (int i = 0; i < best_sol.size(); i++) {
            std::cout << best_sol[i] << " ";
        }
        std::cout << endl;
    
    END
}