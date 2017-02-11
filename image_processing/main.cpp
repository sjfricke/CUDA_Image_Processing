#include "utils.h"
//#include "processing.h"

//Debug
#define USEDEBUG
#ifdef USEDEBUG
#define debug( x, y ) std::cout << x << y << std::endl;
#else
#define debug( x, y ) 
#endif

using namespace std;

// used to save file of a buffer of Pixels
int saveFile(Pixel* image_data, int height, int width, string output_file) {

  cv::Mat image_buffer = cv::Mat(height, width, CV_8UC3, (uint8_t*)image_data ).clone(); // make a copy
  debug("image_buffer", " created");

  cv::imwrite( output_file, image_buffer );

  debug("image write", "");
  return 0;
}

/*
 * used to store set of images by images in buffer
 * image_1 = A; image_2 = B; both 16x8 deminsions
 * [ A_x1_y1, A_x2_y1, A_x3_y1, ... , B_x15_y16, B_x16_y16 ]
 */
int bufferByImage(vector<cv::Mat>& IMAGE_FILES, Pixel* IMAGE_DATA, int image_count) {
  
  int i,j,k; // loops
  Pixel pixel_buffer; // Pixel is a 3-byte struct for 8-bit RGB value
  cv::Vec3b image_buffer;
  uint64_t buffer_count = 0;
  
  // triple for loop... its works, I do what I want 
  for ( i = 0; i < image_count; i++) {
   
    for( j = 0; j < IMAGE_FILES[i].rows; j++) {
      for( k = 0; k < IMAGE_FILES[i].cols; k++) {

	// i == image_index, j == row, k == column
	
        image_buffer = IMAGE_FILES[i].at<cv::Vec3b>(j,k);

	// stores as BGR
	// TODO, make sure Red and Blue are not swapped
  	pixel_buffer.red = image_buffer[2];
	pixel_buffer.green = image_buffer[1];
	pixel_buffer.blue = image_buffer[0];
	
	// sets Pixel at spot in memory
	// TODO - see if index math better then buffer count
	*(IMAGE_DATA + buffer_count) = pixel_buffer;
	
	buffer_count++;
      } //for cols
    } // for rows
  } // iterator end

  debug("malloc pixels: ", buffer_count);

  return 0;
}


/*
 * used to store set of images by coord in buffer
 * image_1 = A; image_2 = B; both 16x8 deminsions
 * [ A_x1_y1, B_x1_y1, A_x2_y1, ... , A_x16_y16, B_x16_y16 ]
 */
int bufferByCoord(vector<cv::Mat>& IMAGE_FILES, Pixel* IMAGE_DATA, int image_count, int height, int width) {
  
  int i,j,k; // loops
  Pixel pixel_buffer; // Pixel is a 3-byte struct for 8-bit RGB value
  cv::Vec3b image_buffer;
  
  // triple for loop... its works, I do what I want 
  for ( i = 0; i < image_count; i++) {
   
    for( j = 0; j < IMAGE_FILES[i].rows; j++) {
      for( k = 0; k < IMAGE_FILES[i].cols; k++) {

	// i == image_index, j == row, k == column
	
        image_buffer = IMAGE_FILES[i].at<cv::Vec3b>(j,k);

	// stores as BGR
	// TODO, make sure Red and Blue are not swapped
  	pixel_buffer.red = image_buffer[2];
	pixel_buffer.green = image_buffer[1];
	pixel_buffer.blue = image_buffer[0];
	
	// sets Pixel at spot in memory
	// TODO - see if index math better then buffer count
	*(IMAGE_DATA + i + (((width*j) + k) * image_count) ) = pixel_buffer;
	
      } //for cols
    } // for rows
  } // iterator end

  return 0;
}


/* 
 * Pass array image paths in argv[1] - argv[n]
 * Opens first one to get size of file
 * Allocates buffer for data
 * Iterates through images sources, loads image and set in data
 * Rest is sent to other operations outside main
 */
int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "%s", "Need to pass at least 3 args");
    exit(1);
  }
  
  int i; // loops
  int err_check;
  //buffers to hold temp data
  cv::Mat mat_buffer;

  // main data of images
  Pixel* IMAGE_DATA; //3D array of images
  int image_count = argc - 1; // Can change if added more arguments to program
  int image_width, image_height; 
  Pixel* result_data;
  
  string output_file;

  vector<cv::Mat> IMAGE_FILES; // holds all file paths

  // adds list of passed images to list of images
  for (i = 1; i < argc; i++) {
    
    mat_buffer = cv::imread(argv[i], CV_LOAD_IMAGE_COLOR);

    if (mat_buffer.empty()) {
      cout << "ERROR: Image not read" << endl;
      exit(1);
    }
    //This shouldn't ever happen given the way the images are created
    //at least based upon my limited understanding of OpenCV, but better to check
    else if (!mat_buffer.isContinuous()) {
      cout << "ERROR: Image not read" << endl;
      exit(1);
    } 

    IMAGE_FILES.push_back(mat_buffer);
  } 

  // gets image dimensions from first photo
  // ATM assuming all are same size
  image_height = IMAGE_FILES.front().rows;
  image_width = IMAGE_FILES.front().cols;


  // allocated enough data by number of photos
  // reference: 3 * 1024 * 576 == ~1.8MB
  int image_byte_size = (sizeof(Pixel) * image_width * image_height);
  
  IMAGE_DATA = (Pixel*) malloc(image_byte_size * image_count);
  
  if (IMAGE_DATA == NULL) {
      cout << "ERROR: IMAGE_DATA Malloc Failed" << endl;
      exit(1);
  }

  debug("byte size: ", (sizeof(Pixel) * image_width * image_height * image_count));

  //bufferByImage(IMAGE_FILES, IMAGE_DATA, image_count);
  bufferByCoord(IMAGE_FILES, IMAGE_DATA, image_count, image_height, image_width);
  
  output_file = "test_output.jpg";

  //sends back pointer with added data from CUDA
  result_data = average_linear_cuda(IMAGE_DATA, image_height, image_width, image_count);

  err_check = saveFile(result_data, image_height, image_width, output_file);

  if (err_check != 0) {  cout << "ERROR: writing to file" << endl; }
  
  return 0;
}
