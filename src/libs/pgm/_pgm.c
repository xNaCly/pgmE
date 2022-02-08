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
  Image *cpImage = createImage(width, height, 1); // create empty image

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

int saveImage(char file_name[], Image *img_pointer) {
  // allocates the string in a big enough size
  char *PGM_content = (char *)malloc((img_pointer->height * img_pointer->width)*sizeof(int) + (3 * sizeof(int)) + (sizeof(char) * 3));
  //char *PGM_content = (char *)malloc((3 * sizeof(int)) + (sizeof(char) * 3));

 int offset = sprintf(PGM_content, "P2\n%d %d\n%d\n", img_pointer->width, img_pointer->height, MAX_BRIGHT);

  if (0 > offset)
    return 0;

  // TODO: this slows the app humongosly down
  // loops over every pixel and appends the pixel value as a string to PGM_content
  for (int i = 0; i < img_pointer->width; i++) {
    for (int ii = 0; ii < img_pointer->height; ii++) {
      // allocate temp string
      char t[5];

      // convert to string
      int size = sprintf(t, "%d\n", img_pointer->data[i][ii]);
      if (0 > size) {
        return 0;
      }
      memcpy(PGM_content + offset, t, size);

      offset += size;
      // append string
      // strcat(PGM_content, t);
    }
  }

  FILE *file;
  // open file with given name
  file = fopen(file_name, "w");

  // return 0 if file couldnt be created
  if (file == NULL) {
	return 0;
  }

  // insert content into file
  fputs(PGM_content, file);

  // free content
  free(PGM_content);
  return 1;
}
