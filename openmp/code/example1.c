// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

int main() {        
  int iam =0, np = 1;
#pragma omp parallel private(iam, np)
  {
    np = omp_get_num_threads();
    iam = omp_get_thread_num();
    printf("Hello from thread %d out of %d \n", iam, np);
  }
}
