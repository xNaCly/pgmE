#include "libs/pgm/_pgm.h"
#include "libs/util/_util.h"

int main(void) {
  Image *img = loadImage("cat.pgm");
  saveImage("test.pgm", img);

  return 0;
}
