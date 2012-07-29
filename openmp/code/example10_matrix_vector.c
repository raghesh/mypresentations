#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void mxv(int m, int n, double *a, double *b, double *c) {
  int i, j;
  #pragma omp parallel for shared(m,n,a,b,c), private(i,j)
    for (i=0; i<m; i++) {
      a[i] = 0.0;
      for (j=0; j<n; j++)
        a[i] += b[i*n+j]*c[j];
    }
}

int main(int argc, char *argv[]) {
  double *a,*b,*c;
  int i, j, m, n;
  printf("Please give m and n: ");
  scanf("%d %d",&m,&n);
  if ( (a=(double *)malloc(m*sizeof(double))) == NULL )
    perror("memory allocation for a");
  if ( (b=(double *)malloc(m*n*sizeof(double))) == NULL )
    perror("memory allocation for b");
  if ( (c=(double *)malloc(n*sizeof(double))) == NULL )
    perror("memory allocation for c");
  printf("Initializing matrix B and vector c\n");
  for (j=0; j<n; j++)
    c[j] = 2.0;
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      b[i*n+j] = i;
  printf("Executing mxv function for m = %d n = %d\n",m,n);
  (void) mxv(m, n, a, b, c);
  free(a);free(b);free(c);
  return(0);
}
