#include <stdio.h>
#include <stdint.h>

#ifndef IMAGE_HEADER_C
#define IMAGE_HEADER_C

typedef struct bmp_file_header {
    uint32_t size;
    uint16_t resv1;
    uint16_t resv2;
    uint32_t offset;
} bmp_file_header;

typedef struct bmp_info_header {
    uint32_t headersize;  /* Tamaño de la cabecera */
    uint32_t width;       /* Ancho */
    uint32_t height;      /* Alto */
    uint16_t planes;      /* Planos de color (Siempre 1) */
    uint16_t bpp;         /* bits por pixel */
    uint32_t compress;    /* compresión */
    uint32_t imgsize;     /* tamaño de los datos de imagen */
    uint32_t bpmx;        /* Resolución X en bits por metro */
    uint32_t bpmy;        /* Resolución Y en bits por metro */
    uint32_t colors;      /* colors used en la paleta */
    uint32_t imxtcolors;  /* Colores importantes. 0 si son todos */
} bmp_info_header;

unsigned char *open_BMP(char *filename, bmp_info_header *info_header);
void save_BMP(char *filename, bmp_info_header *info_header, unsigned char *image_data);
void display_information(bmp_info_header *info_header);

void WriteImage(const char *fileName, unsigned char *pixels, uint32_t width, uint32_t height, uint32_t bytesPerPixel);

void take_photo(bmp_info_header * info, unsigned char *imagen);
void process_image(bmp_info_header * info, unsigned char *image);

#endif