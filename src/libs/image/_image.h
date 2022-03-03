/**
 * @file _image.h
 * @author xnacly
 * @brief includes several image manipulation methods
 * @date 2022-02-21
 */

#ifndef _IMAGE_H_INCLUDED
#define _IMAGE_H_INCLUDED
#include "../pgm/_pgm.h"
// used for: copyImage, createImage

#define PI 3.141592

/**
 * @brief Applies the median filter to the given image
 * @param img
 */
Image *median(Image *img);

/**
 * @brief Applies the gauss filter to the given image
 * @param img
 */
Image *gauss(Image *img);

/**
 * @brief Modifies the image using the laplace-operator
 * @param img
 */
Image *laplace(Image *img);

/**
 * @brief Modifies the Image using the thresholding method
 * @param img
 * @param threshold
 */
Image *threshold(Image *img, int threshold);

/**
 * @brief Scales the given Image to the width and height specified
 * @param img
 * @param width
 * @param height
 */
Image *scale(Image *img, int width, int height);

/**
 * @brief Rotates the Image to the given angle
 * @param img
 * @param angle
 * @param brigthness
 */
Image *rotate(Image *img, double angle, int brigthness);
#endif
