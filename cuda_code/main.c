#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>


int main(int argc, char** argv) {
    printf("arg1: %s\narg2: %s\narg3: %s\n", argv[1], argv[2], argv[3]);

//initialization...
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

  //set the source of compressed jpegs....
  //??

  //get image info..
  //jpeg_read_header(, TRUE);

  //start decompression
    jpeg_start_decompress(&cinfo);

  //image properties and such
    int width = cinfo.output_width;
    int height = cinfo.output_height;
  //......

  //Read decompressed image data
    jpeg_read_scanlines(&cinfo, );



    jpeg_finish_decompress();













}
