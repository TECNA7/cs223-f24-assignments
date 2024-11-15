/*
 * Author: Kripa Lamichhane
 * Date: 11/14/2024
 * Description: A program that outputs a PPM image of the Buddhabrot using multiple threads
  **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

// global variables which can be accessed all over program
int size;
float xmin, xmax, ymin, ymax;
int maxIterations;
int numProcesses;
pthread_mutex_t countMutex;
pthread_barrier_t barrier;

// arrays to computation steps
int** membership;  
unsigned long long** counts;
unsigned long long max_count = 0;
struct ppm_pixel* final_image;

// using thread struct
struct thread_data {
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    pthread_t thread_id;
};

// initializing  2D integer array 
int** create_membership_array(int rows, int cols) {
    int** array = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        array[i] = calloc(cols, sizeof(int));  
    }
    return array;
}

// initializing 2D count array
unsigned long long** create_count_array(int rows, int cols) {
    unsigned long long** array = malloc(rows * sizeof(unsigned long long*));
    for (int i = 0; i < rows; i++) {
        array[i] = calloc(cols, sizeof(unsigned long long));
    }
    return array;
}

// Step 1: Determine mandelbrot set membership
void compute_membership(int start_row, int end_row, int start_col, int end_col) {
    for (int row = start_row; row < end_row; row++) {
        for (int col = start_col; col < end_col; col++) {
            float xfrac = (float)col / size;
            float yfrac = (float)row / size;
            float x0 = xmin + xfrac * (xmax - xmin);
            float y0 = ymin + yfrac * (ymax - ymin);
            
            float x = 0, y = 0;
            int iter = 0;
            while (iter < maxIterations && (x*x + y*y) < 4) {
                float xtmp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtmp;
                iter++;
            }
            
            membership[row][col] = (iter >= maxIterations) ? 1 : 0;
        }
    }
}

// Step 2: Compute visited counts
void compute_counts(int start_row, int end_row, int start_col, int end_col) {
    for (int row = start_row; row < end_row; row++) {
        for (int col = start_col; col < end_col; col++) {
            if (membership[row][col]) continue;

            float xfrac = (float)col / size;
            float yfrac = (float)row / size;
            float x0 = xmin + xfrac * (xmax - xmin);
            float y0 = ymin + yfrac * (ymax - ymin);
            
            float x = 0, y = 0;
            while ((x*x + y*y) < 4) {
                float xtmp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtmp;

                int yrow = round(size * (y - ymin)/(ymax - ymin));
                int xcol = round(size * (x - xmin)/(xmax - xmin));
                
                if (yrow < 0 || yrow >= size) continue;
                if (xcol < 0 || xcol >= size) continue;

                pthread_mutex_lock(&countMutex);
                counts[yrow][xcol]++;
                if (counts[yrow][xcol] > max_count) {
                    max_count = counts[yrow][xcol];
                }
                pthread_mutex_unlock(&countMutex);
            }
        }
    }
}

// Step 3: Compute colors
void compute_colors(int start_row, int end_row, int start_col, int end_col) {
    const float gamma = 0.681;
    const float factor = 1.0/gamma;
    
    for (int row = start_row; row < end_row; row++) {
        for (int col = start_col; col < end_col; col++) {
            float value = 0;
            
            if (counts[row][col] > 0) {
                value = log(counts[row][col]) / log(max_count);
                value = pow(value, factor);
            }
            
            unsigned char color = (unsigned char)(value * 255);
            final_image[row * size + col].red = color;
            final_image[row * size + col].green = color;
            final_image[row * size + col].blue = color;
        }
    }
}

// starting threAD
void* start(void* arg) {
    struct thread_data* data = (struct thread_data*)arg;
    
    printf("Thread %lu) sub-image block: cols (%d, %d) to rows (%d,%d)\n",
           pthread_self(), data->start_col, data->end_col, data->start_row, data->end_row);
    
    // Step 1: Do membership
    compute_membership(data->start_row, data->end_row, data->start_col, data->end_col);
    
    // Step 2: Do counts
    compute_counts(data->start_row, data->end_row, data->start_col, data->end_col);
    
    // waiting for all threads to finish 
    pthread_barrier_wait(&barrier);
    
    // Step 3: Compute colors
    compute_colors(data->start_row, data->end_row, data->start_col, data->end_col);
    
    printf("Thread %lu) finished\n", pthread_self());
    return NULL;
}

int main(int argc, char* argv[]) {
    size = 480;
    xmin = -2.5;
    xmax = 1.0;
    ymin = -1.12;
    ymax = 1.12;
    maxIterations = 1000;
    numProcesses = 4;

    int opt;
    while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
        switch (opt) {
            case 's': size = atoi(optarg); break;
            case 'l': xmin = atof(optarg); break;
            case 'r': xmax = atof(optarg); break;
            case 't': ymax = atof(optarg); break;
            case 'b': ymin = atof(optarg); break;
            case 'p': numProcesses = atoi(optarg); break;
            case '?': 
                printf("usage: %s -s <size> -l <xmin> -r <xmax> "
                       "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); 
                return 1;
        }
    }

    printf("Generating buddhabrot with size %dx%d\n", size, size);
    printf("  Num processes = %d\n", numProcesses);
    printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
    printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

    membership = create_membership_array(size, size);
    counts = create_count_array(size, size);
    final_image = malloc(size * size * sizeof(struct ppm_pixel));

    pthread_barrier_init(&barrier, NULL, numProcesses);

    //creting thread data
    struct thread_data* thread_data_array = malloc(numProcesses * sizeof(struct thread_data));
    
    // recornding start time
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // creating threads
    int rows_per_thread = size / 2;
    int cols_per_thread = size / 2;
    
    for (int i = 0; i < numProcesses; i++) {
        thread_data_array[i].start_row = (i / 2) * rows_per_thread;
        thread_data_array[i].end_row = thread_data_array[i].start_row + rows_per_thread;
        thread_data_array[i].start_col = (i % 2) * cols_per_thread;
        thread_data_array[i].end_col = thread_data_array[i].start_col + cols_per_thread;
        
        pthread_create(&thread_data_array[i].thread_id, NULL, start, &thread_data_array[i]);
    }

    // waiting for all threads to complete
    for (int i = 0; i < numProcesses; i++) {
        pthread_join(thread_data_array[i].thread_id, NULL);
    }

    // recording time  and calculate duration
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double duration = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    
    printf("Computed buddhabrot set (%dx%d) in %f seconds\n", size, size, duration);

    // Wwrtining files
    char filename[100];
    snprintf(filename, sizeof(filename), "buddhabrot-%d-%ld.ppm", size, time(0));
    printf("Writing file: %s\n", filename);
    write_ppm(filename, final_image, size, size);

    // freeing and destroying
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&countMutex);
    
    for (int i = 0; i < size; i++) {
        free(membership[i]);
        free(counts[i]);
    }
    free(membership);
    free(counts);
    free(final_image);
    free(thread_data_array);

    return 0;
}
