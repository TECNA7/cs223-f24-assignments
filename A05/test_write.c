/*----------------------------------------------
 * Author:Kripa Lamichhane 
 * Date: 10/7/2024
 * Description: 
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;

  // Read the original PPM file (feep-raw.ppm)
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
  if (!pixels) {
    printf("Error: Could not read the PPM file.\n");
    return 1;
  }

  // Write the pixel data to a new file (test.ppm)
  write_ppm("test.ppm", pixels, w, h);

  // Free the original pixel data
  free(pixels);

  // Reload the newly written file (test.ppm) to verify its contents
  struct ppm_pixel* test_pixels = read_ppm("test.ppm", &w, &h);
  if (!test_pixels) {
    printf("Error: Could not read the test.ppm file.\n");
    return 1;
  }

  // Print the reloaded image's pixel data
  printf("Testing file test.ppm: %d %d\n", w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = test_pixels[i * w + j];
      printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
    }
    printf("\n");
  }

  // Free the reloaded pixel data
  free(test_pixels);

  return 0;
}

