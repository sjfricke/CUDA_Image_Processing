#include "utils.h"

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "%s", "Need to pass at least 2 args");
  }
  
  int i;
  Pixel current_pixel;
  cv::Vec3b image_buffer;
  
  std::string output_file;

  std::vector<Pixel> IMAGE_DATA;

  std::vector<cv::Mat> IMAGE_FILES;

  // adds list of passed images to list of images
  for (i = 1; i < argc; i++) {

    cv::Mat image_temp;
    
    
    image_temp = cv::imread(argv[i], CV_LOAD_IMAGE_COLOR);

    if (image_temp.empty()) {
      std::cout << "ERROR: Image not read" << std::endl;
      exit(1);
    }

    //This shouldn't ever happen given the way the images are created
    //at least based upon my limited understanding of OpenCV, but better to check
    if (!image_temp.isContinuous()) {
      std::cout << "ERROR: Image not read" << std::endl;
      exit(1);
    } 

    IMAGE_FILES.push_back(image_temp);
  }

  // takes data from files to pixels
  // Triple for loop... its 3am, I do what I want
  for (int l = 0; l < IMAGE_FILES.size(); l++) {
    
    for(int i = 0; i < IMAGE_FILES.at(l).rows; i++) {
      for(int j = 0; j < IMAGE_FILES.at(l).cols; j++) {
        image_buffer = IMAGE_FILES.at(l).at<cv::Vec3b>(i,j);
	current_pixel.red = image_buffer[2];
	current_pixel.green = image_buffer[1];
	current_pixel.blue = image_buffer[0];
	IMAGE_DATA.push_back(current_pixel);
	//printf("RGB at(%x,%x): %.2X%.2X%.2X\n", i, j ,buf[2], buf[1], buf[0]);
      }
    }
    printf("at loop %d size is %zu\n", l, IMAGE_DATA.size());
  }

  
  output_file = "test_output.jpg";

  //make sure the context initializes ok
  
  //load the image and give us our input and output pointers
  //  preProcess(&h_rgbImage, &h_greyImage, &d_rgbImage, &d_greyImage, input_file_0);

  //call the students' code
  // your_rgb_to_greyscale(h_rgbImage, d_rgbImage, d_greyImage, numRows(), numCols());

  //cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
  //checkCudaErrors(cudaMemcpy(h_greyImage, d_greyImage, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost));

  //  cv::Mat output(numRows(), numCols(), CV_8UC1, (void*)data_ptr);

  //output the image
  //cv::imwrite(output_file.c_str(), output);
  
  //cleanup
  //cudaFree(d_rgbaImage__);
  //  cudaFree(d_greyImage__);


  return 0;
}
