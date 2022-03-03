#include "_image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: move to util
int compare(const void *a, const void *b) {
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  if (int_a == int_b) return 0;
  else if (int_a < int_b) return -1;
  else return 1;
}

Image *median(Image *img) {
  Image *imgCpy = copyImage(img);
  for (int i = 0; i < imgCpy->height; i++) { 
	for (int j = 0; j < imgCpy->width; j++) {
	
	// ignore pixels at the border of the image
	if (i < 2 || j < 2 || i >= imgCpy->height - 2 || j >= imgCpy->width - 2) 
		continue;

	  int surNums[9] = {
		  imgCpy->data[i - 1][j + 1], 
		  imgCpy->data[i][j + 1], 	
		  imgCpy->data[i + 1][j + 1], 
		  imgCpy->data[i - 1][j],	
		  imgCpy->data[i][j], 		
		  imgCpy->data[i + 1][j],	
		  imgCpy->data[i - 1][j - 1],
		  imgCpy->data[i][j - 1],	
		  imgCpy->data[i + 1][j - 1]
	  };

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

	imgCpy->data[i][j] = (
		(imgCpy->data[i - 1][j - 1]) + 
		(2 * imgCpy->data[i][j - 1]) + 
		(imgCpy->data[i + 1][j - 1]) +
	  	(2 * imgCpy->data[i - 1][j]) +
		(4 * imgCpy->data[i][j]) +
		(2 * imgCpy->data[i + 1][j]) +
		(imgCpy->data[i - 1][j + 1]) + 
		(2 * imgCpy->data[i][j + 1]) + 
		(imgCpy->data[i + 1][j + 1])
	) / 16;
	}
  }

  return imgCpy;
}

// TODO: WIP
Image *laplace(Image *img) {
  Image *imgCpy = copyImage(img);

  for (int i = 0; i < imgCpy->height; i++) {
	for (int j = 0; j < imgCpy->width; j++) {
	  	// ignore pixels at the border of the image
		if (i < 2 || j < 2 || i >= imgCpy->height - 2 || j >= imgCpy->width - 2) 
			continue;

		imgCpy->data[i][j] = sqrt(
			imgCpy->data[i - 1][j - 1] + 
			imgCpy->data[i][j - 1] + 
			imgCpy->data[i + 1][j - 1] + 
			imgCpy->data[i - 1][j] -
			8 * imgCpy->data[i][j] + 
			imgCpy->data[i + 1][j] + 
			imgCpy->data[i - 1][j + 1] + 
			imgCpy->data[i][j + 1] + 
			imgCpy->data[i + 1][j + 1]);
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

// TODO: BIG WIP
Image *scale(Image *img, int width, int height) {
  Image *newImg = createImage(width, height, 0);

  for (int i = 0; i < newImg->height; i++) {
	for (int j = 0; j < newImg->width; j++) {
	  for (int k = 0; k < img->height; k++) {
		for (int l = 0; l < img->width; l++) {
		  newImg->data[i][j] = (1 - img->width) * (1 - (img->height)) * (img->data[k][l])
			  + (img->width) * (1 - (img->height)) * (img->data[k][l + 1])
			  + (1 - (img->width)) * (img->height) * (img->data[k + 1][l])
			  + (img->width) * (img->height) * (img->data[k + 1][l + 1]);
		}
	  }
	}
  }

  return newImg;
}

Image *rotate(Image *img, double angle, int brigthness) {
  angle = angle * (PI / 180);

  //TODO: currently not calculating the correct dimensions
  //! calculate optimal height and width for the rotated image
  /*int new_width = (int) (img->width * cos(angle) + img->height * cos(90 - angle));
  int new_height = (int) (img->width * sin(angle) + img->height * sin(90 - angle));*/

  /* Image *imgCpy = createImage(new_width, new_height, brigthness);*/
  Image *imgCpy = createImage(img->width, img->height, brigthness);

  // calculate center
  int x_mid = img->width / 2;
  int y_mid = img->height / 2;

  for (int y = 0; y < img->height; y++) {
	for (int x = 0; x < img->width; x++) {
	  // calculate new positions
	  int x_new = (int)round(cos(angle) * (x - x_mid) - sin(angle) * (y - y_mid) + x_mid);
	  int y_new = (int)round(sin(angle) * (x - x_mid) + cos(angle) * (y - y_mid) + y_mid);
	  if (x_new == img->width) x_new = 0;
	  if (y_new == img->height) y_new = 0;
	  if (x_new < 0 || y_new < 0 || x_new >= img->width || y_new >= img->height)
		continue;
	  imgCpy->data[y_new][x_new] = img->data[y][x]; //TODO: doesnt work, seg fault
	}
  }

  return imgCpy;
}

