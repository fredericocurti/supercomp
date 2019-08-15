#ifndef EXEMPLO_H
#define EXEMPLO_H

class Experimento {
    // variáveis declaradas aqui são privadas por padrão
    ;
    public:
        Experimento(void);
        double* gera_entrada(int);
        double duration();
        void run(void);
        double d; /* Duração */
        double* v; /* Vetor gerado */
        int n;
        virtual void experiment_code()=0;
        operator double();
        bool operator < (Experimento*);
        bool operator < (double);    
};  

#endif