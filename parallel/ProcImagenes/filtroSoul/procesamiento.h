#ifndef PROC_H
#define PROC_H

unsigned char *reservar_memoria(uint32_t width, uint32_t height);
void filtroPB(int inicio, int final);
void Sobel(int inicio, int final);
void RGBtoGray(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height);
void GraytoRGB(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height);
void brilloImagen(unsigned char *imagenGray,uint32_t width,uint32_t height);
void *funHilo(void *arg);

#endif