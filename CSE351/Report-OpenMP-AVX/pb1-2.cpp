#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NRA 15000 /* number of rows in matrix A */
#define NCA 15000 /* number of columns in matrix A */

double ** create_2d_matrix(int columns, int rows) {
  double ** mat = new double*[rows];
  for (int i = 0; i < rows; i++) {
    mat[i] = new double[columns];
  }
  return mat;
}

int main () {
  int i, j, k;
  int threads = 4;
  double **a = create_2d_matrix(NRA,NCA);
  double time1 = omp_get_wtime();
  double sum = 0;
  #pragma omp parallel for num_threads(threads) reduction(+:sum) private(j)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++){
      a[i][j] = 1;
      a[i][j] *= (i+j)%13;
      sum += a[i][j];
    }
  double average = sum/(NRA*NCA);
  printf("average = %6.2f, time = %6.2f",average,omp_get_wtime() - time1);
  return 0;
}
