#include <stdio.h>
#include "_util.h"

void print_image_data(Image *img, int print_pixels){
    printf("height: %d, width: %d\n", img->width, img->width);

    if(print_pixels){
        for(int i = 0; i < img->width; i++){
            for(int ii = 0; ii < img->height; ii++){
                printf("%d, ", img->data[i][ii]);
            }
        }
    }
}
