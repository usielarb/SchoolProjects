#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "image.h"

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