#include <stdio.h>

const int N = 256;

__global__
void hello(char *a)
{
  printf("Hello from thread %d\n", threadIdx.x);
  // printf("Hello from thread %d with letter %c\n", threadIdx.x, a[threadIdx.x % 32]);
}

int main()
{
  char a[N] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ01234";

  char *a_d;

  const int csize = N*sizeof(char);
  
  //printf("%s", a);

  cudaMalloc( (void**)&a_d, csize );
  cudaMemcpy( a_d, a, csize, cudaMemcpyHostToDevice );

  hello<<<1, 256>>>(a_d);

  cudaMemcpy( a, a_d, csize, cudaMemcpyDeviceToHost );

  cudaFree( a_d );
  
  //printf("%s\n", a);

  return EXIT_SUCCESS;
}
