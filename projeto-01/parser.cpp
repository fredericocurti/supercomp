#include <iostream>
#include <fstream>
#include <iomanip>
#include "parser.hpp"
using namespace std;

Parser::Parser(void) {
    double v;
    cin >> w;
    cin >> h;
    cin >> mu_d;
    cin >> N;
    for (int i = 0; i < N; i++) {
        std::vector<double> rect;
        for (int j = 0; j < 7; j++) {
            cin >> v; 
            rect.push_back(v);
        }

        rects.push_back(rect);
        // cout << "-> Rect[" << i << "]: ";
        // for (int j = 0; j < 7; j++) { 
        //     cout << rects[i][j] << " ";
        // }
        // cout << endl;
    }
    cin >> dt;
    cin >> print_freq;
    cin >> max_iter;
    // cout << "[Parser] w: " << w << " h: " << h << " mu_d: " << mu_d << endl;
    // cout << "[Parser] dt: " << dt << " print_freq: " << print_freq << " max_iter: " << max_iter << endl;
    std::cout << std::setprecision(5) << std::fixed;
}

void Parser::print(int iter) {
    cout << iter << endl;
    for (int i = 0; i < N; i++) {
        cout << rects[i][3] << " " << rects[i][4] << " " << rects[i][5] << " " << rects[i][6] << endl;
    }
    cout << "--------" << endl;
}