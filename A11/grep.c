/**Author : Kripa Lamichhane
 * Date : 11/30/2024
 * Description:  a simplified version of the bash command grep. Grep searches a list of files for a given keyword or expression. For example, the following command searches for the keyword public in a list of source files
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t lock;

struct thread_data {
    int start, end, id, count;
    char **files;
    char *keyword;
};

void *search(void *userdata) {
    struct thread_data *data = (struct thread_data *)userdata;
    FILE *searchFile;
    char line[100];
    data->count = 0;

    for (int i = data->start; i < data->end; ++i) {
        searchFile = fopen(data->files[i], "r");
        if (!searchFile) {
            pthread_mutex_lock(&lock);
            printf("Thread %d: Unable to open file %s\n", data->id, data->files[i]);
            pthread_mutex_unlock(&lock);
            continue;
        }

        while (fgets(line, sizeof(line), searchFile)) {
            if (strstr(line, data->keyword)) {
                data->count++;
                pthread_mutex_lock(&lock);
                printf("Thread %d) %s: %s", data->id, data->files[i], line);
                pthread_mutex_unlock(&lock);
            }
        }
        fclose(searchFile);
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: ./grep <NumThreads> <Keyword> <Files...>\n");
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        fprintf(stderr, "Number of threads must be a positive number\n");
        return 1;
    }

    char *keyword = argv[2];
    int file_count = argc - 3;
    char **files = &argv[3];

    printf("Found %d files. Searching for keyword: '%s'\n", file_count, keyword);

    struct timeval tstart, tend;
    gettimeofday(&tstart, NULL);

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    struct thread_data *data = malloc(num_threads * sizeof(struct thread_data));

    int subsize = file_count / num_threads;
    int remainder = file_count % num_threads;

    pthread_mutex_init(&lock, NULL);

    for (int j = 0; j < num_threads; j++) {
        data[j].files = files;
        data[j].keyword = keyword;
        data[j].id = j;
        data[j].count = 0;
        data[j].start = subsize * j;
        data[j].end = subsize * (j + 1) + (j == num_threads - 1 ? remainder : 0);

        pthread_create(&threads[j], NULL, search, (void *)&data[j]);
        printf("Thread %d searching %d files (%d to %d)\n", data[j].id, data[j].end - data[j].start, data[j].start, data[j].end);
    }

    int total_matches = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_matches += data[i].count;
    }

    gettimeofday(&tend, NULL);
    double elapsed_time = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec) / 1e6;
    printf("Elapsed time: %g seconds\n", elapsed_time);

    for (int i = 0; i < num_threads; i++) {
        printf("Thread %d found %d matches\n", data[i].id, data[i].count);
    }

    printf("Total matches: %d\n", total_matches);

    free(threads);
    free(data);

    pthread_mutex_destroy(&lock);
    return 0;
}

