// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

int main() {        
  int b = 0;
#pragma omp parallel shared(b)
  {
#pragma omp critical
    b++;
  }
  printf("%d\n", b);
}
