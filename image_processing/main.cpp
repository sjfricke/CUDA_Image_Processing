#include <iostream>
#include "utils.h"
#include <string>
#include <stdio.h>

#include "processing.cpp"

void your_rgba_to_greyscale(const uchar4 * const h_rgbaImage,
			    uchar4 * const d_rgbaImage,
			    unsigned char* const d_greyImage,
			    size_t numRows, size_t numCols);

int main(int argc, char **argv) {

  uchar4        *h_rgbaImage, *d_rgbaImage;
  unsigned char *h_greyImage, *d_greyImage;

  std::string input_file_0;
  std::string input_file_1;
  std::string input_file_2;
  std::string output_file;
  
  input_file_0 = std::string(argv[1]);
  input_file_1 = std::string(argv[2]);
  input_file_2 = std::string(argv[3]);
  output_file = "HW1_output.png";

  //load the image and give us our input and output pointers
  preProcess(&h_rgbaImage, &h_greyImage, &d_rgbaImage, &d_greyImage, input_file_0);

  //call the students' code
  your_rgba_to_greyscale(h_rgbaImage, d_rgbaImage, d_greyImage, numRows(), numCols());

  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

  size_t numPixels = numRows()*numCols();
  checkCudaErrors(cudaMemcpy(h_greyImage, d_greyImage, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost));

  cleanup();

  return 0;
}
