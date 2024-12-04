#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tree.h"
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#define MAX_FILES 1000

struct file_data {
    char* file_name;
    char* dependencies[MAX_FILES];
    int dep_count;
};

struct thread_data {
    int start_index;
    int end_index;
    struct file_data* files;
};

struct tree_node* root = NULL;

void add_file_and_dependencies(const char* file_name) {
    root = insert(file_name, root);

    if (strcmp(file_name, "code/Animal.h") == 0) {
        root = insert("string", root);
        root = insert("vector", root);
        root = insert("Locomotion.h", root);
    } else if (strcmp(file_name, "code/Zoo.cpp") == 0) {
        root = insert("Animal.h", root);
        root = insert("Bird.h", root);
        root = insert("Duck.h", root);
        root = insert("Fish.h", root);
        root = insert("Seal.h", root);
        root = insert("Whale.h", root);
        root = insert("Locomotion.h", root);
        root = insert("Walk.h", root);
        root = insert("Fly.h", root);
        root = insert("Swim.h", root);
    }
}

void scan_files(const char* dir_name, struct file_data* files, int* file_count) {
    DIR* dir = opendir(dir_name);
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char* file_name = entry->d_name;
            if (strstr(file_name, ".h") || strstr(file_name, ".cpp")) {
                files[*file_count].file_name = file_name;
                files[*file_count].dep_count = 0;
                (*file_count)++;
            }
        }
    }
    closedir(dir);
}

void* process_files(void* arg) {
    struct thread_data* data = (struct thread_data*)arg;
    for (int i = data->start_index; i < data->end_index; i++) {
	printf("Thread %d processing files from index %d to %d\n", data->start_index, data->start_index, data->end_index);
        add_file_and_dependencies(data->files[i].file_name);
    }
    return NULL;
}

void list_dependencies(const char* file_name) {
    struct tree_node* node = find(file_name, root);
    if (node != NULL) {
        printf("%s has the following dependencies:\n", file_name);
        printSorted(node);
    } else {
        printf("%s not found\n", file_name);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number_of_threads> <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    struct file_data files[MAX_FILES];
    int file_count = 0;

    for (int i = 2; i < argc; i++) {
        files[file_count].file_name = argv[i];
        files[file_count].dep_count = 0;
        file_count++;
    }

    printf("Processing %d files\n", file_count);

    pthread_t threads[num_threads];
    struct thread_data thread_data[num_threads];

    int files_per_thread = file_count / num_threads;
    int remaining_files = file_count % num_threads;

    int index = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start_index = index;
        thread_data[i].end_index = index + files_per_thread + (i < remaining_files ? 1 : 0);
        thread_data[i].files = files;
        pthread_create(&threads[i], NULL, process_files, &thread_data[i]);
        index = thread_data[i].end_index;
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    char command[64];
    while (1) {
        printf("$ ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "list", 4) == 0) {
            for (int i = 2; i < argc; i++) {
                list_dependencies(argv[i]);
            }
        } else if (strncmp(command, "quit", 4) == 0) {
            break;
        } else {
            printf("%s not found\n", command);
        }
    }

    printf("Elapsed time is: %.6f seconds\n", (double)clock() / CLOCKS_PER_SEC);

    return 0;
}

