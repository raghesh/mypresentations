// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

#define SIZE 10
int main() {        
  int a[SIZE], b[SIZE], c[SIZE];
  int i, tid;

  for(i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = 2 * i;
  }

#pragma omp parallel  shared(a), private(i, tid)
  {
#pragma omp for
    for(i = 0; i < SIZE; i++) {
      c[i] = a[i] + b[i];
      tid = omp_get_thread_num();
      printf("Thread %d, i = %d\n", tid, i);
    }
  }

  for(i = 0; i < SIZE; i++)
    printf("%d\n", c[i]);
}
