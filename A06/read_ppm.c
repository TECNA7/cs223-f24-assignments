/*----------------------------------------------
 * Author:Kripa Lamichhane
 * Date: 10/13/2024
 * Description:read PPM file  new one for assignment 6
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    FILE* ppmData = fopen(filename, "rb");
    if (ppmData == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char buff[100];
    int max_color_value;

    if (!fgets(buff, sizeof(buff), ppmData)) {
        perror("Error reading magic number");
        fclose(ppmData);
        return NULL;
    }
    printf("Magic number: %s", buff); 

    if (strncmp(buff, "P6", 2) != 0) {
        printf("Error: Not a valid P6 PPM file\n");
        fclose(ppmData);
        return NULL;
    }

    do {
        if (!fgets(buff, sizeof(buff), ppmData)) {
            perror("Error reading width and height");
            fclose(ppmData);
            return NULL;
        }
    } while (buff[0] == '#');

    sscanf(buff, "%d %d", w, h);
    printf("Width: %d, Height: %d\n", *w, *h); 

    if (!fgets(buff, sizeof(buff), ppmData)) {
        perror("Error reading max color value");
        fclose(ppmData);
        return NULL;
    }

    sscanf(buff, "%d", &max_color_value);
    printf("Max color value: %d\n", max_color_value); 
    
    if (max_color_value != 255) {
        printf("Error: max color value must be 255\n");
        fclose(ppmData);
        return NULL;
    }

    struct ppm_pixel* pixels = malloc((*w) * (*h) * sizeof(struct ppm_pixel));
    if (pixels == NULL) {
        perror("Error allocating memory");
        fclose(ppmData);
        return NULL;
    }

    size_t read_count = fread(pixels, sizeof(struct ppm_pixel), (*w) * (*h), ppmData);
    if (read_count != (*w) * (*h)) {
        printf("Error: Read %ld pixels, expected %d\n", read_count, (*w) * (*h));
        free(pixels);
        fclose(ppmData);
        return NULL;
    }

    fclose(ppmData);
    return pixels;
}

