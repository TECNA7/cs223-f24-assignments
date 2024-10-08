/*----------------------------------------------
 * Author:Kripa Lamichhane 
 * Date: 10/7/2024
 * Description:this is program to read ppm file
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Read the magic number (P6)
    char magic[3];
    if (!fgets(magic, sizeof(magic), fp) || strcmp(magic, "P6") != 0) {
        printf("Error: Invalid PPM magic number in %s\n", filename);
        fclose(fp);
        return NULL;
    }

    // Skip comments if any (lines starting with '#')
    char ch = fgetc(fp);
    while (ch == '#') {
        while (fgetc(fp) != '\n');
        ch = fgetc(fp);
    }
    ungetc(ch, fp);  // put the character back if it's not a comment

    // Read width, height, and max color value
    int max_color;
    if (fscanf(fp, "%d %d %d\n", w, h, &max_color) != 3) {
        printf("Error: Invalid PPM metadata in %s (width, height, or max color missing)\n", filename);
        fclose(fp);
        return NULL;
    }

    if (max_color != 255) {
        printf("Error: Unsupported max color value in %s (expected 255, got %d)\n", filename, max_color);
        fclose(fp);
        return NULL;
    }

    printf("Reading PPM file: %s, width: %d, height: %d, max_color: %d\n", filename, *w, *h, max_color);

    // Allocate memory for pixel data
    struct ppm_pixel* pixels = (struct ppm_pixel*) malloc((*w) * (*h) * sizeof(struct ppm_pixel));
    if (!pixels) {
        printf("Error: Could not allocate memory for image data\n");
        fclose(fp);
        return NULL;
    }

    // Read pixel data
    size_t pixels_read = fread(pixels, sizeof(struct ppm_pixel), (*w) * (*h), fp);
    if (pixels_read != (*w) * (*h)) {
        printf("Error: Incomplete pixel data in %s (read %zu pixels, expected %d)\n", filename, pixels_read, (*w) * (*h));
        free(pixels);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return pixels;
}
