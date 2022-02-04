#include "_pgm.h"
#include <stdlib.h>
#include <stdio.h>

Image *createImage(int width, int height, int default_brightness){
  Image *img = malloc(sizeof *img);
  int **data[height][width];

  img->width = width;
  img->height = height;

  for(int i = 0; i < height; i++) {
	for(int ii = 0; ii < width; ii++){
	  data[i][ii] = default_brightness;
	}
  }

  img->data = data;

  return img;
}
void freeImage(Image *img_pointer);
Image *copyImage(Image *img_pointer);
Image *loadImage(char file_name[]);
int saveImage(char file_name[], Image *img_pointer);
