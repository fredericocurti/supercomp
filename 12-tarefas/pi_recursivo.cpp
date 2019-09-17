#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l*1024*1024*2;
#define MIN_BLK  1024*1024*256*2

double pi_r(long Nstart, long Nfinish, double step) {
    long i, iblk;
    double sum = 0;
    if (Nfinish-Nstart < MIN_BLK) {
        for (i = Nstart; i < Nfinish; i++){
            double x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x); 
        }
    } else {
        iblk = Nfinish-Nstart;
        #pragma omp task shared(sum)
        sum += pi_r(Nstart, Nfinish-iblk/2, step);
        #pragma omp task shared(sum)
        sum += pi_r(Nfinish-iblk/2, Nfinish, step);
        #pragma omp taskwait
    }
    return sum;
}

double pi_par_tasks(long num_steps) {
    double step = 1.0/(double) num_steps;
    double sum = 0;
    #pragma omp parallel shared(sum)
    {
        #pragma omp master 
        {
            sum += pi_r(0, num_steps, step);
        }
    }
    
    return step * sum;
}

int main () {
    long i;
    double init_time, final_time;
    init_time = omp_get_wtime();
    double pi = pi_par_tasks(num_steps);
    final_time = omp_get_wtime() - init_time;
    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";
}
