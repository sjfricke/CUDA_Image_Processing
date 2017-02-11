#include "utils.h"
#include <stdio.h>

// HARD coding 128 images into it for the time being
// Parallel Reduction is not a fun task to work with...
// unrolling loop to save on preformance as much as possible
// by unrolling it the kernel gets evaluated at compile time for the if statments
__global__ void average_linear_kernel(Pixel* image_data, Pixel* image_result, int image_size) {
   
  __shared__ unsigned int pixel_reduction[64 * 3]; // only need first half of shared array

  // int y = threadIdx.y+ blockIdx.y* blockDim.y;
  // int x = threadIdx.x+ blockIdx.x* blockDim.x;
  int t_id = threadIdx.x; // which image index it is
  int block_offset = blockIdx.x * image_size;
  
  if (t_id < 64) {
    pixel_reduction[(t_id*3) + 0] = image_data[t_id + block_offset].red   + image_data[t_id + block_offset + 64].red;
    pixel_reduction[(t_id*3) + 1] = image_data[t_id + block_offset].green + image_data[t_id + block_offset + 64].green;
    pixel_reduction[(t_id*3) + 2] = image_data[t_id + block_offset].blue  + image_data[t_id + block_offset + 64].blue;
  }
  __syncthreads();

  // Instructions are SIMD synchronous within a warp
  if (t_id < 32) {
    pixel_reduction[(t_id*3) + 0] += pixel_reduction[((t_id+32)*3) + 0];
    pixel_reduction[(t_id*3) + 1] += pixel_reduction[((t_id+32)*3) + 1];
    pixel_reduction[(t_id*3) + 2] += pixel_reduction[((t_id+32)*3) + 2]; 
  __syncthreads();

    pixel_reduction[(t_id*3) + 0] += pixel_reduction[((t_id+16)*3) + 0];
    pixel_reduction[(t_id*3) + 1] += pixel_reduction[((t_id+16)*3) + 1];
    pixel_reduction[(t_id*3) + 2] += pixel_reduction[((t_id+16)*3) + 2];
  __syncthreads();

    pixel_reduction[(t_id*3) + 0] += pixel_reduction[((t_id+8)*3) + 0];
    pixel_reduction[(t_id*3) + 1] += pixel_reduction[((t_id+8)*3) + 1];
    pixel_reduction[(t_id*3) + 2] += pixel_reduction[((t_id+8)*3) + 2];
  __syncthreads();

    pixel_reduction[(t_id*3) + 0] += pixel_reduction[((t_id+4)*3) + 0];
    pixel_reduction[(t_id*3) + 1] += pixel_reduction[((t_id+4)*3) + 1];
    pixel_reduction[(t_id*3) + 2] += pixel_reduction[((t_id+4)*3) + 2];
  __syncthreads();

    pixel_reduction[(t_id*3) + 0] += pixel_reduction[((t_id+2)*3) + 0];
    pixel_reduction[(t_id*3) + 1] += pixel_reduction[((t_id+2)*3) + 1];
    pixel_reduction[(t_id*3) + 2] += pixel_reduction[((t_id+2)*3) + 2];
  __syncthreads();

    pixel_reduction[(t_id*3) + 0] += pixel_reduction[((t_id+1)*3) + 0];
    pixel_reduction[(t_id*3) + 1] += pixel_reduction[((t_id+1)*3) + 1];
    pixel_reduction[(t_id*3) + 2] += pixel_reduction[((t_id+1)*3) + 2];
  }
  __syncthreads();

  if (t_id == 0) {
    image_result[blockIdx.x].red   = pixel_reduction[0];
    image_result[blockIdx.x].green = pixel_reduction[1];
    image_result[blockIdx.x].blue  = pixel_reduction[2];
  }
  __syncthreads();

}

// pass in data and file width and height
// assume no alpha values in data
// returns pointer to value
Pixel* average_linear_cuda(Pixel* image_data_h, int width, int height, int image_count) {

  Pixel* image_data_d;
  Pixel* image_result_d;
  Pixel* image_result_h;
  const int image_size = width * height;
  const int image_data_size = sizeof(Pixel) * image_size;
  
  // allocated data to return
  cudaMalloc( (void**)&image_result_d, image_data_size );
  image_result_h = (Pixel*)malloc(image_data_size);
  
  // allocated data to run on server
  cudaMalloc( (void**)&image_data_d, image_data_size * image_count);
  cudaMemcpy( image_data_d, image_data_h, image_data_size * image_count, cudaMemcpyHostToDevice );

  dim3 dimGrid(height * width);
  dim3 dimBlock(128); //HARD set atm

  printf("cuda calling\n");
  average_linear_kernel<<<dimGrid, dimBlock>>>(image_data_d, image_result_d, image_size);
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