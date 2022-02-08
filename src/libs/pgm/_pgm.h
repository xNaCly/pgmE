/*
 * _pgm.h handles everything regarding images in the .pgm standard
 * http://netpbm.sourceforge.net/doc/pgm.html (Plain PGM)
 */
#ifndef _PGM_H_INCLUDED
#define _PGM_H_INCLUDED

#define MAX_BRIGHT 255

typedef struct
{
  int width;
  int height;
  int **data; // 2d pointer: Brightness values
} Image;

/**
 * creates an Image with given width and height, set every pixel to the default_brightness
 * @param width
 * @param height
 * @param default_brightness
 * @return *Image
 */
Image *createImage(int width, int height, int default_brightness);

/**
 * frees the memory taken up by the given Image pointer
 * @param img_pointer Image pointer created with createImage()
 */
void freeImage(Image *img_pointer);

/**
 * copys the image from the given pointer to a new pointer
 * @param img_pointer Image pointer created with createImage()
 * @return *Image
 */
Image *copyImage(Image *img_pointer);

/**
 * loads image from filesystem with given file name (without extension)
 * @param file_name
 * @return *Image
 */
Image *loadImage(char file_name[]);

/**
 * saves the given pointer in a .pgm file with the given name
 * @param file_name
 * @param img_pointer Image pointer created with createImage()
 * @return 0 or 1
 */
int saveImage(char file_name[], Image *img_pointer);

#endif
