#include "_image.h"
#include <stdlib.h>
#include <stdio.h>

void median(Image *img);
/*Rand soll nicht bearbeitet werden (if AnzahlPixel < 9) + sind Randpixel enthalten?
Image *imgCpy = copyImage(img);
qsort (imgCpy, sizeof(Image *), compare);
int n =;
(AnzahlFeldElemente % 2) == 0 ? x[n/2] : x[(n-1)/2];*/
void gauss(Image *img);
//Image *imgCpy = copyImage(img);
//bi,j = (bi−1,j−1 + 2bi,j−1 + bi+1,j−1 + 2bi−1,j + 4bi,j + 2bi+1,j + bi−1,j+1 + 2bi,j+1 + bi+1,j+1)/16
void laplace(Image *img);
/*Extrahieren von Kanten
Image *imgCpy = copyImage(img);
for (int i = 0; i < img->width ;i++){
for (int j = 0; j <= img->heigth ; j++){
bi,j = bi−1,j−1 + bi,j−1 + bi+1,j−1 + bi−1,j − 8bi,j + bi+1,j + bi−1,j+1 + bi,j+1 + bi+1,j+1*/

Image *threshold(Image *img, int threshold) {
  if(threshold < 1){
	printf("threshold was too small, was set to: 1");
	threshold = 1;
  } else if(threshold > MAX_BRIGHT){
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
void scale(Image *img, int width, int height);
/*Image *imgCpy = copyImage(img);
for (int i = 0; i < img->width ;i++){
for (int j = 0; j <= img->height ; j++){
 ̃bi,j =(1−x)·(1−y)·bk,l +x·(1−y)·bk,l+1 +(1−x)·y·bk+1,l +x·y·bk+1,l+1*/
void rotate(Image *img, double angle, int brigthness);
/*
Image *imgCpy = copyImage(img);
x ̃ = cos(α) · (x − cx) − sin(α) · (y − cy) + cx
y ̃ = sin(α) · (x − cx) + cos(α) · (y − cy) + cy*/
