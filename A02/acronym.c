/**
* The acronym program for Assignment 2.
*
* Computes an acronym from a given phrase
*
* @author: Kripa Lamichhane
* @version: Sep 13, 2024
*/

#include <stdio.h>

int main() {
    char phrase[1024];
    char acronym[124];
    int j = 0;

    printf("Enter a phrase: ");
    scanf("%[^\n]%*c", phrase);

    for (int i = 0; phrase[i] != '\0'; i++) {
        if (phrase[i] >= 'A' && phrase[i] <= 'Z') {
            if (i == 0 || phrase[i-1] == ' ') {
                acronym[j++] = phrase[i];
            }
        }
    }

    acronym[j] = '\0';
    printf("Your acronym is %s\n", acronym);

    return 0;
}
