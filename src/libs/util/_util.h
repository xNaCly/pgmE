/*
 * _util.h provides utility methods
 */
#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include "../pgm/_pgm.h"


#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_STYLE_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"

extern const char *MAIN_OPTIONS[];

/**
 * @brief exits the program and prints the given text highlighted
 * @param text
 */
void throw_error(char text[]);

/**
 * @brief Prints the main (home) selection menu
 */
void main_menu_handler();

/**
 * @brief Runs methods based on given selection
 * @param selection
 */
void selection_handler(int selection);
#endif
