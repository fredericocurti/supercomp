#include <iostream>
#include <iomanip>
#include <omp.h>

int fib(int n) {
    int x,y;
    if(n<2) return n;
    x=fib(n-1);
    y=fib(n-2);
    return(x+y);
}

int fib_par1(int n) {
    int x,y;
    if (n < 2) {
        return n;
    }

    #pragma omp parallel shared(x, y)
    {
        #pragma omp task
        {
            x=fib_par1(n-1);
        }
        #pragma omp task
        {
            y=fib_par1(n-2);
        }
    }
       
    return(x + y);
}

int fib_par2(int n, int tasks) {
    int x,y;
    if (n < 2) {
        return n;
    }

    if (tasks > 0) {
        #pragma omp parallel shared(x, y)
        {
            #pragma omp task
            {
                x=fib_par2(n-1, tasks-1);
            }
                
            #pragma omp task
            {
                y=fib_par2(n-2, tasks-1);    
            }
        }
    } else {
        x = fib_par2(n - 1, tasks-1);
        y = fib_par2(n - 2, tasks-1);    
    }
    
    return(x + y);
}

int main() {    
    int NW=35;
    int f=fib(NW);
    std::cout << f << std::endl;
    f=fib_par2(NW, 3);
    std::cout << f << std::endl;
    f=fib_par1(NW);
    std::cout << f << std::endl;
}