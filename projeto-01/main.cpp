#include "parser.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std::chrono;
using namespace std;

/**
 * Relação retângulo na array
 * rec[0] = m - massa
 * rec[1] = wr - largura
 * rec[2] = hr - altura
 * rec[3] = posicao x
 * rec[4] = posicao y
 * rec[5] = velocidade vx
 * rec[6] = velocidade vy
 */

int main() {
    Parser *p = new Parser();
    int i, j, iter = 0;
    int stable = 0;
    double d, theta, V, mt, g = 9.8; /* gravity */ 
    double mu_dg = p->mu_d * g;
    std::vector<std::vector<double>> pr; /* copy of rects from previous iteration */ 
    high_resolution_clock::time_point start, end;
    
    start = high_resolution_clock::now();
    while (iter < p->max_iter && stable != p->N) {
        stable = 0; /* reseta contador de estabilizador */
        pr = p->rects; /* copia vetor */

        for (i = 0; i < p->N; i++) {
            /* mover retângulos */
            p->rects[i][3] = p->rects[i][3] + p->rects[i][5] * p->dt;
            p->rects[i][4] = p->rects[i][4] + p->rects[i][6] * p->dt;

            /* calcular |V| e theta se alguma das componentes de V são diferentes de zero */
            if (p->rects[i][5] == 0.0 && p->rects[i][6] == 0.0) {
                V = 0;
            } else {
                /* calcular novo |V| graças ao atrito */
                V = sqrt(pow(p->rects[i][5], 2) + pow(p->rects[i][6], 2));
                theta = atan2(p->rects[i][6], p->rects[i][5]);

                V -= mu_dg * p->dt;
                if (V <= 0.0) {
                    V = 0.0;
                }

                p->rects[i][5] = V * cos(theta);
                p->rects[i][6] = V * sin(theta);
            }

            /* colisões com a parede
            * colisão com a parede direita, inverte vx */
            if (p->rects[i][3] + p->rects[i][1] >= p->w) {
                // cout << "-> ["<< i <<"] collided with right wall on iter" << iter << endl;
                p->rects[i][5] *= -1;
                p->rects[i][3] = pr[i][3]; // Restaura posição de x pré colisao
            }

            // colisão com a parede esquerda
            if (p->rects[i][3] < 0) {
                // cout << "-> ["<< i <<"] collided with left wall on iter " << iter << endl;
                p->rects[i][5] *= -1;
                p->rects[i][3] = pr[i][3]; // Restaura posição de x pré colisao
            }

            /* colisão com a parede de cima */
            if (p->rects[i][4] >= p->h) {
                // cout << "-> ["<< i <<"] collided with top wall on iter" << iter << endl;
                p->rects[i][6] *= -1;
                p->rects[i][4] = pr[i][4]; // Restaura posição de y pré colisao
            }

            /* colisão com a parede de baixo */
            if (p->rects[i][4] - p->rects[i][2] < 0) {
                // cout << "-> ["<< i <<"] collided with bottom wall on iter" << iter << endl;
                p->rects[i][6] *= -1;
                p->rects[i][4] = pr[i][4]; // Restaura posição de y pré colisao
            }

            /* verificar se estabilizou -> |v| dos N corpos < 0,0001 m/s */
            if (V < 0.0001) {
                stable++;
            }
        }

        /* colisão com outros retângulos */
        for (i = 0; i < p->N; i++) {
            for (j = i + 1; j < p->N; j++) {
                if (p->rects[j][3] + p->rects[j][1] > p->rects[i][3] &&
                    p->rects[j][4] + p->rects[j][2] > p->rects[i][4] &&
                    p->rects[i][3] + p->rects[i][1] > p->rects[j][3] &&
                    p->rects[i][4] + p->rects[i][2] > p->rects[j][4] && 
                    i != j) {
                        // cout << "-> ["<< i <<"] collided with [" << j << "]" << endl;
                        mt = p->rects[i][0] + p->rects[j][0];

                        /* Move r1 */
                        p->rects[i][5] = (pr[i][5] * (p->rects[i][0] - p->rects[j][0]) + (2 * pr[j][5] * p->rects[j][0])) / mt;
                        p->rects[i][6] = (pr[i][6] * (p->rects[i][0] - p->rects[j][0]) + (2 * pr[j][6] * p->rects[j][0])) / mt;

                        /* Move r2 */
                        p->rects[j][5] = (pr[j][5] * (p->rects[j][0] - p->rects[i][0]) + (2 * pr[i][5] * p->rects[i][0])) / mt;
                        p->rects[j][6] = (pr[j][6] * (p->rects[j][0] - p->rects[i][0]) + (2 * pr[i][6] * p->rects[i][0])) / mt;

                        /* Reseta a posição para uma posição válida */
                        p->rects[i][3] = pr[i][3];
                        p->rects[i][4] = pr[i][4];
                        p->rects[j][3] = pr[j][3];
                        p->rects[j][4] = pr[j][4];
                    }
            }
        }
            
        /* Printa o estado da simulação a cada print_freq iterações */
        if (iter % p->print_freq == 0) {
            p->print(iter);
        }

        iter++;
    }

    /* Printa tempo na saida de erros */
    end = high_resolution_clock::now();
    d = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cerr << d << endl;

    if (stable == p->N) {
        // cout << "stable:" << stable << endl;
    }

    return 0;
}

