/*----------------------------------------------
 * Author: Kripa Lamichhane 
 * Date: 10/13/2024
 * Description: this is write ppm file for assignment 06
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <stdlib.h>

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
    FILE* binFile = fopen(filename, "wb");
    if (binFile == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(binFile, "P6\n");
    fprintf(binFile, "# Created by custom program\n");
    fprintf(binFile, "%d %d\n", w, h);
    fprintf(binFile, "255\n");

    for (int i = 0; i < h; i++) {
        fwrite(pixels[i], sizeof(struct ppm_pixel), w, binFile);
    }

    fclose(binFile);
}
void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file, "P6\n");
    fprintf(file, "# Created by write_ppm\n");
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n");

    fwrite(pixels, sizeof(struct ppm_pixel), w * h, file);

    fclose(file);
    printf("Writing file %s\n", filename);
}


