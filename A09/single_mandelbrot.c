/*
 * Author : Kripa Lamichhane
 * Date : 11/8/2024
 * Description : Program for PPM image of mandelbrot set
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': 
        printf("usage eoorror: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]);
        return 1;
    }
  }

  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // measuring time here
  struct timeval start, end;
  gettimeofday(&start, NULL);

  //color palette generation here
  srand(time(0));
  struct ppm_pixel* palette = malloc(maxIterations * sizeof(struct ppm_pixel));
  for (int i = 0; i < maxIterations; i++) {
    palette[i].red = rand() % 256;
    palette[i].green = rand() % 256;
    palette[i].blue = rand() % 256;
  }

  // allocating memory
  struct ppm_pixel* pixels = malloc(size * size * sizeof(struct ppm_pixel));
  if (!pixels) {
    printf("can't allocate memory \n");
    free(palette);
    return 1;
  }

  // computing sets
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      float xfrac = (float) col / (size - 1);
      float yfrac = (float) row / (size - 1);
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int iter = 0;
      while (iter < maxIterations && x*x + y*y < 4) {
        float xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iter++;
      }

      struct ppm_pixel color = iter < maxIterations ? palette[iter] : (struct ppm_pixel){0, 0, 0};
      pixels[row * size + col] = color;
    }
  }

  // measurement time ends...
  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size, elapsed);

  char filename[64];
  snprintf(filename, sizeof(filename), "mandelbrot-%d-%ld.ppm", size, time(0));
  printf("Writing file: %s\n", filename);

  // writing image to file
  write_ppm(filename, pixels, size, size);

  // freeing memory
  free(palette);
  free(pixels);

  return 0;
}

