#include "p_pgm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Image *createImage(int width, int height, int default_brightness,
                   char *image_name) {
  Image *img;
  img = malloc(sizeof *img);

  img->width = width;
  img->height = height;
  img->name = image_name;

  // allocate double pointer to contain pointers
  img->data = (int **)malloc(height * sizeof(int *));

  // loop over columns
  for (int i = 0; i < height; i++) {
    // allocate rows
    img->data[i] = (int *)malloc(width * sizeof(int));

    // loop over row items
    for (int ii = 0; ii < width; ii++) {
      // assign default value to every pixel
      img->data[i][ii] = default_brightness;
    }
  }

  return img;
}

void freeImage(Image **img) {
  if (*img == NULL) return; // avoid double free
  for(int i = 0; i < (*img)->height; i++){
    free((*img)->data[i]); // loop over pointers to free them
  }
  free((*img)->data); // free pointer pointer 

  free(*img);   // free memory taken up by pointer
  *img = NULL;  // set pointer NULL to prevent it pointing to a random
  // memory adress
}

Image *copyImage(Image *img) {
  int width = img->width;
  int height = img->height;
  Image *cpImage = createImage(width, height, 1, img->name);

  // loop over columns
  for (int i = 0; i < height; i++) {
    // loop over row items
    for (int ii = 0; ii < width; ii++) {
      // deep copy values
      cpImage->data[i][ii] = img->data[i][ii];
    }
  }

  return cpImage;
}

Image *loadImage(char *file_name) {
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

  Image *img = createImage(width, height, brightness, file_name);

  for (int i = 0; i < height; i++) {
    for (int ii = 0; ii < width; ii++) {
      // push all pixel values into the data field
      fscanf(file, "%d", &img->data[i][ii]);
    }
  }

  fclose(file);
  return img;
}

int saveImage(const char *file_name, Image *img_pointer) {
  // open file with given name
  FILE *file = fopen(file_name, "w");

  // return 0 if file couldn't be created
  if (file == NULL) {
    return 0;
  }

  // print first 4 lines to file
  fprintf(file, "P2\n%d %d\n%d\n", img_pointer->width, img_pointer->height,
          MAX_BRIGHT);

  // loops over every pixel and appends the value to the file
  for (int i = 0; i < img_pointer->height; i++) {
    for (int ii = 0; ii < img_pointer->width; ii++) {
      fprintf(file, "%d\n", img_pointer->data[i][ii]);
    }
  }

  fclose(file);
  return 1;
}
