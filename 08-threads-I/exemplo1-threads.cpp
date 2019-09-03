#include <thread>
#include <iostream>

void funcao_rodando_em_paralelo(int a, int *b) {
    std::cout << "a=" << a << std::endl;
    *b = 5;
}


int main() {
    int b = 10;

    // Cria thread e a executa.
    // Primeiro argumento é a função a ser executada.
    
    // Os argumentos em seguida são passados diretamente
    // para a função passada no primeiro argumento.
    std::thread t1(funcao_rodando_em_paralelo, 15, &b);
    
    
    std::cout << "Antes do join b=" << b << std::endl;
    
    // Espera até que a função acabe de executar.
    t1.join();
    
    std::cout << "Depois do join b=" << b << std::endl;
}
