#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "defs.h"

#define THREADS 4
#define MASK_DIM 3

typedef struct arguments {
    int thread;

    int *row_gradient;
    int *column_gradient;

    unsigned char *image;
    unsigned char *result;

    uint32_t width;
    uint32_t height;
} arguments;

pthread_t threads[THREADS];

int convolution(unsigned char *image, int x, int y, int width , int *kernel){
    register int i, j, k = 0;
    int image_i, convolution = 0;

    for (i = 0; i < MASK_DIM; ++i){
        for (j = 0; j < MASK_DIM; ++j){
            image_i = (y + i) * width + (x + j);
            convolution += image[image_i] * kernel[k++];
        }
    }

    return convolution;
}

void filter_row(arguments *a, int y){
    register int x;
    int image_i, row_conv, column_conv;

    for (x = 0; x < a->width - MASK_DIM; ++x){
        image_i = (y + 1) * a->width + (x + 1);

        row_conv = convolution(a->image, x, y, a->width, a->row_gradient) >> 2;
        column_conv = convolution(a->image, x, y, a->width, a->column_gradient) >> 2;

        a->result[image_i] = (unsigned char)sqrt((row_conv * row_conv) + (column_conv * column_conv));
    }
}

int f_thread_index(pthread_t pid){
    for (int i = 0; i < THREADS; ++i){
        if (pthread_equal(pid, threads[i])){
            return i;
        }
    }

    return -1;
}

void *thread_filter(void *args){
    arguments *a = (arguments *)args;

    int thread = f_thread_index(pthread_self());

    int block = (a->height - MASK_DIM) / THREADS;
    int begin = thread * block;
    int end = begin + block;

    for (int y = begin; y < end; ++y){
        filter_row(args, y);
    }

    if (thread == 0){
        for (int y = block * THREADS; y < a->height - MASK_DIM; ++y){
            filter_row(args, y);
        }
    }

    return NULL;
}

void *p_sobel(unsigned char *image, unsigned char *result, uint32_t width, uint32_t height){
    int row_gradient[MASK_DIM * MASK_DIM] = {
        1, 0, -1,
        2, 0, -2,
        1, 0, -1
    };

    int column_gradient[MASK_DIM * MASK_DIM] = {
        -1, -2, -1,
         0,  0,  0,
         1,  2,  1
    };

    arguments args;
    args.row_gradient = row_gradient;
    args.column_gradient = column_gradient;
    args.image = image;
    args.result = result;
    args.width = width;
    args.height = height;

    for (int i = 0; i < THREADS; ++i){
        pthread_create(&(threads[i]), NULL, thread_filter, &args);
    }

    for (int i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);
        printf("Thread %d has finished.\n", i);
    }

    return NULL;
}
