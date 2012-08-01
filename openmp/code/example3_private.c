// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

int main() {        
  int b = 20, tid = 0;
  printf("%x\n", &b);
#pragma omp parallel private(b, tid)
  {
    ++;
    printf("%x\n", &b);
    tid = omp_get_thread_num();
    printf("Thread %d: b = %d\n", tid, b);
  }
  printf("%d\n", b);
}
