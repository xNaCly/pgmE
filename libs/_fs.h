/*
fs.h handles everything regarding images in the .pgm standard
http://netpbm.sourceforge.net/doc/pgm.html (Plain PGM)
*/
#ifndef _FS_H_INCLUDED
#define _FS_H_INCLUDED


typedef struct
{
  int width;
  int height;
  int **data; // 2d pointer: Brightness values
} Image;

/* Image manipulation methods */
Image* createImage(int width, int height, int default_brightness){}

void freeImage(Image* img_pointer){}

Image* copyImage(Image* img_pointer){}

Image* loadImage(char datei_name[]){}

int saveImage(char datei_name[], Image* img_pointer){}

#endif
