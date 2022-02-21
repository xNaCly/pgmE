#ifndef _IMAGE_H_INCLUDED
#define _IMAGE_H_INCLUDED
#include "../pgm/_pgm.h"

//TODO: INFO methods in this file need to modifiy a copy of the original image, not the og

#define PI 3.14159265359

/**
 * Applies the median filter to the given image
 * @param img
 */
Image *median(Image *img);

/**
 * Applies the gauss filter to the given image
 * @param img
 */
Image *gauss(Image *img);

/**
 * Modifies the image using the laplace-operator
 * @param img
 */
Image *laplace(Image *img);

/**
 * Modifies the Image using the thresholding method
 * @param img
 * @param threshold
 */
Image *threshold(Image *img, int threshold);

/**
 * Scales the given Image to the width and height specified
 * @param img
 * @param width
 * @param height
 */
Image *scale(Image *img, int width, int height);

/**
 * Rotates the Image to the given angle
 * @param img
 * @param angle
 * @param brigthness
 */
Image *rotate(Image *img, double angle, int brigthness);
#endif
