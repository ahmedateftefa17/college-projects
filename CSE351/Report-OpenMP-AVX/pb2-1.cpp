#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define __RANGE__ 500000

int main () {
  int threads = 4, notPrimes = 0;
  double time1 = omp_get_wtime();
  for (int i = 2; i <= __RANGE__; i++)
    for (int j = 2; j <= i/2; j++)
      if(i % j == 0){
        notPrimes++;
        break;
      }
  printf("primes = %d, time = %6.2f", __RANGE__ - notPrimes - 1, omp_get_wtime() - time1);
  return 0;
}
