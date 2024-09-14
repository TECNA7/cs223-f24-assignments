/* This is Songs.c
 *
 * @Author : Kripa Lamichhane
 * @Date : Sep 13,2024
 * This program fills an array with three or more songs and then allows the user * to edit the data in the array.
 * */
#include <stdio.h>
#include <string.h>

struct song {
    char title[32];
    char artist[32];
    int minutes;
    int seconds;
    float danceability;
};

void PrintSongs(struct song songs[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d) %-20s artist: %-20s duration: %d:%02d  danceability: %.2f\n", 
		i, songs[i].title, songs[i].artist, songs[i].minutes, 
		songs[i].seconds, songs[i].danceability);
    }
    printf("======================================\n");
}

void EditSongs(struct song songs[], int song_id) {
    char choices[32];
    printf("Which attribute do you wish to edit? [artist, title, duration, danceability]: ");
    scanf(" %[^\n]%*c", choices);

    if (strcmp(choices, "artist") == 0) {
        printf("Enter artist: ");
        scanf(" %[^\n]%*c", songs[song_id].artist); 
    } else if (strcmp(choices, "title") == 0) {
        printf("Enter title: ");
        scanf(" %[^\n]%*c", songs[song_id].title); 
    } else if (strcmp(choices, "duration") == 0) {
        printf("Enter a duration (minutes): ");
        scanf("%d%*c", &songs[song_id].minutes);
        printf("Enter a duration (seconds): ");
        scanf("%d%*c", &songs[song_id].seconds);
    } else if (strcmp(choices, "danceability") == 0) {
        printf("Enter danceability: ");
        scanf("%f%*c", &songs[song_id].danceability); 
    } else {
        printf("Invalid choices!\n");
    }

}

int main() {
    struct song songs[3] = {
        {"Shout", "Tears for Fears", 4, 11, 0.50},
        {"As it was", "Harry Styles", 2, 47, 0.70},
        {"Wish you were here", "Pink Floyd", 5, 34, 0.30}
    };

    int choice;
        printf("Welcome to My Struct's Song List.\n");
        PrintSongs(songs, 3);

        printf("Enter a song id to edit [0,1,2]: ");
        scanf("%d%*c", &choice); 

        if (choice >= 0 && choice < 3) {
            EditSongs(songs, choice);
        } else {
            printf("Invalid choices!\n");
        }
        
        printf("\n");
	PrintSongs(songs, 3);
    return 0;
}

