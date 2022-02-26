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

int check_is_option_valid(int selection, int image_in_memory) {
  if(selection > SELECTION_EXIT) {
    return SELECTION_INVALID;
  }
  // disallow editing and saving if there is no file in mem
  if (selection != 0 && selection != SELECTION_EXIT && !image_in_memory) {
    throw_warning("No Image loaded into the program.");
    return SELECTION_INVALID;
  }
  return selection;
}
