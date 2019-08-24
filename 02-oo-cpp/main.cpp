#include "log.hpp"
#include "pow3.hpp"
#include "pow3mult.hpp"
#include "sqrt.hpp"
#include "sum.hpp"
#include "sumavx.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

int main() {
    int i, j, n = 1000;
    double avg_time;
    std::tuple<std::string, double> min_time, max_time;
    std::vector<std::pair<double, double> > results;
    Experimento *log, *pow, *pow3mult, *sqrt, *sum, *sumavx;

    min_time = std::make_tuple("",INT32_MAX);
    max_time = std::make_tuple("",0);

    for (i = 0; i < 5; i++) {
        std::cout << "--------- n: " << n << " ---------\n";

        /* Log */
        log = new ExperimentoLog();
        log->gera_entrada(n);
        results.push_back(log->run());
        std::cout << "avg_time for log: " << results[0].first << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "log";
            std::get<1>(max_time) = results[0].first;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "log";
            std::get<1>(min_time) = results[0].first;
        }

        /* Pow */    
        pow = new ExperimentoPow();
        pow->gera_entrada(n);
        results.push_back(pow->run());
        std::cout << "avg_time for pow: " << results[1].first << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "pow";
            std::get<1>(max_time) = results[1].first;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "pow";
            std::get<1>(min_time) = results[1].first;
        }


        /* Pow3Mult */
        pow3mult = new ExperimentoPow3Mult();
        pow3mult->gera_entrada(n);
        results.push_back(pow3mult->run());
        std::cout << "avg_time for pow3mult: " << results[2].first << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "pow3mult";
            std::get<1>(max_time) = results[2].first;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "pow3mult";
            std::get<1>(min_time) = results[2].first;
        }

        /* Sqrt */
        sqrt = new ExperimentoSqrt();
        sqrt->gera_entrada(n);
        results.push_back(sqrt->run());
        std::cout << "avg_time for sqrt: " << results[3].first << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "sqrt";
            std::get<1>(max_time) = results[3].first;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "sqrt";
            std::get<1>(min_time) = results[3].first;
        }

        /* Sum */
        sum = new ExperimentoSum();
        sum->gera_entrada(n);
        results.push_back(sum->run());
        std::cout << "avg_time for sum: " << results[4].first << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "sum";
            std::get<1>(max_time) = results[4].first;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "sum";
            std::get<1>(min_time) = results[4].first;
        }

        /* SumAVX */
        sumavx = new ExperimentoSumAvx();
        sumavx->gera_entrada(n);
        results.push_back(sumavx->run());
        std::cout << "avg_time for sumavx: " << results[5].first << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "sumavx";
            std::get<1>(max_time) = results[5].first;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "sumavx";
            std::get<1>(min_time) = results[5].first;
        }

        n *= 10;
    }

    /* Exercício overload double() */
    std::cout << "casting double: " << double(*sum) << "ms\n";

    /* Exercício overload < comparação */
    std::cout << "pow durou menos que sqrt?:" << (sqrt < pow == 1 ? "true" : "false") << "\n";

    /* Exercício pra ver se experimento durou menos de 0.1s */
    std::cout << "log durou menos que 0.1s:" << (double(*log) < 100 == 1 ? "true" : "false") << "\n";
    std::cout << "pow durou menos que 0.1s:" << (double(*pow) < 100 == 1 ? "true" : "false") << "\n";
    std::cout << "pow3mult durou menos que 0.1s:" << (double(*pow3mult) < 100 == 1 ? "true" : "false") << "\n";
    std::cout << "sqrt durou menos que 0.1s:" << (double(*sqrt) < 100 == 1 ? "true" : "false") << "\n";
    std::cout << "sum durou menos que 0.1s:" << (double(*sum) < 100 == 1 ? "true" : "false") << "\n";

    /* Exercício maior e menor tempo */
    std::cout << "experimento mais duradouro na média foi " << std::get<0>(max_time) << " com duração " << std::get<1>(max_time) << " ms\n";
    std::cout << "experimento mais curto na média foi " << std::get<0>(min_time) << " com duração " << std::get<1>(min_time) << "ms \n";
    return 0;
}