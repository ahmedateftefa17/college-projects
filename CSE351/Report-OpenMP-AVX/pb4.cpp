#include <stdio.h>
#include <immintrin.h>
#include <ctime>

void* malloc_aligned_generic(size_t alignment, size_t size)
{
  char* p1 = (char*) malloc(size + alignment + sizeof(void*));
  p1 += sizeof(void*);
  void* p2 = (void*) ((uintptr_t) p1 + alignment - (uintptr_t) p1 % alignment);
  *((void**)((uintptr_t) p2 - sizeof(void*))) = p1 - sizeof(void*);
  return p2;
}

void free_aligned(void* p)
{

}

void cosx(int N, int terms, float* x, float* result)
{
  for(int i = 0; i < N; i++)
  {
    float value = 1;
    float numer = x[i] * x[i];
    int denom = 2;
    int sign = -1;
    for(int j = 1; j < terms; j++)
    {
      value += sign * numer / denom;
      numer *= x[i] * x[i];
      denom *= (j+2) * (j+3);
      sign  *= -1;
    }
    result[i] = value;
  }
}


void cosx_avx(unsigned long long N, unsigned short terms, float x[], float result[])
{
  for(int i = 0; i < N; i+=8)
  {
    __m256 origx = _mm256_set1_ps(x[i]);
    __m256 unity = _mm256_set1_ps(1.0f);
    __m256 value = unity;
    __m256 numer = _mm256_mul_ps(origx, origx);
    __m256 denom = _mm256_set1_ps(2);
    float sign = -1;
    for (int j = 1; j <= terms; j++)
    {
      value = _mm256_add_ps(_mm256_div_ps(_mm256_mul_ps(_mm256_set1_ps(sign), numer), denom), value);
      numer = _mm256_mul_ps(numer, _mm256_mul_ps(origx, origx));
      denom = _mm256_mul_ps(denom, _mm256_set1_ps(float(j + 2) * float(j + 3)));
      sign *= -1;
    }
    _mm256_store_ps(&result[i], value);
  }
}

int main()
{
  const unsigned long long N = (unsigned long long) (8 * 10e6);
  const unsigned short NUM_TERMS = 7;
  float* result;
  float* x;

  result = (float*)malloc_aligned_generic(32, sizeof(float) * N);
  x = (float*)malloc_aligned_generic(32, sizeof(float) * N);

  for(int i = 0; i < N; i++)
    x[i] = (float) 3.14 * rand() / RAND_MAX;
  x[0] = 0;

  long clock1 = clock();
  cosx(N, NUM_TERMS, x, result);
  printf("Normal Time = %6.2f\n", double(clock() - clock1) / CLOCKS_PER_SEC);

  clock1 = clock();
  cosx_avx(N, NUM_TERMS, x, result);
  printf("AVX Time    = %6.2f\n", double(clock() - clock1) / CLOCKS_PER_SEC);

  printf("%f\n", result[0]);

  // free_aligned(x);
  // free_aligned(result);

  return 0;
}
