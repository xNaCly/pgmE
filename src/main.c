#include <stdio.h>
#include "libs/pgm/_pgm.h"
#include "libs/image/_image.h"

// TODO: temporäre funktion entfernen
void print_image(Image *img) {
  printf("Breite: %d\nHöhe: %d\n", img->width, img->height);
}

int main(void) {
  //main_menu_handler();
  Image *img = loadImage("cat.pgm");
  print_image(img);

  // TODO: hier die funktionen testen.
  Image *edited_img = rotate(img, 180, 255);
  saveImage("test.pgm", edited_img);
  return 0;
}
