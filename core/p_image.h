/**
 * @file _image.h
 * @author xnacly
 * @brief includes several image manipulation methods
 * @date 2022-02-21
 */

#ifndef P_IMAGE_H_INCLUDED
#define P_IMAGE_H_INCLUDED
#include "p_pgm.h"   // used for: copyImage, createImage
#include "p_util.h"  // used for: compare

#define PI 3.141592  // needed for rotation

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
Image *laplace(
    Image *img);  // INFO: this method was overthrown due to a wrong formular

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
