/*----------------------------------------------
 * Author: Kripa Lamichhane
 * Date: 10/7/2024
 * Description: the program to write binary data
 --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "write_ppm.h"

// Flat array version of write_ppm
void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }

    // Write the PPM header
    fprintf(fp, "P6\n");
    fprintf(fp, "# Created by write_ppm\n");
    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    // Write the pixel data in binary format
    size_t num_pixels = w * h;
    if (fwrite(pxs, sizeof(struct ppm_pixel), num_pixels, fp) != num_pixels) {
        perror("Error writing pixel data");
        fclose(fp);
        return;
    }

    fclose(fp);
}

// 2D array version of write_ppm
void write_ppm_2d(const char* filename, struct ppm_pixel** pxs, int w, int h) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }

    // Write the PPM header
    fprintf(fp, "P6\n");
    fprintf(fp, "# Created by write_ppm_2d\n");
    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    // Write the pixel data in binary format row by row
    for (int i = 0; i < h; i++) {
        if (fwrite(pxs[i], sizeof(struct ppm_pixel), w, fp) != (size_t)w) {
            perror("Error writing pixel data");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

