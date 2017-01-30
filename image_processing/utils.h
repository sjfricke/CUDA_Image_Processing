
#ifndef UTILS_H__
#define UTILS_H__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <vector>
#include <cstdlib>

typedef struct _Pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} Pixel;

Pixel* add_values(Pixel* image_data, int width, int height, int image_count);

extern std::vector<Pixel> IMAGE_DATA;

extern std::vector<cv::Mat> IMAGE_FILES;

#endif
