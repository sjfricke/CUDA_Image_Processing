#include "utils.h"
//#include "processing.h"

//Debug
#define USEDEBUG
#ifdef USEDEBUG
#define debug( x ) std::cout << x << std::endl;
#else
#define debug( x ) 
#endif
/* 
 * Pass array image paths in argv[1] - argv[n]
 * Opens first one to get size of file
 * Allocates buffer for data
 * Iterates through images sources, loads image and set in data
 * Rest is sent to other operations outside main
 */

using namespace std;

int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "%s", "Need to pass at least 3 args");
    exit(1);
  }
  
  int i,j; // loops
  //buffers to hold temp data
  Pixel pixel_buffer;
  cv::Vec3b image_buffer;
  cv::Mat mat_buffer;
  int buffer_count = 0;
  
  int image_count = argc - 1; // Can change if added more arguments to program
  int image_width, image_height; 
  
  //Pixel* added_values;
  
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
  Pixel* IMAGE_DATA = (Pixel*) malloc(sizeof(Pixel) * image_width * image_height * image_count);
  
  if (IMAGE_DATA == NULL) {
      cout << "ERROR: IMAGE_DATA Malloc Failed" << endl;
      exit(1);
  }

  debug((sizeof(Pixel) * image_width * image_height * image_count));
  
  // iterates through vector
  for (vector<cv::Mat>::iterator iterator = IMAGE_FILES.begin() ; iterator != IMAGE_FILES.end(); ++iterator) {

    // takes data from files to pixels
    // double for loop inside iterator... its 3am, I do what I want 
    for( i = 0; i < iterator->rows; i++) {
      for( j = 0; j < iterator->cols; j++) {
	image_buffer = (*iterator).at<cv::Vec3b>(i,j);
	pixel_buffer.red = image_buffer[2];
	pixel_buffer.green = image_buffer[1];
	pixel_buffer.blue = image_buffer[0];
	
	//sets Pixel at spot in memory
	*(IMAGE_DATA + buffer_count) = pixel_buffer;
	
	buffer_count++;
      }
    }
  
  } // iterator end
  
 

  
  output_file = "test_output.jpg";

  //sends back pointer with added data from CUDA
  //added_values = add_values(IMAGE_DATA, IMAGE_WIDTH, IMAGE_HEIGHT, image_count);
  
  return 0;
}
