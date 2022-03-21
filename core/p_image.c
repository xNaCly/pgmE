#include "p_image.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h> 


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
      if (i < 2 || j < 2 || i >= imgCpy->height - 2 || j >= imgCpy->width - 2)
        continue;

      int surNums[9] = {imgCpy->data[i - 1][j + 1], imgCpy->data[i][j + 1],
                        imgCpy->data[i + 1][j + 1], imgCpy->data[i - 1][j],
                        imgCpy->data[i][j],         imgCpy->data[i + 1][j],
                        imgCpy->data[i - 1][j - 1], imgCpy->data[i][j - 1],
                        imgCpy->data[i + 1][j - 1]};

      int lenght = sizeof(surNums) / sizeof(int);
      qsort(surNums, lenght, sizeof(int), compare);

      int m_pixel = surNums[4];

      imgCpy->data[i][j] = m_pixel;
    }
  }
  return imgCpy;
}

Image *gauss(Image *img) {
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
    for (int j = 0; j < imgCpy->width; j++) {
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

  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
    for (int j = 0; j < imgCpy->width; j++) {
      imgCpy->data[i][j] = (imgCpy->data[i][j] < threshold) ? 0 : MAX_BRIGHT;
    }
  }

  return imgCpy;
}

Image *scale(Image *img, int width, int height) {
  if (width == img->width && height == img->height) {
    Image *imgCpy = copyImage(img);
    return imgCpy;
  }


  Image *newImg = createImage(width, height, 0, img->name);
  int k = img->width;
  int l = img->height;

  for (int lh = 0; lh < height; lh++) {
    for (int kw = 0; kw < width; kw++) {
      float x = (float)kw/width * k;
      float y = (float)lh/height * l;
      int oldX = x > k-2 ? k-2 : (int)x;
      int oldY = y > l-2 ? l-2 : (int)y;
      float dX = x-oldX;
      float dY = y-oldY;

      newImg->data[kw][lh] = 
        (1-dX) * (1-dY) * img->data[oldX][oldY] +
        dX * (1-dY) * img->data[oldX+1][oldY] +
        (1-dX) * dY * img->data[oldX][oldY+1] +
        dX * dY * img->data[oldX+1][oldY+1];
    }
  }

  return newImg;
}

Image *rotate(Image *img, double angle, int brightness) {
  angle = angle * (PI / 180);

  Image *imgCpy = createImage(img->width, img->height, brightness, img->name);
  int x_mid = img->width / 2;
  int y_mid = img->height / 2;

  for (int y = 0; y < img->height; y++) {
    for (int x = 0; x < img->width; x++) {
      int x_new = (int)round(cos(angle) * (x - x_mid) -
                             sin(angle) * (y - y_mid) + x_mid);
      int y_new = (int)round(sin(angle) * (x - x_mid) +
                             cos(angle) * (y - y_mid) + y_mid);
      if (x_new == img->width) x_new = 0;
      if (y_new == img->height) y_new = 0;
      if (x_new < 0 || y_new < 0 || x_new >= img->width || y_new >= img->height)
        continue;
      imgCpy->data[y_new][x_new] = img->data[y][x];
    }
  }

  Image *newImg = median(imgCpy);
  freeImage(&imgCpy);
  return newImg;
}
