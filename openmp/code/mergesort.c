#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 2050000
#define INFINITY 0x7fffffff
#define DATAMAX 0x3fffffff

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
  
  L[n1] = INFINITY;
  R[n2] = INFINITY;
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
    int tid = 0, n = 1;
    #pragma omp parallel sections
    {
      #pragma omp section
      mergeSortOMPParallel(A, p, q, threads / 2);
      #pragma omp section
      mergeSortOMPParallel(A, q, r, threads - threads / 2);
    }
    merge(A, p, q, r);
  }
}

void printData(int A[]) {
  int i;

  for (i = 0; i < DATASIZE; i++)
    printf("%d  ", A[i]);
  printf("\n");
}

int main(int argc, char *argv[]) {
  unsigned int seed;
  int A[DATASIZE];
  int r, i, num_threads;

  if (argc < 3) {
	  fprintf(stderr, "Usage: %s <seed> <num_threads>\n", argv[0]);
    fprintf(stderr, "Set num_threads = OMP_NUM_THREADS\n");
	  exit(EXIT_FAILURE);
  }

  seed = atoi(argv[1]);
  srand(seed);
  for (i = 0; i < DATASIZE; i++) {
    r =  rand();
    A[i] = r % DATAMAX;
  }
  num_threads = atoi(argv[2]);
  mergeSortOMPParallel(A, 0, DATASIZE, 8);

  //printData(A);
  return 0;
}
