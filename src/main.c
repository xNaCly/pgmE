#include <stdio.h>
#include "libs/pgm/_pgm.h"
//#include "libs/util/_util.h"

// TODO: tempräre funktion entfernen
void print_image(Image *img) {
  printf("Breite: %d\nHöhe: %d", img->width, img->height);
}

int main(void) {
	//main_menu_handler();
  Image *img = loadImage("cat.pgm");
  print_image(img);

	// TODO: hier die funktionen testen.

  return 0;
}
