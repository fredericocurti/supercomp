#include <omp.h>
#include <iostream>
#include <iomanip>

int main() {
    std::cout << "I think";
    #pragma omp parallel
    {
        #pragma omp master
        {
            #pragma omp task 
            {
                std::cout << "races";
            }

            #pragma omp task 
            {
                std::cout << "cars";
            }
        }
    }
    std::cout << " are fun" << std::endl;   
}