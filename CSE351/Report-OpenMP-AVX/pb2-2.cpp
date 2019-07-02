#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define __RANGE__ 500000

int main () {
  int threads = 2;
  // int threads = 4;
  // int threads = 8;
  // int threads = 12;
  int notPrimes = 0;
  double time1 = omp_get_wtime();
  #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(static)
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(static, 1)
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(static, 100)
  // #pragma omp parallel for num_threads(threads) reduction(+:notPrimes) schedule(static, 1000)
  for (int i = 2; i <= __RANGE__; i++)
    for (int j = 2; j <= i/2; j++)
      if(i % j == 0){
        notPrimes++;
        j = i; // to break the loop
      }
  printf("primes = %d, time = %6.2f", __RANGE__ - notPrimes - 1, omp_get_wtime() - time1);
  return 0;
}
