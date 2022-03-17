#include "p_util.h"

#include <stdio.h>
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <string.h>  // strcmp

double toDouble(const char *text) {
  char *ptr;
  long l;

  l = strtod(text, &ptr);

  // checks if text and rest after conversion from strtol is equal,
  // meaning no int was in text
  if (strcmp(text, ptr) == 0) {
    return SELECTION_INVALID;
  }

  return l;
}

int toInt(const char *text) {
  char *ptr;
  long l;

  l = strtol(text, &ptr, 10);

  // checks if text and rest after conversion from strtol is equal,
  // meaning no int was in text
  if (strcmp(text, ptr) == 0) {
    return SELECTION_INVALID;
  }

  return (int)l;
}

void throw_error(const char *text) {
  printf("%s%s%s\n", ANSI_COLOR_RED, text, ANSI_RESET);
  exit(EXIT_FAILURE);
}

void throw_warning(const char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_YELLOW, text, ANSI_RESET);
}

int check_is_option_valid(int selection, int image_in_memory) {
  // selection mustn't be bigger than the last option
  if (selection > SELECTION_EXIT) {
    return SELECTION_INVALID;
  }

  // disallow editing and saving if there is no file in mem
  if (selection != 0 && selection != SELECTION_EXIT && !image_in_memory) {
    throw_warning("Bild bearbeiten ohne Bild im Speicher nicht möglich.");
    return SELECTION_INVALID;
  }
  return selection;
}
