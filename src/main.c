#include <stdio.h>
#include <stdlib.h>
#include "libs/pgm/_pgm.h"
#include "libs/image/_image.h"

int main(void) {
    Image *img = createImage(25,25,255);
    printf("height: %d, width: %d\n", img->width, img->width);
    for(int i = 0; i < img->width; i++){
        for(int ii = 0; ii < img->height; ii++){
            printf("%d, ", img->data[i][ii]);
        }
    }

    return 0;
}
