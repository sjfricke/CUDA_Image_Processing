#include "file.h"

using namespace std;

const int HEADER_SIZE = 8;

Pixel* fileRead(char* filename) {

  Pixel* data_stream;
  unsigned char* data_buffer;
  FILE * file;
  long file_size;
  size_t e_check;
  int file_height, file_width, data_size;
  int i;

  file = fopen( filename , "rb" );
  if (file==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek(file , 0 , SEEK_END);
  file_size = ftell(file);
  rewind(file);

  data_size = (int)file_size - HEADER_SIZE;

  // 8 bytes for header
  data_stream = (Pixel*) malloc( data_size );
  if (data_stream == NULL) {fputs ("Memory error",stderr); exit (2);}

  // reads in header detail and gets height and width
  data_buffer = (unsigned char*) malloc(HEADER_SIZE);
  if (data_buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  e_check = fread(data_buffer,1,HEADER_SIZE,file);
  if (e_check != HEADER_SIZE) {fputs ("Reading error",stderr); exit (3);}

  file_height = *((int*)data_buffer + 0);
  file_width =  *((int*)data_buffer + 1);

  e_check = fread(data_stream, 1, (data_size), file);
  if (e_check != data_size) {fputs ("Reading error",stderr); exit (3);}

  for (i = 0; i < 16; i++){
    printf("at %d: %04x\n", i, *(data_stream + (i * 3)));
    printf("\t r: %x g: %x b: %x\n", (*(data_stream +(i*3))).red, (*(data_stream +(i*3))).green, (*(data_stream +(i*3))).blue);
  }

  // terminate
  fclose(file);
  free(data_buffer);
  return data_stream;
}
