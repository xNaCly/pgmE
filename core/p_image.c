#include "p_image.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>  // malloc

/**
 * used for qsort
 * @param a
 * @param b
 * @return int
 */
static int compare(const void *a, const void *b) {
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  if (int_a == int_b)
    return 0;
  else if (int_a < int_b)
    return -1;
  else
    return 1;
}

Image *median(Image *img) {
  Image *imgCpy = copyImage(img);
  for (int i = 0; i < imgCpy->height; i++) {
    for (int j = 0; j < imgCpy->width; j++) {
      // ignore pixels at the border of the image
      if (i < 2 || j < 2 || i >= imgCpy->height - 2 || j >= imgCpy->width - 2)
        continue;

      // fill a field with the 8 surrounding pixels
      int surNums[9] = {imgCpy->data[i - 1][j + 1], imgCpy->data[i][j + 1],
                        imgCpy->data[i + 1][j + 1], imgCpy->data[i - 1][j],
                        imgCpy->data[i][j],         imgCpy->data[i + 1][j],
                        imgCpy->data[i - 1][j - 1], imgCpy->data[i][j - 1],
                        imgCpy->data[i + 1][j - 1]};

      // sort the array
      int lenght = sizeof(surNums) / sizeof(int);
      qsort(surNums, lenght, sizeof(int), compare);

      // access median value
      int m_pixel = surNums[4];

      // set pixel to median:
      imgCpy->data[i][j] = m_pixel;
    }
  }
  return imgCpy;
}

Image *gauss(Image *img) {
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
    for (int j = 0; j < imgCpy->width; j++) {
      // ignore pixels at the border of the image
      if (i < 2 || j < 2 || i >= imgCpy->height - 2 || j >= imgCpy->width - 2)
        continue;

      imgCpy->data[i][j] =
          ((imgCpy->data[i - 1][j - 1]) + (2 * imgCpy->data[i][j - 1]) +
           (imgCpy->data[i + 1][j - 1]) + (2 * imgCpy->data[i - 1][j]) +
           (4 * imgCpy->data[i][j]) + (2 * imgCpy->data[i + 1][j]) +
           (imgCpy->data[i - 1][j + 1]) + (2 * imgCpy->data[i][j + 1]) +
           (imgCpy->data[i + 1][j + 1])) /
          16;
    }
  }

  return imgCpy;
}

Image *laplace(Image *img) {
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
    for (int j = 0; j < imgCpy->width; j++) {
      // ignore pixels at the border of the image
      if (i < 2 || j < 2 || i >= imgCpy->height - 2 || j >= imgCpy->width - 2)
        continue;

      int value = (img->data[i - 1][j - 1] + img->data[i][j - 1] +
                   img->data[i + 1][j - 1] + img->data[i - 1][j] -
                   (8 * img->data[i][j]) + img->data[i + 1][j] +
                   img->data[i - 1][j + 1] + img->data[i][j + 1] +
                   img->data[i + 1][j + 1]);

      imgCpy->data[i][j] = value < 0 ? 0 : value;
    }
  }

  return imgCpy;
}

Image *threshold(Image *img, int threshold) {
  // threshold higher than MAX_BRIGHT and lower than 1 doesnt make sense,
  // therefore update threshold to reasonable values
  if (threshold < 1) {
    printf("threshold was too small, was set to: 1\n");
    threshold = 1;
  } else if (threshold > MAX_BRIGHT) {
    printf("threshold was too big, was set to: %d\n", MAX_BRIGHT);
    threshold = MAX_BRIGHT;
  }

  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
    for (int j = 0; j < imgCpy->width; j++) {
      // if pixel at coord is smaller than threshold -> replace it with 0,
      // otherwise replace it with MAX_BRIGHT
      imgCpy->data[i][j] = (imgCpy->data[i][j] < threshold) ? 0 : MAX_BRIGHT;
    }
  }

  return imgCpy;
}

// TODO: BIG WIP
Image *scale(Image *img, int width, int height) {
  // if image has same dimensions as the given dimensions to rescale, return a
  // copy of the given img
  if (width == img->width && height == img->height) {
    Image *imgCpy = copyImage(img);
    return imgCpy;
  }

  int x = img->width / width;
  int y = img->height / height;

  Image *newImg = createImage(width, height, 0, img->name);

  for (int i = 0; i < newImg->height; i++) {
    for (int j = 0; j < newImg->width; j++) {
      //	if(i >= img->height - 1 || j >= img->width -1)
      //		continue;

      newImg->data[i][j] = (1 - x) * (1 - y) * img->data[i][j] +
                           x * (1 - y) * img->data[i][j + 1] +
                           (1 - x) * y * img->data[i + 1][j] +
                           x * y * img->data[i + 1][j + 1];
    }
  }

  return newImg;
}

Image *rotate(Image *img, double angle, int brightness) {
  angle = angle * (PI / 180);

  Image *imgCpy = createImage(img->width, img->height, brightness, img->name);

  // calculate center
  int x_mid = img->width / 2;
  int y_mid = img->height / 2;

  for (int y = 0; y < img->height; y++) {
    for (int x = 0; x < img->width; x++) {
      // calculate new positions
      int x_new = (int)round(cos(angle) * (x - x_mid) -
                             sin(angle) * (y - y_mid) + x_mid);
      int y_new = (int)round(sin(angle) * (x - x_mid) +
                             cos(angle) * (y - y_mid) + y_mid);
      // out of bound checks
      // ----------------------------
      if (x_new == img->width) x_new = 0;
      if (y_new == img->height) y_new = 0;
      if (x_new < 0 || y_new < 0 || x_new >= img->width || y_new >= img->height)
        continue;
      // ----------------------------
      imgCpy->data[y_new][x_new] = img->data[y][x];
    }
  }
  Image *newImg = median(imgCpy);
  return newImg;
}
