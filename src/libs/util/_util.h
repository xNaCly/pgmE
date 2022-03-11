/*
 * _util.h provides utility methods
 */
#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include "../pgm/_pgm.h"

#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_STYLE_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"

enum {
  SELECTION_LOAD = 0,
  SELECTION_MEDIAN_FILTER,
  SELECTION_GAUSS_FILTER,
  // SELECTION_LAPLACE_OPERATOR,
  SELECTION_THRESHOLD,
  SELECTION_SCALE,
  SELECTION_ROTATE,
  SELECTION_SAVE,
  SELECTION_EXIT,  // ALWAYS LATEST AVAILABLE OPTION ;)
  SELECTION_INVALID =
      9999  // MAKE SURE THAT THIS WILL RUN INTO THE INVALID SECTION ;)
};

/**
 * used for qsort
 * @param a
 * @param b
 * @return
 */
int compare(const void *a, const void *b);

/**
 * @brief converts string to integer
 * @param text
 * @return integer
 */
int toInt(const char *text);

/**
 * @brief exits the program and prints the given text highlighted red
 * @param text
 */
void throw_error(char text[]);

/**
 * @brief prints the given text highlighted yellow, differs from throw_error by
 * not exiting the program.
 * @param text
 */
void throw_warning(char text[]);

/**
 * @brief checks if the selection meets certian criteria
 * @param selection
 * @param arr_size size of the array containing possible inputs
 * @param edited_unsaved_image_in_memory
 * @param image_in_memory
 */
int check_is_option_valid(int selection, int image_in_memory);
#endif
