#include "_util.h"
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  if (int_a == int_b)
    return 0;
  else if (int_a < int_b)
    return -1;
  else
    return 1;
}

int toInt(const char *text) {
  char *ptr;
  long l;

  l = strtol(text, &ptr, 10);

  return (int)l;
}

void throw_error(char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_RED, text, ANSI_RESET);
  exit(1);
}

void throw_warning(char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_YELLOW, text, ANSI_RESET);
}

int check_is_option_valid(int selection, int image_in_memory) {
  if (selection > SELECTION_EXIT) {
    return SELECTION_INVALID;
  }
  // disallow editing and saving if there is no file in mem
  if (selection != 0 && selection != SELECTION_EXIT && !image_in_memory) {
    throw_warning("No Image loaded into the program.");
    return SELECTION_INVALID;
  }
  return selection;
}
