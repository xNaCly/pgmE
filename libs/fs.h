/* fs.h handles everything regarding images in the . */
#ifndef FS_H_INCLUDED
#define FS_H_INCLUDED


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
