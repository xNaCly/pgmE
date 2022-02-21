#include "_image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Image *median(Image *img);
  /*Rand soll nicht bearbeitet werden (if AnzahlPixel < 9) + sind Randpixel
  enthalten? Image *imgCpy = copyImage(img); qsort (imgCpy, sizeof(Image *),
  compare); int n =; (AnzahlFeldElemente % 2) == 0 ? x[n/2] : x[(n-1)/2];*/

Image *gauss(Image *img){
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->width ; i++){
  	for (int j = 0; j < imgCpy->height ; j++){
    	imgCpy->data[i][j] = (imgCpy->data[i-1][j-1] + 2*imgCpy->data[i][j-1] + imgCpy->data[i+1][j-1] + 2*imgCpy->data[i-1][j] + 4*imgCpy->data[i][j] + 2*imgCpy->data[i+1][j] + imgCpy->data[i-1][j+1] + 2*imgCpy->data[i][j+1] + imgCpy->data[i+1][j+1])/16;
  	}
  }

  return imgCpy;
}

Image *laplace(Image *img){
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->width ; i++){
	for (int j = 0; j < imgCpy->height ; j++){
	    imgCpy->data[i][j] = imgCpy->data[i-1][j-1] + imgCpy->data[i][j-1] + imgCpy->data[i+1][j-1] + imgCpy->data[i-1][j] -8 * imgCpy->data[i][j] + imgCpy->data[i+1][j] + imgCpy->data[i-1][j+1] + imgCpy->data[i][j+1] + imgCpy->data[i+1][j+1];
  	}
  }

  return imgCpy;
}

Image *threshold(Image *img, int threshold) {
  if (threshold < 1) {
	printf("threshold was too small, was set to: 1");
	threshold = 1;
  } else if (threshold > MAX_BRIGHT) {
	printf("threshold was too big, was set to: 255");
	threshold = 255;
  }

  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
	for (int j = 0; j < imgCpy->width; j++) {
	  imgCpy->data[i][j] = (imgCpy->data[i][j] < threshold) ? 0 : 255;
	}
  }

  return imgCpy;
}

Image *scale(Image *img, int width, int height){
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->width ;i++){
	for (int j = 0; j <= imgCpy->height ; j++){
   //imgCpy->data[i][j] =(1−x)·(1−y)·bk,l +x·(1−y)·bk,l+1 +(1−x)·y·bk+1,l +x·y·bk+1,l+1*/}
   }
  }

  return imgCpy;
}

Image *rotate(Image *img, double angle, int brigthness) {
  angle = angle * (PI / 180);

  Image *imgCpy = createImage(
	  img->width,
	  img->height,
	  brigthness);

  // calculate center
  int x_mid = img->width / 2;
  int y_mid = img->height / 2;

  for (int y = 0; y < img->height; y++) {
	for (int x = 0; x < img->width; x++) {
	  // calulate new positions
	  int x_new = (int)round(cos(angle) * (x - x_mid) - sin(angle) * (y - y_mid) + x_mid);
	  int y_new = (int)round(sin(angle) * (x - x_mid) + cos(angle) * (y - y_mid) + y_mid);

      if(x_new == img->width) x_new = 0;
      if(y_new == img->height) y_new = 0;

	  if(x_new < 0 || y_new < 0) continue;

	  // assign data from old pixel coords to new pixel coord
	  imgCpy->data[y_new][x_new] = img->data[y][x];
	}
  }

  return imgCpy;
}

