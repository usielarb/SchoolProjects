#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "image.h"
#include "thread.h"

unsigned char *open_BMP(char *filename, bmp_info_header *info_header){
    FILE *f;
    bmp_file_header header;
    unsigned char *image_data;
    uint16_t type;

    // Opening file
    f = fopen(filename, "r");
    if (f == NULL){
        perror("Error opening the file in read mode");
        exit(EXIT_FAILURE);
    }

    // Cheking file type
    fread(&type, sizeof(uint16_t), 1, f);
    if (type != 0x4D42){
        printf("The file %s provided is not a BMP 24 bits image valid", filename);
        fclose(f);
        exit(EXIT_FAILURE);
    }

    // Reading file header
    fread(&header, sizeof(bmp_file_header), 1, f);
    // Reading image header
    fread(info_header, sizeof(bmp_info_header), 1, f);

    // Reading image
    image_data = (unsigned char *)malloc(info_header->imgsize);
    if (image_data == NULL){
        perror("Error reserving memory");
        exit(EXIT_FAILURE);
    }

    fseek(f, header.offset, SEEK_SET);
    fread(image_data, info_header->imgsize, 1, f);
    fclose(f);

    return image_data;
}

void save_BMP(char *filename, bmp_info_header *info_header, unsigned char *image_data){
    bmp_file_header header;
    FILE *f;
    uint16_t type;

    f = fopen(filename, "w+");
    if (f == NULL){
        printf("Error opening %s file", filename);
        exit(EXIT_FAILURE);
    }

    header.size = info_header->imgsize + sizeof(bmp_file_header) + sizeof(bmp_info_header) + 2;
    header.offset = sizeof(bmp_file_header) + sizeof(bmp_info_header) + 2;
    type = 0x4D42;

    fwrite(&type, sizeof(type), 1, f);
    fwrite(&header, sizeof(bmp_file_header), 1, f);
    fwrite(info_header, sizeof(bmp_info_header), 1, f);

    fseek(f, header.offset, SEEK_SET);

    fwrite(image_data, info_header->imgsize, 1, f);
    fclose(f);
}

void display_information(bmp_info_header *info_header){
    printf("Header size: %u\n", info_header->headersize);
    printf("Width: %d\n", info_header->width);
    printf("Height: %d\n", info_header->height);
    printf("Number of color planes (1): %d\n", info_header->planes);
    printf("Number of bits per pixel: %d\n", info_header->bpp);
    printf("Compression used: %d\n", info_header->compress);
    printf("Size of the raw bitmap data: %u\n", info_header->imgsize);
    printf("Horizontal resolution: %u\n", info_header->bpmx);
    printf("Vertical resolution: %u\n", info_header->bpmy);
    printf("Colors in the palette: %d\n", info_header->colors);
    printf("Important colors: %d\n", info_header->imxtcolors);
}

void take_photo(bmp_info_header * info, unsigned char *imagen){
    system ("raspistill -n -t 500 -e bmp -w 640 -h 480 -o foto.bmp");
    system ("magick convert foto.bmp -resize 50% foto.bmp");
    imagen = open_BMP("foto.bmp", info );
}

void rgb_to_gray(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height){
    unsigned char gray_level;

    for (int i = 0, j = 0; i < height * width; i++, j += 3){
        gray_level = (30 * rgb_image[j] + 59 * rgb_image[j + 1] + 11 * rgb_image[j + 2]) / 100;
        gray_image[i] = gray_level;
    }
}

void gray_to_rgb(unsigned char *rgb_image, unsigned char *gray_image, uint32_t width, uint32_t height){
    for (int i = 0, j = 0; i < (height * width); i++, j += 3){
        rgb_image[j] = rgb_image[j + 1] = rgb_image[j + 2] = gray_image[i];
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

void process_image(bmp_info_header * info, unsigned char *image){
    unsigned char *gray = allocate_memory(info->width, info->height);
    unsigned char *filtered = allocate_memory(info->width, info->height);

    rgb_to_gray(image, gray, info->width, info->height);
    p_sobel(gray, filtered, info->width, info->height);
    gray_to_rgb(image, filtered, info->width, info->height);

    free(gray);
    free(filtered);
}

