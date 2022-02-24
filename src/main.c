/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */

#include <stdio.h>
#include <stdlib.h>
#include "libs/pgm/_pgm.h"
#include "libs/util/_util.h"
#include "libs/image/_image.h"

void main_menu(int edited_unsaved_image_in_memory, int image_in_memory) {
  const char *MAIN_OPTIONS[] = {
	  "Datei laden", "Median-Filter", "Gauß-Filter",
	  "Laplace-Operator", "Schwellwertverfahren", "Bild skalieren",
	  "Bild rotieren", "Datei speichern", "Exit",
  };
  const int arr_size = (sizeof MAIN_OPTIONS / sizeof MAIN_OPTIONS[0]) - 1;

  int selection = 0;

  while (selection != 8) {
	printf("\nMain Menu:\n\n");
	for (int i = 0; i < sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]); i++) {
	  // loop over all options and print them
	  printf("[%d] %s%s%s\n", i, ANSI_STYLE_BOLD, MAIN_OPTIONS[i], ANSI_RESET);
	}

	if (!image_in_memory)
	  printf("%s\nNo Image in ram!%s\n", ANSI_COLOR_RED, ANSI_RESET);

	// input prompt for the selection
	printf("\nSelection (0-%d): ", arr_size);

	// assign input to variable
	// TODO: use strtol
	scanf("%d", &selection);

	if (selection == arr_size) {
	  if (!edited_unsaved_image_in_memory) {
		exit(0);
	  }
	  printf("%sThere is still an unsaved editied image in memory, save it before exiting%s\n",
			 ANSI_COLOR_RED,
			 ANSI_RESET);
	}

	check_selection(selection, arr_size, edited_unsaved_image_in_memory, image_in_memory);

	Image *img = NULL;

	if (selection == 0) {
	  printf("[%d] %s\n", 0, MAIN_OPTIONS[0]);
	  char dateiname[255] = ""; // size: 255 due to the maximum file length

	  //clear();
	  printf("Dateiname (with .pgm): ");
	  scanf("%s", dateiname);

	  img = loadImage(dateiname);

	  if (img == NULL) {
		throw_error("Datei konnte nicht geöffnet werden.");
	  }

	  //clear();
	  printf("%s%s wurde eingelesen.%s\n", ANSI_COLOR_GREEN, dateiname,
			 ANSI_RESET);
	  image_in_memory = 1;
	} else if (selection == 1) {
	  edited_unsaved_image_in_memory = 1;
	} else if (selection == 2) {
	  edited_unsaved_image_in_memory = 1;
	} else if (selection == 3) {
	  edited_unsaved_image_in_memory = 1;
	} else if (selection == 4) {
	  edited_unsaved_image_in_memory = 1;
	} else if (selection == 5) {
	  edited_unsaved_image_in_memory = 1;
	} else if (selection == 6) {
	  printf("[%d] %s\n", 6, MAIN_OPTIONS[6]);

	  float angle = 0;
	  int brightness = MAX_BRIGHT;

	  //clear();
	  printf("Winkel um den das Bild gedreht werden soll: ");
	  scanf("%f", &angle);

	  printf("Helligkeit mit der freiliegende Pixel gefüllt werden sollen: ");
	  scanf("%d", &brightness);

	  // this has a warning, currently no idea how to fix this
	  img = rotate(img, angle, brightness);

	  //clear();
	  printf("%sBild wurde um %f-Grad im Uhrzeigersinn gedreht.%s\n",
			 ANSI_COLOR_GREEN, angle, ANSI_RESET);
	  edited_unsaved_image_in_memory = 1;
	} else if (selection == 7) {
	  char dateiname[255];

	  //clear();
	  printf("Dateiname (with .pgm): ");
	  scanf("%s", dateiname);

	  int feedback = saveImage(dateiname, img);

	  if (!feedback) {
		throw_error(
			"Datei konnte nicht gespeichert werden. (Fehler beim Speichern)");
	  }

	  freeImage(img);

	  edited_unsaved_image_in_memory = 0;
	  image_in_memory = 0;

	  //clear();
	  printf("%sBild wurde als: %s gespeichert.%s\n", ANSI_COLOR_GREEN, dateiname,
			 ANSI_RESET);
	}
  }

}

int main(void) {
  int edited_image_in_memory = 0;
  int image_in_memory = 0;
  main_menu(edited_image_in_memory, image_in_memory);

  //Image *img = loadImage("cat.pgm");
  //print_image(img);

  // TODO: hier die funktionen testen.
  // *********************************

  //Image *edited_img = threshold(img, 120);
  //Image *edited_img = laplace(img);
  //Image *edited_img = rotate(img, 80, 0);
  //saveImage("test.pgm", edited_img);
  return 0;
}
