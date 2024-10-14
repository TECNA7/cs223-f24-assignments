/*----------------------------------------------
 * Author:Kripa Lamichhane 
 * Date: 10/13/2024
 * Description: a program that reads in a single 64-bit unsigned integer (e.g. unsigned long) and outputs it as an 8x8 1bpp sprite.
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

   for (int i = 0; i < 64; i++) {
        unsigned long mask = 0x1ul << (63 - i);
        if (img & mask) {
            printf("@");  
        } else {
            printf(" ");  
        }
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
  return 0;
}
