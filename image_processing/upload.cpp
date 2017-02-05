#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char** argv) {

  // check for parameter
  if (argc < 3) {
     fprintf(stderr, "%s\n", "Need to pass <file_src> <resize_dst>");
     exit(1);
  }

  // declare images
  cv::Mat src_image;
  cv::Mat dest_image_thumb;
  cv::Mat dest_image_full;

  // read in image
  src_image = cv::imread( argv[1], CV_LOAD_IMAGE_COLOR );
  if ( !src_image.data ) {
    fprintf(stderr, "%s\n", "image was not read correctly");
    exit(1);
  }

  // resize image and writes it out
  cv::resize(src_image, dest_image_thumb, cv::Size(100, 56), 0, 0, CV_INTER_AREA);
  cv::imwrite( argv[2], dest_image_thumb );

  // overwrites src_image
  cv::resize(src_image, dest_image_full, cv::Size(1024, 576), 0, 0, CV_INTER_CUBIC);
  cv::imwrite( argv[1], dest_image_full );

  exit(0);
}
