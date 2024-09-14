/*This is exclaim.c that turns a word into an exclaimation. 
 *
 * @author : Kripa Lamichhane
 * @date : 09/13/2024
 * */
#include <stdio.h>
#include <stdlib.h>

int main() {
	char buffer[32];
	char c_arr [] = {'@', '!', '#', '*'};

	srand(1);

	printf("Enter a word : ");
	scanf("%s", buffer);

	printf("OMG! ");
	for (int i = 0; buffer[i] != '\0'; i++) {
        	if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            		printf("%c", c_arr[rand() % 4]);
        	} else {
            		printf("%c", buffer[i]);
        	}
    	}
    
    	printf("\n");
    
    	return 0;
}
