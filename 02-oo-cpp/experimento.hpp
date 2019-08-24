#ifndef EXEMPLO_H
#define EXEMPLO_H
#include <vector>
#include <utility>

class Experimento {
    // variáveis declaradas aqui são privadas por padrão
    ;
    public:
        Experimento(void);
        std::vector<double> gera_entrada(int);
        std::pair<double, double> run(void);
        std::vector<double> v; /* Vetor gerado */
        double duration();
        double d; /* Duração */
        int n;
        virtual void experiment_code()=0;
        operator double();
        bool operator < (Experimento*);
        bool operator < (double);    
};  

#endif