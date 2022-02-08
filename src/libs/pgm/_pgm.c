#include "_pgm.h"
#include <stdlib.h>
#include <stdio.h>

Image *createImage(int width, int height, int default_brightness) {
  Image *img;
  img = malloc(sizeof *img);

  img->width = width;
  img->height = height;

  // allocate double pointer to contain pixel data
  img->data = (int **)malloc(width * sizeof(int *));

  // loop over columns
  for (int i = 0; i < width; i++) {
	// allocate rows
	img->data[i] = (int *)malloc(height * sizeof(int));

	// loop over row items
	for (int ii = 0; ii < height; ii++) {
	  // assign default value to every pixel
	  img->data[i][ii] = default_brightness;
	}
  }

  return img;
}

void freeImage(Image *img_pointer) {
  free(img_pointer); // free memory taken up by pointer
  img_pointer = NULL; // set pointer NULL to prevent it pointing to a random memory adress
}

Image *copyImage(Image *img_pointer) {
  int width = img_pointer->width;
  int height = img_pointer->height;
  Image *cpImage = createImage(width, height, 255); // create empty image

  // loop over columns
  for (int i = 0; i < width; i++) {
	// loop over row items
	for (int ii = 0; ii < height; ii++) {
	  // deep copy values
	  cpImage->data[i][ii] = img_pointer->data[i][ii];
	}
  }

  return cpImage;
}

// TODO: needs implementing
Image *loadImage(char file_name[]);
// TODO: needs implementing
int saveImage(char file_name[], Image *img_pointer);
