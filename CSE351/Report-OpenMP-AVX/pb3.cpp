#include <stdio.h>
#include <ctime>

using namespace std;

int main(int argc, char const *argv[])
{
  long long loops = 100000000;
  double pi = 0.0;
  int threads = 4;
  double step = 1.0/loops;
  long clock1 = clock();
  #pragma omp parallel for num_threads(threads) reduction(+:pi)
  for(long long i = 0; i < loops; i++)
    pi += 4.0 / ( 1 + ( ( i + 0.5 ) * step * ( i + 0.5 ) * step ) );
  printf("PI = %.10f\nTime = %.2fs\n", pi * step, float(clock() - clock1) / CLOCKS_PER_SEC);
  return 0;
}
