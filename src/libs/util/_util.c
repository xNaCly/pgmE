#include "_util.h"
#include <stdio.h>
#include <stdlib.h>

void throw_error(char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_RED, text, ANSI_RESET);
  exit(1);
}

void throw_warning(char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_YELLOW, text, ANSI_RESET);
}

void check_selection(int selection, int arr_size, int edited_unsaved_image_in_memory, int image_in_memory) {
  // check if selection is in allowed spectrum
  if (selection < 0 || selection > arr_size - 1) {
	char *error_text = "";
	//clear();
	sprintf(
		error_text,
		"Selection is not available, please input a number between 0 and %d.",
		arr_size - 1);
	throw_warning(error_text);
  }

  // disallow editing and saving if there is no file in mem
  if (selection != 0 && !image_in_memory) {
	//clear();
	throw_warning("No Image loaded into the program.");
  }
}
