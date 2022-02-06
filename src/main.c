#include <stdio.h>
#include "libs/pgm/_pgm.h"
#include "libs/image/_image.h"
#include "libs/util/_util.h"

int main(void) {
   Image *img = createImage(25,25,255);
   print_image_data(img, 0);
   Image *img2 = copyImage(img);
   print_image_data(img2, 0);
   freeImage(img);
   return 0;
}
