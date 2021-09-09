#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "defs.h"

#include "image.h"
#include "thread.h"


unsigned char *ReservarMemoria(uint32_t width, u_int32_t height);
void RBGToGray(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height);
void GraytoRGB(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height);
void gauss_filter(unsigned char *gray_image, unsigned char *result, uint32_t width, uint32_t height);

int main(){
    bmp_info_header info;
    unsigned char *rgb_image, *gray_image, *filtered_image;

    rgb_image = open_BMP("hoja.bmp", &info);

    display_information(&info);
    gray_image = ReservarMemoria(info.width, info.height);
    filtered_image = ReservarMemoria(info.width, info.height);
    memset(filtered_image, 255, info.width * info.height);


    RBGToGray(rgb_image, gray_image, info.width, info.height);
    p_gauss_filter(gray_image, filtered_image, info.width, info.height);
    GraytoRGB(rgb_image, filtered_image, info.width, info.height);

    save_BMP("result.bmp", &info, rgb_image);

    free(rgb_image);
    free(gray_image);
    free(filtered_image);

    return 0;
}


void GraytoRGB(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height){
    for (int i = 0, j = 0; i < (height * width); i++, j += 3){
        rgb_image[j] = rgb_image[j + 1] = rgb_image[j + 2] = gray_image[i];
    }
}

void RBGToGray(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height){
    unsigned char gray_level;

    for (int i = 0, j = 0; i < height * width; i++, j += 3){
        gray_level = (30 * rgb_image[j] + 59 * rgb_image[j + 1] + 11 * rgb_image[j + 2]) / 100;
        gray_image[i] = gray_level;
    }
}

unsigned char *ReservarMemoria(uint32_t width, u_int32_t height){
    unsigned char * image = (unsigned char *)malloc(height * width * sizeof(unsigned char));
    if (image == NULL){
        perror("Error reservando memoria");
        exit(EXIT_FAILURE);
    }

    return image;
}