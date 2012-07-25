// To compile: gcc example1.c -fopenmp
#include <omp.h>
#include <stdio.h>

int main() {
  int tid;
#pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    printf("Thread %d sleeping\n", tid);
    sleep(tid);
    printf("Thread %d woke up, but waiting for others\n", tid);
#pragma omp barrier
    printf("Thread %d ready to go\n", tid);
  }
}
