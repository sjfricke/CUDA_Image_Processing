#include "utils.h"
#include <stdio.h>

__global__ void kernel_add_values(Pixel* image_data) {
 
  int y = threadIdx.y+ blockIdx.y* blockDim.y;
  int x = threadIdx.x+ blockIdx.x* blockDim.x;
  //if (y < height && x < width) {
  //  int index = width*y +x;
  //  Pixel color = image_data[index];
  // }
}

// pass in data and file width and height
// assume no alpha values in data
// returns pointer to value
Pixel* add_values(Pixel* image_data, int width, int height, int image_count) {

  Pixel* image_data_d;
  Pixel* image_result_d;

  const int data_size = sizeof(Pixel) * width * height;

  // allocated data to return
  cudaMalloc( (void**)&image_result_d, data_size );

  // allocated data to run on serve
  cudaMalloc( (void**)&image_data_d, data_size * image_count);
  cudaMemcpy( image_data_d, image_data, data_size * image_count, cudaMemcpyHostToDevice );

  dim3 dimGrid(32);
  dim3 dimBlock(32,32);
  
  kernel_add_values<<<dimGrid, dimBlock>>>(image_data_d);

  cudaMemcpy( image_data, image_data_d, data_size, cudaMemcpyDeviceToHost );

  cudaFree( image_data_d );

  return image_result_d;
  // cudaDeviceSynchronize();

  //TODO, what is this?
  //checkCudaErrors(cudaGetLastError());
}