/*----------------------------------------------
 * Author:Kripa Lamichhane 
 * Date: 10/2/2024
 * Description: Code that generates a crossword using two words from a user. 
 ---------------------------------------------*/

//including built-in header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// checking  input arguments
int arguments(int arg, char* arg1[]) {
    if (arg != 3) {
        printf("Usage: %s word1 word2\n", arg1[0]);
        return 0;
    }
    return 1;
}

// finding the common letter index between two words
int findCommonIndex(char* word1, char* word2, int* w1Index, int* w2Index) {
    for (int i = 0; i < strlen(word1); i++) {
        for (int j = 0; j < strlen(word2); j++) {
            if (word1[i] == word2[j]) {
                *w1Index = i;  // Index in word1 (to place vertical)
                *w2Index = j;  // Index in word2 (to place horizontal)
                return 1; // Common letter found
            }
        }
    }
    return 0; // Common letter not found
}

// allocating the crossword grid in heap(dynamically)
char** allocateCrossword(int rows, int cols) {
    char** crossword = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        crossword[i] = (char*)malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            crossword[i][j] = '.'; // Fill the grid with dots initially
        }
    }
    return crossword;
}

// placing word2 horizontally in the grid
void placeWord2(char** crossword, char* word2, int word2Len, int word1Index) {
    for (int i = 0; i < word2Len; i++) {
        crossword[word1Index][i] = word2[i];
    }
}

// placing word1 vertically in the grid
void placeWord1(char** crossword, char* word1, int word1Len, int word2Index) {
    for (int i = 0; i < word1Len; i++) {
        crossword[i][word2Index] = word1[i];
    }
}

// printing the crossword grid
void printCrossword(char** crossword, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", crossword[i][j]);
        }
        printf("\n");
    }
}

// freeing the dynamically allocated memory
void freeCrossword(char** crossword, int rows) {
    for (int i = 0; i < rows; i++) {
        free(crossword[i]);
    }
    free(crossword);
}

//our main method to call other methods
int main(int arg, char* arg1[]) {
    // checking input arguments
    if (!arguments(arg, arg1)) {
        return 1;
    }

    char* word1 = arg1[1];  // vertical
    char* word2 = arg1[2];  // horizontal
    int word1Len = strlen(word1);
    int word2Len = strlen(word2);
    int word1Index, word2Index;

    // finding common letter index between word1 and word2
    if (!findCommonIndex(word1, word2, &word1Index, &word2Index)) {
        printf("No common letter!\n");
        return 1;
    }

    // allocating a grid large enough to fit both words
    int rows = word1Len; 
    int cols = word2Len;
    
    //making grid larger to fit both words
    int gridRows = rows > word1Index + 1 ? rows : word1Index + 1; 
    int gridCols = cols > word2Index + 1 ? cols : word2Index + 1;  

    char** crossword = allocateCrossword(gridRows, gridCols);

    // placing words in the crossword grid
    placeWord1(crossword, word1, word1Len, word2Index);  
    placeWord2(crossword, word2, word2Len, word1Index); 

    // printing the crossword grid
    printCrossword(crossword, gridRows, gridCols);

    // freeing dynamically allocated memory
    freeCrossword(crossword, gridRows);

    return 0;
}


