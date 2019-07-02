#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define __RANGE__ 500000

int main () {
  int threads = 12, notPrimes = 0;
  double time1 = omp_get_wtime();
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(static)
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(dynamic, 1)
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(dynamic, 100)
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(dynamic, 1000)
  for (int i = 2; i <= __RANGE__; i++)
    for (int j = 2; j <= i/2; j++)
      if(i % j == 0){
        notPrimes++;
        j = 2 * i;
      }

  printf("primes = %d, time = %6.2f", __RANGE__ - notPrimes - 1, omp_get_wtime() - time1);

  return 0;
}
