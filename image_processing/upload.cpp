#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char** argv) {

  // check for parameter
  if (argc < 3) {
     fprintf(stderr, "%s\n", "Need to pass file src and dest");
     exit(1);
  }

  // declare images
  cv::Mat src_image;
  cv::Mat dest_image;

  // read in image
  src_image = cv::imread( argv[1], 1 );
  if ( !src_image.data ) {
    fprintf(stderr, "%s\n", "image was not read correctly");
    exit(1);
  }

  cv::resize(src_image, dest_image, cv::Size(100, 56), 0, 0, CV_INTER_AREA);

  // write out image
  cv::imwrite( argv[2], dest_image );

  exit(0);
}
