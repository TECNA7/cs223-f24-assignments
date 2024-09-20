/*----------------------------------------------
 * Author: Kripa Lamichhane
 * Date: 9/20/2024
 * Description: This is a program that turns a phrase into ent-speech. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int Pause, Length, i, j;
    char input[32], *slow;

    printf("Pause length: ");
    if (scanf("%d", &Pause) != 1) {
        printf("Invalid length\n");
        return 1;
    }

    printf("Text: ");
    if (scanf("%31s", input) != 1) {
        printf("Invaid text\n");
        return 1;
    }
    Length = strlen(input);

    slow = (char *)malloc((Length * 2 + 1) * sizeof(char)); 
    if (!slow) {
        printf("There's memory leak\n");
        return 2;
    }

    for (i = 0, j = 0; i < Length; i++) {
        slow[j++] = input[i];
        if (i < Length - 1) slow[j++] = '.';
    }
    slow[j] = '\0'; 

    for (i = 0; slow[i] != '\0'; i++) {
        printf("%c", slow[i]);
        if (slow[i] == '.') {
            for (j = 0; j < Pause; j++) printf(".");
        }
    }
    printf("\n");

    free(slow);
    return 0;
}
