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

  img->data = (int **)malloc(height * sizeof(int *));

  for (int i = 0; i < height; i++) {
    img->data[i] = (int *)malloc(width * sizeof(int));

    for (int ii = 0; ii < width; ii++) {
      img->data[i][ii] = default_brightness;
    }
  }

  return img;
}

void freeImage(Image **img) {
  if (*img == NULL) return; 
  for(int i = 0; i < (*img)->height; i++){
    free((*img)->data[i]); 
  }
  free((*img)->data); 

  free(*img);   
  *img = NULL; 
}

Image *copyImage(Image *img) {
  int width = img->width;
  int height = img->height;
  Image *cpImage = createImage(width, height, 1, img->name);

  for (int i = 0; i < height; i++) {
    for (int ii = 0; ii < width; ii++) {
      cpImage->data[i][ii] = img->data[i][ii];
    }
  }

  return cpImage;
}

Image *loadImage(char *file_name) {
  FILE *file = fopen(file_name, "r");

  if (file == NULL) return NULL;

  char pgm_prefix = getc(file);
  int pgm_version = 0;

  int width = 0;
  int height = 0;
  int brightness = 1;

  fscanf(file, "%d\n", &pgm_version);

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
      fscanf(file, "%d", &img->data[i][ii]);
    }
  }

  fclose(file);
  return img;
}

int saveImage(const char *file_name, Image *img_pointer) {
  char file_name_[255];
  sprintf(file_name_, "pgme_%s", file_name);
  FILE *file = fopen(file_name, "w");

  if (file == NULL) {
    return 0;
  }

  fprintf(file, "P2\n%d %d\n%d\n", img_pointer->width, img_pointer->height,
          MAX_BRIGHT);

  for (int i = 0; i < img_pointer->height; i++) {
    for (int ii = 0; ii < img_pointer->width; ii++) {
      fprintf(file, "%d\n", img_pointer->data[i][ii]);
    }
  }

  fclose(file);
  return 1;
}
