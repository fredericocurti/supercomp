#include "log.hpp"
#include "pow3.hpp"
#include "pow3mult.hpp"
#include "sqrt.hpp"
#include "sum.hpp"
#include <iostream>
#include <vector>
#include <tuple>

int main() {
    int i, j, n = 1000;
    double avg_time;
    std::tuple<std::string, double> min_time, max_time;
    Experimento *log, *pow, *pow3mult, *sqrt, *sum;

    min_time = std::make_tuple("",INT32_MAX);
    max_time = std::make_tuple("",0);

    for (i = 0; i < 5; i++) {
    std::cout << "--------- n: " << n << " ---------\n";
        avg_time = 0;
        for (j = 0; j < 10; j++) {
            log = new ExperimentoLog();
            log->gera_entrada(n);
            log->run();
            avg_time += log->duration();
        }
        avg_time /= 10;

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "log";
            std::get<1>(max_time) = avg_time;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "log";
            std::get<1>(min_time) = avg_time;
        }

        std::cout << "avg_time for log: " << avg_time << "\n";
        

        avg_time = 0;
        for (j = 0; j < 10; j++) {
            pow = new ExperimentoPow();
            pow->gera_entrada(n);
            pow->run();
            avg_time += pow->duration();
        }
        avg_time /= 10;
        std::cout << "avg_time for pow: " << avg_time << "\n";


        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "pow";
            std::get<1>(max_time) = avg_time;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "pow";
            std::get<1>(min_time) = avg_time;
        }


        avg_time = 0;
        for (j = 0; j < 10; j++) {
            pow3mult = new ExperimentoPow3Mult();
            pow3mult->gera_entrada(n);
            pow3mult->run();
            avg_time += pow3mult->duration();
        }
        avg_time /= 10;
        std::cout << "avg_time for pow3mult: " << avg_time << "\n";


        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "pow3mult";
            std::get<1>(max_time) = avg_time;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "pow3mult";
            std::get<1>(min_time) = avg_time;
        }

        avg_time = 0;
        for (j = 0; j < 10; j++) {
            sqrt = new ExperimentoSqrt();
            sqrt->gera_entrada(n);
            sqrt->run();
            avg_time += sqrt->duration();
        }
        avg_time /= 10;
        std::cout << "avg_time for sqrt: " << avg_time << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "sqrt";
            std::get<1>(max_time) = avg_time;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "sqrt";
            std::get<1>(min_time) = avg_time;
        }

        avg_time = 0;
        for (j = 0; j < 10; j++) {
            sum = new ExperimentoSum();
            sum->gera_entrada(n);
            sum->run();
            avg_time += sum->duration();
        }
        avg_time /= 10;
        std::cout << "avg_time for sum: " << avg_time << "\n";

        if (avg_time > std::get<1>(max_time)) {
            std::get<0>(max_time) = "sum";
            std::get<1>(max_time) = avg_time;
        }

        if (avg_time < std::get<1>(min_time)) {
            std::get<0>(min_time) = "sum";
            std::get<1>(min_time) = avg_time;
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