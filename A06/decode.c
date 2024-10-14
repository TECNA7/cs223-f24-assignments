/*----------------------------------------------
 * Author:Kripa Lamichhane 
 * Date: 10/13/2024
 * Description: reads in a PPM file (raw, or binary, format) and then outputs any message that might be stored in the least significant bits of each color
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: decode <file.ppm>\n");
        return 0;
    }

    const char* filename = argv[1];
    int width, height;
    struct ppm_pixel* pixels = read_ppm(filename, &width, &height);
    if (pixels == NULL) {
        perror("Error: could not read file");
        return 1;
    }

    printf("Reading %s with width %d and height %d\n", filename, width, height);
    printf("Max number of characters in the image: %d\n", (width * height * 3) / 8);

    unsigned char current_char = 0;
    int bit_count = 0;
    for (int i = 0; i < width * height * 3; i++) {
     int lsb;
     if (i % 3 == 0) {
        lsb = (pixels[i / 3].red & 1);
     } else if (i % 3 == 1) {
        lsb = (pixels[i / 3].green & 1);
     } else {
        lsb = (pixels[i / 3].blue & 1);
      } 

      printf("Pixel %d: LSB = %d\n", i, lsb);

      current_char |= (lsb << bit_count);
      bit_count++;

      if (bit_count == 8) {
        printf("Decoded character: %c\n", current_char);
        if (current_char == '\0') {
            break;
        }
        current_char = 0;
        bit_count = 0;
       }
    }
    printf("\n");
    free(pixels);
    return 0;
}

