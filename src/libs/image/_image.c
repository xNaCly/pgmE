#include "_image.h"
#include <stdlib.h>

void median(Image *img);
    /*Rand soll nicht bearbeitet werden (if AnzahlPixel < 9) + sind Randpixel enthalten?
    qsort (img, sizeof(Image *), compare);
    (AnzahlFeldElemente % 2) == 0 ? x[n/2] : x[(n-1)/2];*/
void gauss(Image *img);
    //bi,j = (bi−1,j−1 + 2bi,j−1 + bi+1,j−1 + 2bi−1,j + 4bi,j + 2bi+1,j + bi−1,j+1 + 2bi,j+1 + bi+1,j+1)/16
void laplace(Image *img);
   /*Extrahieren von Kanten
   for (int i = 0; i < img->width ;i++){
   for (int j = 0; j <= img->heigth ; j++){
   bi,j = bi−1,j−1 + bi,j−1 + bi+1,j−1 + bi−1,j − 8bi,j + bi+1,j + bi−1,j+1 + bi,j+1 + bi+1,j+1*/
void threshold(Image *img, int threshold){
    //for (int i = 0; i < img->width ;i++){
    //for (int j = 0; j <= img->height ; j++){
    //&img[i,j]< threshold ? 0 : 255;}}
	}
void scale(Image *img, int width, int height);
    /*createImage(width, heigth, brigthness);
    for (int i = 0; i < img->width ;i++){
    for (int j = 0; j <= img->height ; j++){
     ̃bi,j =(1−x)·(1−y)·bk,l +x·(1−y)·bk,l+1 +(1−x)·y·bk+1,l +x·y·bk+1,l+1*/
void rotate(Image *img, double angle, int brigthness);
    /*
    createImage(width, height, brigthness);
    x ̃ = cos(α) · (x − cx) − sin(α) · (y − cy) + cx
    y ̃ = sin(α) · (x − cx) + cos(α) · (y − cy) + cy*/
