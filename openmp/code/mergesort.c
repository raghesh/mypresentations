#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 10

void merge(int A[], int p, int q, int r) {
  int i, j, k;
  int n1 = q - p;
  int n2 = r - q;

  int *L = (int *)malloc((n1 + 1)*sizeof(int));
  int *R = (int *)malloc((n2 + 1)*sizeof(int));

  for (i = 0; i < n1; i++)
    L[i] = A[p + i];

  for (i = 0; i < n2; i++)
    R[i] = A[q + i];

  L[n1] = 0xfffffff;
  R[n2] = 0xfffffff;
  i = 0; j = 0;
  for (k = p; k < r; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
  }
  free(L);
  free(R);
}


void mergeSortSerial(int A[], int p, int r) {
  printf("%d %d: ", p, r);
  for (int i = 0; i < DATASIZE; i++)
    printf("%d ", A[i]);
  printf("\n");
  if (p == r - 1)
    return;
  int q = (p + r) / 2;
  mergeSortSerial(A, p, q);
  mergeSortSerial(A, q, r);
  merge(A, p, q, r);
}

void mergeSortOMPParallel(int A[], int p, int r, int threads) {
  if (threads == 1)
    mergeSortSerial(A, p, r);
  else if (threads > 1) {
    int q = (p + r) / 2;
    int iam = 0, np = 1;
    #pragma omp parallel sections
    {
      #pragma omp section
      mergeSortOMPParallel(A, p, q, threads / 2);
      #pragma omp section
      mergeSortOMPParallel(A, q, r, threads - threads / 2);
    }
#if defined (_OPENMP)
    np = omp_get_num_threads();
    iam = omp_get_thread_num();
#endif
    printf("Hello from thread %d out of %d \n", iam, np);
    merge(A, p, q, r);
  }
}

int main(int argc, char *argv[]) {
  unsigned int seed;
  //int A[DATASIZE] = {100, 2, 78, 34, 1, 5, 0, 234, 9, 0}, r, i;
  //int A[DATASIZE] = {100, 2, 78, 34}, r, i;
  int A[DATASIZE] = {4404747, 1048575, 1048575, 1048575, 0, 1048575, 0, 135049, 0, 0},  r, i;

  if (argc != 2) {
	  fprintf(stderr, "Usage: %s <seed>\n", argv[0]);
	  exit(EXIT_FAILURE);
  }
/*  seed = atoi(argv[1]);
 srand(seed);
  for (i = 0; i < DATASIZE; i++) {
    r =  rand();
    A[i] = r;
  }*/
  for (i = 0; i < DATASIZE; i++)
    printf("%d  ", A[i]);
  printf("\n");
  mergeSortSerial(A, 0, DATASIZE);
  //mergeSortOMPParallel(A, 0, DATASIZE, 1);

  for (i = 0; i < DATASIZE; i++)
    printf("%d  ", A[i]);
  printf("\n");
}
