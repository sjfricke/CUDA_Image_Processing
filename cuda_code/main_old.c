#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv) {
    printf("arg1: %s\narg2: %s\narg3: %s\n", argv[1], argv[2], argv[3]);

    int rc;
    int width;
    int height;
    int line;

    //Variables for the source jpg
    struct stat file_info;
    unsigned  long jpg_size;
    unsigned  char *jpg_buffer;

    //output variables
    unsigned long bmp_size;
    unsigned char *bmp_buffer;
    int row_stride, pixel_size;


    //initialization of decompression
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    //getting data from file
    rc = stat(argv[1], &file_info);
    if (rc) {
        fprintf(stderr, "ERROR: %s", "stat failed\n");
    }
    jpg_size = file_info.st_size;
    jpg_buffer = (unsigned char*)malloc(jpg_size + 100);
    if (jpg_buffer == NULL) {
        fprintf(stderr, "ERROR: %s", "malloc couldn't allocate buffer\n");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);

    rc = jpeg_read_header(&cinfo, TRUE);
    if (rc) {
        fprintf(stderr, "ERROR: %s", "couldn't read header\n");
    }

    //start decompression
    jpeg_start_decompress(&cinfo);

  //image properties and such
    width = cinfo.output_width;
    height = cinfo.output_height;
    line = cinfo.output_scanline;
  //......
    printf("Image is %d by %d with %d components\n", width, height, pixel_size);

    jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);
    free(jpg_buffer);












}
