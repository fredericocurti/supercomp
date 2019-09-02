#include <vector>
#include <utility>
#include <string>

class Parser {
    public:
        Parser();
        /* largura do campo */
        double w;

        /* altura do campo */
        double h; 

        /* coeficiente de atrito dinâmico */
        double mu_d; 

        /* quantidade de retângulos */
        double N; 

        /* Vetor de retangulos */
        std::vector<std::vector<double>> rects; 

        /* tamanho do passo da simulação */
        double dt; 

        /* a cada print_freq iterações printa o estado da simulação na saída padrão */
        int print_freq; 

        /* número máximo de iterações */
        int max_iter;

        /* printa atributos da instância */
        void print(int); 
};