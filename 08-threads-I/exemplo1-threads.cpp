#include <thread>
#include <iostream>


void funcao_rodando_em_paralelo(int a, int *b, int tid) {
    std::cout << "Thread: " << tid << "a=" << a << std::endl;
    *b = 5;
}

int main() {
    int b = 10;
    int tid = 0;
    unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
    std::thread *threads = new std::thread[concurentThreadsSupported];
    std::cout << "Threads supported:" << concurentThreadsSupported << std::endl;
    
    // Os argumentos em seguida são passados diretamente
    // para a função passada no primeiro argumento.
    for (int i = 0; i < concurentThreadsSupported; i++) {
        threads[i] = std::thread(funcao_rodando_em_paralelo, 15, &b, tid);
        tid++;
        std::cout << "Antes do join b=" << b << std::endl;
    }

    for (int i = 0; i < concurentThreadsSupported; i++) {
        threads[i].join();
    }
    
    std::cout << "Depois do join b=" << b << std::endl;
}
