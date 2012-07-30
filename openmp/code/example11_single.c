// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

#define SIZE 10
int main() {        
  int a, i;
  int b[SIZE];

  #pragma omp parallel shared(a,b) private(i)
  {
    #pragma omp single
    {
      a = 10;
      printf("Single construct executed by thread %d\n",
          omp_get_thread_num());
    }
    /* A barrier is automatically inserted here */
    #pragma omp for
    for (i=0; i < SIZE; i++)
      b[i] = a;
  }
  printf("After the parallel region:\n");
  for (i=0; i < SIZE; i++)
    printf("b[%d] = %d\n",i,b[i]);
}
