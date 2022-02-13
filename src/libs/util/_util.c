#include <stdio.h>
#include "_util.h"

const char *MAIN_OPTIONS[] = {
	"Datei laden",
	"Datei speichern",
	"Exit"
};

const char *EDIT_OPTIONS[] = {
	"Median-Filter",
	"Gauß-Filter"
	"Laplace-Operator",
	"Schwellwertverfahren",
	"Bild skalieren",
	"Bild rotieren",
};

void print_image(Image *img, int print_pixels) {
  if(img == NULL) return;

  printf("width: %d, height: %d\n", img->width, img->height);

  if (print_pixels) {
	for (int i = 0; i < img->width; i++) {
	  for (int ii = 0; ii < img->height; ii++) {
		printf("%d, ", img->data[i][ii]);
	  }
	}
  }
}

void print_home(){
  for(int i = 0; i < sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]); i++){
	printf("[%d] %s\n", i, MAIN_OPTIONS[i]);
  }
}