// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

#define SIZE 10
int main() {        
  int a[SIZE], b[SIZE], c[SIZE];
  int i, tid, result = 0;

  for(i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = 2 * i;
  }

#pragma omp parallel shared(a), private(i, tid), reduction(+:result)
  {
#pragma omp for
    for(i = 0; i < SIZE; i++) {
      result += a[i] + b[i];
    }
    printf("%d\n", result);
  }

  printf("result = %d\n", result);
}
