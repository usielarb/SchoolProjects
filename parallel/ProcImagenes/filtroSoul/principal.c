#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "imagen.h"
#include "defs.h"
#include "procesamiento.h"
#include "hilos.h"
bmpInfoHeader info;
unsigned char *imagenGray, *imagenFiltrada;

int main()
{
    register int nh;
    int *hilo, nhs[NUM_HILOS];
    pthread_t tids[NUM_HILOS];

    unsigned char *imagenRGB;

    char nomImagen[38] = "calle1";
    char nomImagenFinal[38] ;
    stpcpy(nomImagenFinal,nomImagen);
    strcat(nomImagenFinal, "Soul");
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

