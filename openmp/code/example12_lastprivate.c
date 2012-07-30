// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

#define SIZE 10
int main() {        
  int a, i;

  #pragma omp parallel for private(i) lastprivate(a)
  for (i=0; i < SIZE; i++)
  {
      a = i+1;
      printf("Thread %d a = %d i = %d\n", omp_get_thread_num(),a,i);
  }
  printf("Value of a after parallel for: a = %d\n",a);
}
