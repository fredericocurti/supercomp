% 18 - Comunicação Coletiva e Assíncrona
% Super Computação 2019/2
% Igor Montagner, Luciano Soares 

Todas as comunicações feitas no curso até o momento foram *ponto-a-ponto* e *síncronas*, ou seja, sempre é necessário especificar para quem a mensagem será enviada e de quem ela será recebida e nossas funções *bloqueiam o programa até que terminem*. Em algumas situações, porém, é necessário fazer comunicação de *um-para-muitos* ou de *muitos-para-um*. Neste roteiro iremos exercitar este tipo de comunicação para tornar mais simples dois programas que fizemos anteriormente. Alguns exemplos de como usar estas funções podem ser vistos [neste link](https://theboostcpplibraries.com/boost.mpi-collective-data-exchange). 

# Parte 1 - mínimo e máximo usando comunicação coletiva

**Exercício**: Encontra o valor máximo de um vetor. Você pode gerá-lo randomicamente no processo 0.

1. Você deve usar *scatter* para distribuir as partes do vetor
2. Você deve usar *reduce* para encontrar o menor valor.

**Exercício**: Ordene um vetor usando *MPI*. 

1. Use *scatter* para distribuir as partes do vetor
1. Ordene cada pedaço usando `std::sort`
1. Use *gather* para receber no nó 0 os vetores ordenados
1. Faça um merge dos resultados

# Parte 2 - comunicação assíncrona

Comunicação assíncrona é usada em duas situações:

1. A ordem de recebimento/envio das mensagens não importa;
1. Desejamos iniciar o recebimento de uma mensagem grande enquanto realizamos outra tarefa.

## Chamadas `irecv` e `isend`

As chamadas `irecv` e `isend` são versões assíncronas da passagem de mensagens e retornam um objeto do tipo `boost::mpi::request`. Objetos deste tipo podem esperar a mensagem ser efetivada com o método `wait` e testar se já foram efetivados com `test`. Veja abaixo um exemplo de recebimento assíncrono de mensagem. Note que o código só bloqueia quando chamamos `r.wait()`.

```cpp
#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <string>
#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;
    if (world.rank() == 0) {
        std::string s;
        auto r = world.irecv(1, 0, s);
        r.wait();
        std::cout << s << "\n";
    }
    else if (world.rank() == 1) {
        sleep(3);
        std::string s = "Hello async!";
        world.send(0, 0, s);
    }
}
```

**Exercício**: O código abaixo recebe as mensagens de 1 e 2 de maneira assíncrona, mas não funciona muito diferente de um código síncrono. Modifique-o para usar [`boost::mpi::wait_any`](https://www.boost.org/doc/libs/1_68_0/doc/html/boost/mpi/wait_any.html) ([link docs](https://www.boost.org/doc/libs/1_68_0/doc/html/boost/mpi/wait_any.html)) e mostrar as mensagens na ordem de chegada (ou seja, primeiro a do rank 2 e depois a do rank 1). 

```cpp
#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world;
    
    if (world.rank() == 0) {
        std::string s[2];
        auto r1 = world.irecv(1, 10, s[0]);
        auto r2 = world.irecv(2, 20, s[1]);
        
        r1.wait();
        std::cout << s[0] << "\n" << std::endl;

        r2.wait();        
        std::cout << s[1] << '\n';
    } else if (world.rank() == 1) {
        std::string s = "Hello, world!";
        sleep(2);
        world.send(0, 10, s);
        std::cout << "Fim rank 1 " << std::endl;
    } else if (world.rank() == 2) {
        std::string s = "Hello, moon!";
        sleep(1);
        world.send(0, 20, s); 
        std::cout << "Fim rank 2 " << std::endl;
    }
}
```

**Dicas**: 

1. Você pode criar um vetor de `boost::mpi::request` para passar para `wait_any`;
1. `wait_any` espera até que **exatamente** um request seja completado. Logo, você precisará chamar esta função mais de uma vez. 

**Exercício**: Vamos olhar novamente para o problema da ordenação de elementos de um vetor. Como a operação de *merge* é lenta, vamos receber os vetores e fazer o *merge* na ordem em que os vetores resultado são recebidos. 

**Atenção**: com `gather` só começo os *merge*s após todas as ordenações acabarem.

Faça agora uma versão em que

1. o envio dos vetores seja assíncrono;
1. o recebimento vetores parciais ordenados seja assíncrono;
1. a operação de *merge* ocorra na ordem em que os vetores parcialmente ordenados chegam.

