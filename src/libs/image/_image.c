#include "_image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Image *median(Image *img);
/*Rand soll nicht bearbeitet werden (if AnzahlPixel < 9) + sind Randpixel
enthalten? Image *imgCpy = copyImage(img); qsort (imgCpy, sizeof(Image *),
compare); int n =; (AnzahlFeldElemente % 2) == 0 ? x[n/2] : x[(n-1)/2];*/

Image *gauss(Image *img);
// Image *imgCpy = copyImage(img);
// bi,j = (bi−1,j−1 + 2bi,j−1 + bi+1,j−1 + 2bi−1,j + 4bi,j + 2bi+1,j + bi−1,j+1
// + 2bi,j+1 + bi+1,j+1)/16

Image *laplace(Image *img);
/*Extrahieren von Kanten
Image *imgCpy = copyImage(img);
for (int i = 0; i < img->width ;i++){
for (int j = 0; j <= img->heigth ; j++){
bi,j = bi−1,j−1 + bi,j−1 + bi+1,j−1 + bi−1,j − 8bi,j + bi+1,j + bi−1,j+1 +
bi,j+1 + bi+1,j+1*/

Image *threshold(Image *img, int threshold) {
  if (threshold < 1) {
	printf("threshold was too small, was set to: 1");
	threshold = 1;
  } else if (threshold > MAX_BRIGHT) {
	printf("threshold was too big, was set to: 255");
	threshold = 255;
  }

  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->width; i++) {
	for (int j = 0; j < imgCpy->height; j++) {
	  imgCpy->data[i][j] = (imgCpy->data[i][j] < threshold) ? 0 : 255;
	}
  }

  return imgCpy;
}

Image *scale(Image *img, int width, int height);
/*Image *imgCpy = copyImage(img);
for (int i = 0; i < img->width ;i++){
for (int j = 0; j <= img->height ; j++){
 ̃bi,j =(1−x)·(1−y)·bk,l +x·(1−y)·bk,l+1 +(1−x)·y·bk+1,l +x·y·bk+1,l+1*/

Image *rotate(Image *img, double angle, int brigthness) {
  angle = angle * (PI / 180);

  Image *imgCpy = createImage(
	  img->width,
	  img->height,
	  brigthness);

  // calculate center
  int x_mid = img->width / 2;
  int y_mid = img->height / 2;

  printf("\nMittelpunkt: (%d,%d)\nWinkel: %f\n", x_mid, y_mid, angle);

  for (int x = 0; x < img->width; x++) {
	for (int y = 0; y < img->height; y++) {
	  int x_new = (int)round(cos(angle) * (x - x_mid) - sin(angle) * (y - y_mid) + x_mid);
	  int y_new = (int)round(sin(angle) * (x - x_mid) + cos(angle) * (y - y_mid) + y_mid);

	  //printf("[%d][%d]: %d,%d\n", x, y, x_new, y_new);
	  imgCpy->data[x_new][y_new] = img->data[x][y];
	}
  }

  return imgCpy;
}
/*
Image *imgCpy = copyImage(img);
x ̃ = cos(α) · (x − cx) − sin(α) · (y − cy) + cx
y ̃ = sin(α) · (x − cx) + cos(α) · (y − cy) + cy*/
