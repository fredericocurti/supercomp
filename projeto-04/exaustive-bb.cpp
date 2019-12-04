#include <iostream>
#include <tuple>
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

typedef struct {
    double x;
    double y;
} point;

using namespace std;
using namespace std::chrono;

double dist(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
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
    vector<double> &best_seq, vector<bool> &usado) {

    if (curr_cost > *best_cost) {
        return best_cost;
    }

    if (idx == points.size()) {
        curr_cost += dist(points[curr_sol[0]], points[curr_sol.back()]);
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
            double new_cost = curr_cost + dist(points[curr_sol[idx-1]], points[curr_sol[idx]]);
            best_cost = backtrack(points, idx+1, new_cost, curr_sol, best_cost, best_seq, usado);
            usado[i] = false;
            curr_sol[idx] = -1;
        }
    }

    return best_cost;
}

int main() {
    int N;
    double d;
    point p;
    vector<point> points;
    vector<bool> usado;
    vector<double> curr_sol;
    vector<double> best_sol;
    high_resolution_clock::time_point start, end;
    double best_cost = numeric_limits<double>::max();

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> p.x;
        cin >> p.y;
        points.push_back(p);
        curr_sol.push_back(-1);
        best_sol.push_back(-1);
        usado.push_back(false);
    }

    curr_sol[0] = 0;
    usado[0] = true;

    start = high_resolution_clock::now();

    backtrack(points, 1, 0, curr_sol, &best_cost, best_sol, usado);

    end = high_resolution_clock::now();
    d = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    std::cerr << d << " ms" << endl;
    std::cout << std::fixed;
    std::cout << setprecision(5);
    std::cout << path_dist(best_sol, points) << " 1" << std::endl;

    std::cout << setprecision(0);
    for (int i = 0; i < best_sol.size(); i++) {
        std::cout << best_sol[i] << " ";
    }
    std::cout << endl;
}