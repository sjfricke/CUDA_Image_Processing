#include "utils.h"
#include <stdio.h>

__global__ void average_linear_kernel(Pixel* image_data, Pixel* image_result, int col, int row, int image_index) {
 
  //int y = threadIdx.y+ blockIdx.y* blockDim.y;
  int x = threadIdx.x+ blockIdx.x* blockDim.x;

  if (x < (col * row)) {
    image_result[x] = image_data[x];
  }
  
  //if (y < height && x < width) {
  //  int index = width*y +x;
  //  Pixel color = image_data[index];
  // }
}

// pass in data and file width and height
// assume no alpha values in data
// returns pointer to value
Pixel* average_linear_cuda(Pixel* image_data_h, int width, int height, int image_count) {

  Pixel* image_data_d;
  Pixel* image_result_d;
  Pixel* image_result_h;
  const int image_data_size = sizeof(Pixel) * width * height;

  // allocated data to return
  cudaMalloc( (void**)&image_result_d, image_data_size );
  image_result_h = (Pixel*)malloc(image_data_size);
  
  // allocated data to run on server
  cudaMalloc( (void**)&image_data_d, image_data_size * image_count);
  cudaMemcpy( image_data_d, image_data_h, image_data_size * image_count, cudaMemcpyHostToDevice );

  dim3 dimGrid(64);
  dim3 dimBlock(32);

  printf("cuda calling\n");
  average_linear_kernel<<<dimGrid, dimBlock>>>(image_data_d, image_result_d,  width, height, image_count);
  printf("cuda called\n");
  
  cudaMemcpy( image_result_h, image_result_d, image_data_size, cudaMemcpyDeviceToHost );

  // checks for CUDA errors
  cudaError_t errSync  = cudaGetLastError();
  cudaError_t errAsync = cudaDeviceSynchronize();
   if (errSync != cudaSuccess){ printf("Sync kernel error: %s\n", cudaGetErrorString(errSync)); }
  else if (errAsync != cudaSuccess) { printf("Async kernel error: %s\n", cudaGetErrorString(errAsync)); }
  
  cudaFree( image_data_d );
  cudaFree( image_result_d);

  //  for (int i = 0; i < (width * height); i++) {
  //  printf("pixel <%d, %d> RGB: <%d, %d, %d>\n", i%width, i/width, image_result_h[i].red, image_result_h[i].green, image_result_h[i].blue);
  // }
  
  return image_result_h;
}