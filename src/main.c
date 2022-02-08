#include <stdio.h>
#include "libs/pgm/_pgm.h"
#include "libs/image/_image.h"
#include "libs/util/_util.h"

int main(void) {
  Image *img = createImage(1920, 1080, 255);

  //Image *img2 = copyImage(img);
  //print_image(img2, 0);

  saveImage("test.pgm", img);

  freeImage(img);
  return 0;
}
