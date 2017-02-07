
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
#include <stdint.h>

typedef struct _Pixel {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} Pixel;

Pixel* average_linear_cuda(Pixel* image_data, int width, int height, int image_count);

#endif
