/* Author : Kripa Lamichhane
 * Date : 11/13/2024
 * Description: our write ppm file
 * */
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE *output = fopen(filename, "w");
    if (!output) {
      printf("Error opening file");
    }
    fprintf(output, "P6\n");
    fprintf(output, "%d %d\n", w, h);
    fprintf(output, "255\n"); 
    fwrite(pixels, sizeof(struct ppm_pixel), (w * h), output);
    fclose(output);
}
void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
