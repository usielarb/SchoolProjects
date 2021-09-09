#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "defs.h"

#include "image.h"
#include "thread.h"


unsigned char *allocate_memory(uint32_t width, u_int32_t height);
void rgb_to_gray(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height);
void gray_to_rgb(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height);
void gauss_filter(unsigned char *gray_image, unsigned char *result, uint32_t width, uint32_t height);

int main(){
    bmp_info_header info;
    unsigned char *rgb_image, *gray_image, *filtered_image;

    rgb_image = open_BMP("hoja.bmp", &info);

    display_information(&info);
    gray_image = allocate_memory(info.width, info.height);
    filtered_image = allocate_memory(info.width, info.height);
    memset(filtered_image, 255, info.width * info.height);


    rgb_to_gray(rgb_image, gray_image, info.width, info.height);
    p_gauss_filter(gray_image, filtered_image, info.width, info.height);
    // gauss_filter(gray_image, filtered_image, info.width, info.height);
    gray_to_rgb(rgb_image, filtered_image, info.width, info.height);

    save_BMP("result.bmp", &info, rgb_image);

    free(rgb_image);
    free(gray_image);
    free(filtered_image);

    return 0;
}



void gauss_filter(unsigned char *image, unsigned char *result, uint32_t width, uint32_t height){
    register int x, y, xm, ym;
    int kernel_i, image_i, convolution, factor = 330;

    int gauss_kernel[MASK_DIM * MASK_DIM] = {
        1,  4,  7,  4, 1,
        4, 20, 33, 20, 4,
        7, 33, 54, 33, 7,
        4, 20, 33, 20, 4,
        1,  4,  7,  4, 1
    };

    for (y = 0; y <= height - MASK_DIM; y++){
        for (x = 0; x <= width - MASK_DIM; x++){
            kernel_i = 0;
            convolution = 0;

            for (ym = 0; ym < MASK_DIM; ym++){
                for (xm = 0; xm < MASK_DIM; xm++){
                    image_i = (y + ym) * width + (x + xm);
                    convolution += image[image_i] * gauss_kernel[kernel_i++];
                }
            }

            convolution /= factor;
            image_i = (y + 2) * width + (x + 2);
            result[image_i] = convolution;
        }
    }
}

void gray_to_rgb(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height){
    for (int i = 0, j = 0; i < (height * width); i++, j += 3){
        rgb_image[j] = rgb_image[j + 1] = rgb_image[j + 2] = gray_image[i];
    }
}

void rgb_to_gray(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height){
    unsigned char gray_level;

    for (int i = 0, j = 0; i < height * width; i++, j += 3){
        gray_level = (30 * rgb_image[j] + 59 * rgb_image[j + 1] + 11 * rgb_image[j + 2]) / 100;
        gray_image[i] = gray_level;
    }
}

unsigned char *allocate_memory(uint32_t width, u_int32_t height){
    unsigned char * image = (unsigned char *)malloc(height * width * sizeof(unsigned char));
    if (image == NULL){
        perror("Error allocating memory for image");
        exit(EXIT_FAILURE);
    }

    return image;
}