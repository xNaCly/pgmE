/*
 * _util.h provides utility methods
 */
#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include "../pgm/_pgm.h"

// ---------- Coloring the output -----------
#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_STYLE_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"
// ---------- ------------------- -----------

// enables the switch case which contains the main menu
// (basically just used to compare to the user input)
enum {
  SELECTION_LOAD = 0,
  SELECTION_MEDIAN_FILTER,
  SELECTION_GAUSS_FILTER,
  // SELECTION_LAPLACE_OPERATOR, // INFO: discontinued
  SELECTION_THRESHOLD,
  SELECTION_SCALE,
  SELECTION_ROTATE,
  SELECTION_SAVE,
  SELECTION_EXIT,  
  SELECTION_INVALID =
      9999 // Error code 
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
void throw_error(const char* text);

/**
 * @brief prints the given text highlighted yellow, differs from throw_error by
 * not exiting the program.
 * @param text
 */
void throw_warning(const char* text);

/**
 * @brief checks if the selection meets certian criteria
 * @param selection
 * @param arr_size size of the array containing possible inputs
 * @param edited_unsaved_image_in_memory
 * @param image_in_memory
 */
int check_is_option_valid(int selection, int image_in_memory);
#endif
