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

#define clear() system("clear")

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
void check_selection(int selection, int arr_size, int edited_unsaved_image_in_memory, int image_in_memory);
#endif
