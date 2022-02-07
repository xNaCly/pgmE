/*
 * _pgm.h handles everything regarding images in the .pgm standard
 * http://netpbm.sourceforge.net/doc/pgm.html (Plain PGM)
 */
#ifndef _PGM_H_INCLUDED
#define _PGM_H_INCLUDED

typedef struct
{
  int width;
  int height;
  int **data; // 2d pointer: Brightness values
} Image;

// creates Image with given width, height and brightness
Image *createImage(int width, int height, int default_brightness);

// frees the memory taken up by the given Image pointer
void freeImage(Image *img_pointer);

// copys the image from the given pointer to a new pointer
Image *copyImage(Image *img_pointer);

// loads image from filesystem with given file name (without extension)
Image *loadImage(char file_name[]);

// saves the given pointer in a .pgm file with the given name
int saveImage(char file_name[], Image *img_pointer);

#endif
