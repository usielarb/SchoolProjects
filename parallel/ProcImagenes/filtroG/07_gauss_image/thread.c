#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "defs.h"

typedef struct arguments {
    int thread;

    int *kernel;
    int factor;

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

void filter_row(unsigned char *image, unsigned char *result, uint32_t width, uint32_t height, int *kernel, int factor, int y){
    register int x;
    int image_i;

    for (x = 0; x < width - MASK_DIM; ++x){
        image_i = (y + 2) * width + (x + 2);
        result[image_i] = convolution(image, x, y, width, kernel) / factor;
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
    
    int *kernel = a->kernel;
    int factor = a->factor;

    unsigned char *image = a->image;
    unsigned char *result = a->result;

    uint32_t width = a->width;
    uint32_t height = a->height;

    int thread = f_thread_index(pthread_self());

    int block = (height - MASK_DIM) / THREADS;
    int begin = thread * block;
    int end = begin + block;

    for (int y = begin; y < end; ++y){
        filter_row(image, result, width, height, kernel, factor, y);
    }

    if (thread == 0){
        for (int y = block * THREADS; y < height - MASK_DIM; ++y){
            filter_row(image, result, width, height, kernel, factor, y);
        }
    }


    // for (int y = thread; y < height - MASK_DIM; y += THREADS){
    //     filter_row(image, result, width, height, kernel, factor, y);
    // }

    return NULL;
}

void p_gauss_filter(unsigned char *image, unsigned char *result, uint32_t width, uint32_t height){
    int kernel[MASK_DIM * MASK_DIM] = {
        1,  4,  7,  4, 1,
        4, 20, 33, 20, 4,
        7, 33, 54, 33, 7,
        4, 20, 33, 20, 4,
        1,  4,  7,  4, 1
    };

    int factor = 330;

    arguments args;
    args.factor = factor;
    args.kernel = kernel;
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
}
