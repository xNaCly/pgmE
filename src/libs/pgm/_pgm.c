#include "_pgm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
  Image *cpImage = createImage(width, height, 1);

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

Image *loadImage(char file_name[]) {
  // open file in read mode
  FILE *file = fopen(file_name, "r");

  // if opening the file failed return NULL
  if (file == NULL) return NULL;

  // get first char of the file
  char pgm_prefix = getc(file);
  int pgm_version = 0;

  int width = 0;
  int height = 0;
  int brightness = 1;

  // get first int of the file
  fscanf(file, "%d\n", &pgm_version);

  // check if first line of the file conforms to the pgm standard
  if (pgm_prefix != 'P' || pgm_version != 2) {
	return NULL;
  }

  fscanf(file, "%d", &width);
  fscanf(file, "%d", &height);
  fscanf(file, "%d", &brightness);

  if (width <= 0 || height <= 0 || brightness <= 0) {
	return NULL;
  }

  Image *img = createImage(width, height, 255);

  for(int i = 0; i < width; i++){
	for(int ii = 0; ii < height; ii++){
	  fscanf(file, "%d", &img->data[i][ii]);
	}
  }

  fclose(file);
  return img;
}

int saveImage(char file_name[], Image *img_pointer) {
  // open file with given name
  FILE *file = fopen(file_name, "w");

  // return 0 if file couldn't be created
  if (file == NULL) {
	return 0;
  }

  // print first 4 lines to file
  fprintf(file,
		  "P2\n%d %d\n%d\n",
		  img_pointer->width,
		  img_pointer->height,
		  MAX_BRIGHT);

  // loops over every pixel and appends the value to the file
  for (int i = 0; i < img_pointer->width; i++) {
	for (int ii = 0; ii < img_pointer->height; ii++) {
	  fprintf(file, "%d\n", img_pointer->data[i][ii]);
	}
  }

  fclose(file);

  return 1;
}
