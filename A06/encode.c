/*----------------------------------------------
 * Author:Kripa Lamichhane 
 * Date: 10/13/2024
 * Description: reads in a PPM file (raw, or binary, format) and asks the user for a message to embed within it
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: encode <file.ppm>\n");
        return 0;
    }
    const char* filename = argv[1];
    int width, height;
    struct ppm_pixel* pixels = read_ppm(filename, &width, &height);
    if (pixels == NULL) {
        printf("Error: could not read file %s\n", filename);
        return 1;
    }

    printf("Reading %s with width %d and height %d\n", filename, width, height);

    int max_chars = (width * height * 3) / 8;
    printf("Max number of characters in the image: %d\n", max_chars);

    char message[1000];
    printf("Enter a phrase: ");
    fgets(message, sizeof(message), stdin);
    int message_length = strlen(message);
    if (message_length > max_chars) {
        printf("Error: message is too long to be encoded in the image\n");
        free(pixels);
        return 1;
    }

    int bit_index = 0;
    for (int i = 0; i < message_length + 1; i++) { 
        unsigned char current_char = message[i];
        for (int j = 0; j < 8; j++) {
            int lsb = (current_char >> j) & 1; 
            int pixel_index = bit_index / 3;
            int color_channel = bit_index % 3;

            if (color_channel == 0) {
                pixels[pixel_index].red = (pixels[pixel_index].red & 0xFE) | lsb;
            } else if (color_channel == 1) {
                pixels[pixel_index].green = (pixels[pixel_index].green & 0xFE) | lsb;
            } else {
                pixels[pixel_index].blue = (pixels[pixel_index].blue & 0xFE) | lsb;
            }

            bit_index++;
        }
    }

    char encoded_filename[256];
    snprintf(encoded_filename, sizeof(encoded_filename), "%s-encoded.ppm", filename);

    write_ppm(encoded_filename, pixels, width, height);
    printf("Writing file %s\n", encoded_filename);

    free(pixels);
    return 0;
}

