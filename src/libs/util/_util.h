/*
 * _util.h provides utility methods
 */
#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include "../pgm/_pgm.h"

extern const char *MAIN_OPTIONS[];

extern const char *EDIT_OPTIONS[];

/**
 *
 * @param img Image pointer created with createImage()
 * @param print_pixels flag if pixel values should be printed
 */
void print_image(Image *img, int print_pixels);

/**
 * Prints the main (home) selection menu
 */
void print_home(void);

#endif
