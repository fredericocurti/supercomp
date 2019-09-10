#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NPOINTS 1000
#define MAXITER 10000

struct d_complex {
   double r;
   double i;
};

int testpoint(struct d_complex c) {
   int iter;
   double temp;
   struct d_complex z = c;

   for (iter = 0; iter < MAXITER; iter++) {
      temp = (z.r * z.r) - (z.i * z.i) + c.r;
      z.i = z.r * z.i * 2 + c.i;
      z.r = temp;
      if ((z.r * z.r + z.i * z.i) > 4.0) {
         return 1;
      }
   }
   return 0;
}

int main() {
   int i, j;
   double area, error;
   double eps = 1.0e-5;
   struct d_complex c;
   int numoutside = 0;

   #pragma omp parallel for private(c)
   for (i = 0; i < NPOINTS; i++) {
      #pragma omp parallel for
      for (j = 0; j < NPOINTS; j++) {
         c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
         c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
         #pragma omp atomic
         numoutside += testpoint(c);
      }
   }

   area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
   error = area / (double)NPOINTS;
   printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
   printf("Correct answer should be around 1.510659\n");
   printf("numoutside: %d\n", numoutside);
   return 1;
}
