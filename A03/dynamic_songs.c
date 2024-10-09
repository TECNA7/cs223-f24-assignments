/*----------------------------------------------
 * Author: Kripa Lamichhane 
 * Date: 9/20/2024
 * Description: File that that reads songs from a text file into an array
 --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[128];
    char artist[128];
    int duration[2]; 
    float danceability;
    float energy;
    float tempo;
    float valence;
} Song;

void prints(Song* songs, int size) {
    printf("Welcome to Dynamic Donna's Danceability Directory.\n");
    for (int i = 0; i < size; i++) {
        printf("%d) %-25s artist: %-20s duration: %d:%02d D: %.03f E: %.03f T: %.03f V: %.03f\n",
            i, songs[i].title, songs[i].artist, songs[i].duration[0], songs[i].duration[1],
            songs[i].danceability, songs[i].energy, songs[i].tempo, songs[i].valence);
    }
}

int main() {
    FILE *songlist = fopen("songlist.csv", "r");
    if (songlist == NULL) {
        printf("Error: unable to open file.\n");
        return 1;
    }

    char line[256];
    fgets(line, sizeof(line), songlist);
    int num_songs = atoi(strtok(line, ","));

    Song *songs = malloc(sizeof(Song) * num_songs);
    if (songs == NULL) {
        printf("Error: unable to allocate memory.\n");
        fclose(songlist);
        return 1;
    }

    fgets(line, sizeof(line), songlist);

    // Reading data from file
    for (int i = 0; i < num_songs; i++) {
        fgets(line, sizeof(line), songlist);

        // Parsing the line
        strcpy(songs[i].title, strtok(line, ","));
        strcpy(songs[i].artist, strtok(NULL, ","));
        int duration_ms = atoi(strtok(NULL, ",")); // Duration in milliseconds
        songs[i].duration[0] = duration_ms / 60000;  //Duration in  Minutes
        songs[i].duration[1] = (duration_ms % 60000) / 1000; // Durationm Seconds
        songs[i].danceability = atof(strtok(NULL, ","));
        songs[i].energy = atof(strtok(NULL, ","));
        songs[i].tempo = atof(strtok(NULL, ","));
        songs[i].valence = atof(strtok(NULL, ","));
    }

    prints(songs, num_songs);

    // Freed
    free(songs);
    fclose(songlist);

    return 0;
}

