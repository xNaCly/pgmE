#ifndef _IMAGE_H_INCLUDED
#define _IMAGE_H_INCLUDED
#include "../pgm/_pgm.h"

//! All methods in this file need to modifiy a copy of the original image, not the og


/**
 * Applies the median filter to the given image
 * @param img
 */
void median(Image *img);

/**
 * Applies the gauss filter to the given image
 * @param img
 */
void gauss(Image *img);

/**
 * Modifies the image using the laplace-operator
 * @param img
 */
void laplace(Image *img);

/**
 * Modifies the Image using the Thresholding method
 * @param img
 * @param threshold
 */
void threshold(Image *img, int threshold);

/**
 * Scales the given Image to the width and height specified
 * @param img
 * @param width
 * @param height
 */
void scale(Image *img, int width, int height);

/**
 * Rotates the Image to the given angle
 * @param img
 * @param angle
 */
void rotate(Image *img, double angle);
#endif
