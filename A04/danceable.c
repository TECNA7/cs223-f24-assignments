/*----------------------------------------------
 * Author: Kripa Lamichhane
 * Date: 9/24/2024
 * Description: This program allows user to easily
 * access the most danceable songs in songlist.csv.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Songs' struct for the typedef */
typedef struct song {
    char title[1000];
    char artist[1000];
    int duration;
    float danceability;
    float energy;
    float tempo;
    float valence;
} Song;

/*Node;s struct for the typedef */
typedef struct Node {
    Song song;
    struct Node* next;
} Node;

/*printing songs */
void printSong(Song song) {
    int minutes = song.duration / 60000;
    int seconds = (song.duration % 60000) / 1000;
    printf("%-30s %-15s %d:%02ds D: %.3f E: %.3f T: %.3f V: %.3f\n",
           song.title, song.artist, minutes, seconds, song.danceability,
           song.energy, song.tempo, song.valence);
}
/* prints all songs present */
void printAllSongs(Node* head) {
    Node* current = head;
    int index = 0;
    while (current != NULL) {
        printf("%d) ", index++);
        printSong(current->song);
        current = current->next;
    }
}

Node* insert(Song song, Node* head) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->song = song;
    newNode->next = head;
    return newNode;
}

Node* removeMostDanceable(Node** head) {
    if (*head == NULL){ 
	    return NULL;
    }

    Node* current = *head;
    Node* maxNode = current;
    Node* prevMax = NULL;

    while (current->next != NULL) {
        if (current->next->song.danceability > maxNode->song.danceability) {
            maxNode = current->next;
            prevMax = current;
        }
        current = current->next;
    }

    if (maxNode == *head) {
        *head = (*head)->next;
    } else {
        prevMax->next = maxNode->next;
    }

    maxNode->next = NULL;
    return maxNode;
}

void clearList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
	//Freed the current datas
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    FILE *songlist = fopen("songlist.csv", "r");
    if (songlist == NULL) {
        printf("Can't open a file.\n");
        return 1;
    }

    char buff[1021];
    int songNumber = 0;
    char input; //for user input either d or anything else to terminate infinite loop
    fgets(buff, sizeof(buff), songlist);
    Node* head = NULL;

    while (fgets(buff, sizeof(buff), songlist) != NULL) {
        Song wholeline;
        char* content;

        content = strtok(buff, ",");
        strcpy(wholeline.title, content);
        content = strtok(NULL, ",");
        strcpy(wholeline.artist, content);
        content = strtok(NULL, ",");
        wholeline.duration = atoi(content);
        content = strtok(NULL, ",");
        wholeline.danceability = atof(content);
        content = strtok(NULL, ",");
        wholeline.energy = atof(content);
        content = strtok(NULL, ",");
        wholeline.tempo = atof(content);
        content = strtok(NULL, ",");
        wholeline.valence = atof(content);

        head = insert(wholeline, head);
        songNumber++;
    }

    fclose(songlist);

    while (1) {
        printAllSongs(head);
        printf("\nDataset contains %d songs\n", songNumber);
        printf("=======================\n");
        printf("Press 'd' to show the most danceable song (any other key to quit): ");
        scanf(" %c", &input);

        if (input == 'd' && songNumber > 0) {
            Node* mostDanceable = removeMostDanceable(&head);
            if (mostDanceable != NULL) {
                printf("\n-------------------THE MOST DANCEABLE PLACE--------------------------------\n");
                printSong(mostDanceable->song);
                printf("-----------------------------------------------------------------\n\n");
                free(mostDanceable);
                songNumber--;
            }
        } else {
            break;
        }
    }

    clearList(&head);
    return 0;
}

