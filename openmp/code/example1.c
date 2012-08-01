// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

int main() {        
  int tid, n;
    n = omp_get_num_threads();
#pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    printf("Hello from thread %d out of %d \n", tid, n);
  }
}
