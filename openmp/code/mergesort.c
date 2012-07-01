#include <stdio.h>
#include <stdlib.h>

void merge(int A[], int p, int q, int r) {
  int i, j, k;
  int n1 = q - p;
  int n2 = r - q;

  int *L = malloc((n1 + 1)*sizeof(int));
  int *R = malloc((n2 + 1)*sizeof(int));

  for (i = 0; i < n1; i++)
    L[i] = A[p + i];

  for (i = 0; i < n2; i++)
    R[i] = A[q + i];

  L[n1] = 0xfffff;
  R[n2] = 0xfffff;
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
int main() {
  int A[10] = {4, 2, 3, 1, 6, 5, 8, 10, 7, 9}, i;

  mergeSortOMPParallel(A, 0, 10, 2);

  for (i = 0; i < 10; i++)
    printf("%d\n", A[i]);
}
