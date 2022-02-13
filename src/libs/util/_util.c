#include <stdio.h>
#include <stdlib.h>
#include "_util.h"
#include "../pgm/_pgm.h"

const char *MAIN_OPTIONS[] = {
	"Datei laden",
	"Median-Filter",
	"Gauß-Filter",
	"Laplace-Operator",
	"Schwellwertverfahren",
	"Bild skalieren",
	"Bild rotieren",
	"Datei speichern",
	"Exit",
};

const int edited_unsaved_image_in_memory = 0;
const int image_in_memory = 0;
Image *img;

void throw_error(char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_RED, text, ANSI_RESET);
  exit(1);
}

void selection_handler(int selection) {
  if (selection == 0) {
	char *dateiname;

	printf("Dateiname (with .pgm): ");
	scanf("%s", &dateiname);

	img = loadImage(dateiname);

	if (img == NULL) {
	  throw_error("Datei konnte nicht geöffnet werden.");
	}
  } else if (selection == 1) {}
  else if (selection == 2) {}
  else if (selection == 3) {}
  else if (selection == 4) {}
  else if (selection == 5) {}
  else if (selection == 6) {}
  else if (selection == 7) {
	char *dateiname;

	printf("Dateiname (with .pgm): ");
	scanf("%s", &dateiname);

	int feedback = saveImage(dateiname, img);

	if (!feedback) {
	  throw_error("Datei konnte nicht gespeichert werden. (Fehler beim Speichern)");
	}
  }
}

void main_menu_handler() {
  int selection = 0;
  int arr_size = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

  // clear terminal window
  system("clear");

  printf("\nMain Menu:\n\n");
  for (int i = 0; i < arr_size; i++) {
	// loop over all options and print them
	printf("[%d] %s%s%s\n", i, ANSI_STYLE_BOLD, MAIN_OPTIONS[i], ANSI_RESET);
  }
  // input prompt for the selection
  printf("\nSelection (0-%d): ", arr_size - 1);

  // assign input to variable
  //TODO: use strtol
  scanf("%d", &selection);

  // check if selection is in allowed spectrum
  if (selection < 0 || selection > arr_size - 1) {
	char *error_text = "";
	sprintf(error_text, "Selection is not available, please input a number between 0 and %d.", arr_size - 1);
	throw_error(error_text);
  }

  if (selection == arr_size - 1) exit(0);

  // disallow editing and saving if there is no file in mem
  if (selection != 0 && !image_in_memory) {
	throw_error("No Image loaded into the program.");
  }

  selection_handler(selection);

}
