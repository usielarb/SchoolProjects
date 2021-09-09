#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "imagen.h"
#include "defs.h"
#include "procesamiento.h"
bmpInfoHeader info;
unsigned char *imagenGray, *imagenFiltrada;



// unsigned char *reservar_memoria(uint32_t width, uint32_t height);
// void filtroPB(int inicio, int final);
// void RGBtoGray(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height);
// void GraytoRGB(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height);
// void brilloImagen(unsigned char *imagenGray,uint32_t width,uint32_t height);
// void *funHilo(void *arg);


int main()
{
    register int nh;
    int *hilo, nhs[NUM_HILOS];
    pthread_t tids[NUM_HILOS];

    unsigned char *imagenRGB;

    char nomImagen[38] = "hoja";
    char nomImagenFinal[38] ;
    stpcpy(nomImagenFinal,nomImagen);
    strcat(nomImagenFinal, "Filtrada");
    strcat(nomImagen,".bmp");
    strcat(nomImagenFinal,".bmp");
    //printf("%s, %s", nomImagen, nomImagenFinal);
    imagenRGB = abrirBMP(nomImagen, &info);
    displayInfo(&info);

    imagenGray = reservar_memoria(info.width, info.height);
    imagenFiltrada = reservar_memoria(info.width, info.height);
    memset(imagenFiltrada, 255, info.width * info.height);

    RGBtoGray(imagenRGB, imagenGray, info.width, info.height);


    for (nh = 0; nh < NUM_HILOS; nh++)
    {
        nhs[nh] = nh;
        pthread_create(&tids[nh], NULL, funHilo, (void *)&nhs[nh]);
        printf ("todo kul\n");
    }

    for (nh = 0; nh < NUM_HILOS; nh++)
        pthread_join(tids[nh], (void **)&hilo);

    GraytoRGB(imagenRGB, imagenFiltrada, info.width, info.height);

    guardarBMP(nomImagenFinal, &info, imagenRGB);

    free(imagenRGB);
    free(imagenGray);
    free(imagenFiltrada);

    return 0;
}



// void filtroPB(int inicio, int final)
// {
//     register int x, y, xm, ym;
//     int indicem, indicei, conv;
//     int mascara[DMASK * DMASK] = {
//         1, 4, 7, 4, 1,
//         4, 20, 33, 20, 4,
//         7, 33, 54, 33, 7,
//         4, 20, 33, 20, 4,
//         1, 4, 7, 4, 1};

//     for (y = inicio; y <= final; y++)
//     {
//         for (x = 0; x <= info.width - DMASK; x++)
//         {
//             indicem = 0;
//             conv = 0;
//             for (ym = 0; ym < DMASK; ym++)
//             {
//                 for (xm = 0; xm < DMASK; xm++)
//                 {
//                     indicei = (y + ym) * info.width + (x + xm);
//                     conv += mascara[indicem++] * imagenGray[indicei];
//                 }
//             }
//             conv = conv / 330;
//             indicei = (y + 2) * info.width + (x + 2);
//             imagenFiltrada[indicei] = conv;
//         }
//     }
// }

// unsigned char *reservar_memoria(uint32_t width, uint32_t height)
// {
//     unsigned char *imagen;
//     imagen = (unsigned char *)malloc(width * height * sizeof(unsigned char));
//     if (imagen == NULL)
//     {
//         perror("Error en la memoria de la imagen");
//         exit(EXIT_FAILURE);
//     }
//     return imagen;
// }

// void RGBtoGray(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height)
// {
//     unsigned char nivelGris;
//     int indiceGray, indiceRGB;
//     for (indiceGray = 0, indiceRGB = 0; indiceGray < (height * width); indiceGray++, indiceRGB += 3)
//     {
//         nivelGris = (imagenRGB[indiceRGB] * 30 + imagenRGB[indiceRGB + 1] * 59 + imagenRGB[indiceRGB + 2] * 11) / 100;
//         imagenGray[indiceGray] = nivelGris;
//     }
// }

// void GraytoRGB(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height)
// {
//     int indiceGray, indiceRGB;
//     for (indiceGray = 0, indiceRGB = 0; indiceGray < (height * width); indiceGray++, indiceRGB += 3)
//     {
//         imagenRGB[indiceRGB] = imagenGray[indiceGray];
//         imagenRGB[indiceRGB + 1] = imagenGray[indiceGray];
//         imagenRGB[indiceRGB + 2] = imagenGray[indiceGray];
//     }
// }

// void brilloImagen(unsigned char *imagenGray,uint32_t width,uint32_t height){
//     register int indiceGray;
//     int pixel;

//     for(indiceGray=0; indiceGray<(width*height) ; indiceGray++){
//         pixel = imagenGray[indiceGray] +70;
//         imagenGray[indiceGray] = (pixel>255)? 255 : (unsigned char)pixel;
//     }
// }

// void *funHilo(void *arg)
// {
//     int nhilo = *(int *)arg;
//     int nucleo = (info.height - DMASK) / NUM_HILOS; 
//     int inicio = nhilo * nucleo;
//     int final;
//     if (nhilo == NUM_HILOS - 1)
//         final = info.height - DMASK;
//     else
//         final = inicio + nucleo;
//     filtroPB(inicio, final);
//     pthread_exit(arg);
// }