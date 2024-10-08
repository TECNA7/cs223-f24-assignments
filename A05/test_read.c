/*----------------------------------------------
 * Author: Kripa Lamichhane
 * Date: 10/7/2024
 * Description: the program for reading and printing the values of a binaryfile 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
    int width, height;
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &width, &height);
    if (pixels == NULL) {
        printf("Error reading PPM file.\n");
        return 1;
    }

    printf("Testing file feep-raw.ppm: %d %d\n", width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            struct ppm_pixel pixel = pixels[i * width + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}

