/***************************************************
 * mathgame.c
 * Author:Kripa Lamichhane
 * Implements a math game
 *
 * Welcome to Math Game !!!!!
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int loop, num01, num02, i, sum;
	int TotalScore = 0;

	printf("Math Game Begins!\n");
	printf("Rounds to Play: \n");
	scanf("%d", &loop);

	for(i = 0; i < loop; i++){
		num01 = rand() % 10;
	        num02 = rand() % 10;
		printf("%d + %d = ? ", num01, num02);
		scanf("%d", &sum);
		
		if (sum == (num01 + num02)){
			printf("Correct!\n");
			TotalScore++;
		}	
		else{
			printf("Incorrect :(\n");
		}
	}
	printf("Your total score is %d/%d . \n", TotalScore, loop);

  return 0;
}
