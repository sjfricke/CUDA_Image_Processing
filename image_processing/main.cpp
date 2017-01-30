#include "utils.h"
#include "processing.h"

const IMAGE_WIDTH = 32;
const IMAGE_HEIGHT = 32;

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "%s", "Need to pass at least 3 args");
  }
  
  int i;
  Pixel current_pixel;
  cv::Vec3b image_buffer;
  int image_count = atoi(argv[1]); // Can change if added more arguments to program
  int buffer_count = 0;

  Pixel* added_values;
  
  std::string output_file;

  // allocated enough data by number of photos
  Pixel* IMAGE_DATA = (Pixel*) malloc(sizeof(Pixel) * IMAGE_WIDTH * IMAGE_HEIGHT * image_count)
  
  if (IMAGE_DATA == NULL) {
      std::cout << "ERROR: IMAGE_DATA Malloc Failed" << std::endl;
      exit(1);
  }
  
  std::vector<cv::Mat> IMAGE_FILES;

  // adds list of passed images to list of images
  for (i = 2; i < argc; i++) {

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

	//sets Pixel at spot in memory
	*(IMAGE_DATA + buffer_count) = current_pixel;
	
	buffer_count++;
      }
    }
  }

  
  output_file = "test_output.jpg";

  //sends back pointer with added data from CUDA
  added_values = add_values(IMAGE_DATA, IMAGE_WIDTH, IMAGE_HEIGHT, image_count);
  
  //average_value(0, 1023);
  std::cout << "=================" << std::endl;
  //average_value(1024, 2047);
  std::cout << "=================" << std::endl;
  //average_value(2048, 3071);
    
  
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
