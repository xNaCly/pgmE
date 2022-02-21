/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */

#include <stdio.h>
#include "libs/pgm/_pgm.h"
#include "libs/image/_image.h"

// TODO: temporäre funktion entfernen
/**
 * @brief prints the width and height of the given image
 * @param img
 */
void print_image(Image *img) {
  printf("Breite: %d\nHöhe: %d\n", img->width, img->height);
}

int main(void) {
  //main_menu_handler();
  Image *img = loadImage("cat.pgm");
  print_image(img);

  // TODO: hier die funktionen testen.

  // *********************************

  Image *edited_img = threshold(img, 120);
  //Image *edited_img = laplace(img);


  //Image *edited_img = rotate(img, 45, 0);
  saveImage("test.pgm", edited_img);
  return 0;
}
