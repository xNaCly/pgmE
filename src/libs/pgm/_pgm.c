#include "_pgm.h"
#include <stdlib.h>
#include <stdio.h>

Image *createImage(int width, int height, int default_brightness){
  Image *img;
  img = malloc(sizeof *img);

  img->width = width;
  img->height = height;

  img->data = (int **) malloc(width*sizeof(int *));

  for(int i = 0; i < width; i++){
    img->data[i] = (int *) malloc(height*sizeof(int));
    for(int ii = 0; ii < height; ii++){
      img->data[i][ii] = default_brightness;
    }
  }

  return img;
}

void freeImage(Image *img_pointer){
  free(img_pointer);
  img_pointer = NULL;
}

Image *copyImage(Image *img_pointer){
  Image *copiedImage = img_pointer;

  return copiedImage;
}

Image *loadImage(char file_name[]);
int saveImage(char file_name[], Image *img_pointer);
