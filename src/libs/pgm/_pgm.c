#include "_pgm.h"
#include <stdlib.h>
#include <stdio.h>

Image *createImage(int width, int height, int default_brightness) {
  Image *img;
  img = malloc(sizeof *img);

  img->width = width;
  img->height = height;

  img->data = (int **)malloc(width * sizeof(int *)); // allocate double pointer to contain pixel data

  for (int i = 0; i < width; i++) { // loop over columns
	img->data[i] = (int *)malloc(height * sizeof(int)); // allocate rows

	for (int ii = 0; ii < height; ii++) { 	// loop over row items
	  img->data[i][ii] = default_brightness; // assign default value to every pixel
	}
  }

  return img;
}

void freeImage(Image *img_pointer) {
  free(img_pointer); // free memory taken up by pointer
  img_pointer = NULL; // set pointer NULL to prevent it pointing to a random memory adress
}

Image *copyImage(Image *img_pointer) {
  Image *copiedImage = img_pointer; // easiest way to copy a pointer is by passing its value to a new pointer

  return copiedImage;
}

Image *loadImage(char file_name[]);
int saveImage(char file_name[], Image *img_pointer);
