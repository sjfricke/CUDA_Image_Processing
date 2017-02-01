#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char** argv) {

  // check for parameter
  if (argc < 4) {
     fprintf(stderr, "%s\n", "Need to pass <file_src> <resize_dst> <data_dst>");
     exit(1);
  }

  int err_check; // used to check return value on functions
  FILE* data_file;
  unsigned char* data_stream;
  int* header_info;
  //  const unsigned char ZERO = 0;
  int buffer_size;

  // declare images
  cv::Mat src_image;
  cv::Mat dest_image;
  cv::Vec3b image_buffer;

  // read in image
  src_image = cv::imread( argv[1], CV_LOAD_IMAGE_COLOR );
  if ( !src_image.data ) {
    fprintf(stderr, "%s\n", "image was not read correctly");
    exit(1);
  }

  // resize image and writes it out
  cv::resize(src_image, dest_image, cv::Size(100, 56), 0, 0, CV_INTER_AREA);
  cv::imwrite( argv[2], dest_image );

  // makes sure all color is 0-255
  src_image.convertTo(src_image, CV_8U);

  header_info = (int*) malloc(sizeof(int) * 2);
  if (header_info == NULL) {
    fprintf(stderr, "%s\n", "header not malloced");
    exit(1);
  }

  *(header_info + 0) = src_image.rows;
  *(header_info + 1) = src_image.cols;

  data_file = fopen(argv[3], "wb");
  fwrite(header_info, sizeof(int), 2, data_file);

  // 3 bytes for each pixel of image
  //!! UNDID, TODO if needed:
  //   extra byte due to 4 byte aligning of bytes
  buffer_size = sizeof(unsigned char) * src_image.cols * src_image.rows * 3;

  data_stream = (unsigned char*) malloc(buffer_size);
  if (data_stream == NULL) {
     fprintf(stderr, "%s\n", "failed to malloc stream");
     exit(1);
  }

  printf("Width: %d\tHeight: %d\tsize: %d\n", src_image.cols, src_image.rows, buffer_size);

  // create data stream
  // CV holds color as BGR
  for(int i = 0; i < src_image.rows; i++) {
      for(int j = 0; j < src_image.cols; j++) {
        image_buffer = src_image.at<cv::Vec3b>(i,j);
	*(data_stream + ((((src_image.cols * i) + j) * 3) + 0)) = image_buffer[0];
	*(data_stream + ((((src_image.cols * i) + j) * 3) + 1)) = image_buffer[1];
	*(data_stream + ((((src_image.cols * i) + j) * 3) + 2)) = image_buffer[2];
//	*(data_stream + ((((src_image.cols * i) + j) * 4) + 3)) = ZERO;
    }
  }

  fwrite(data_stream, sizeof(unsigned char), buffer_size, data_file);

  fclose(data_file);

  free(data_stream);

  exit(0);
}
