#include <stdio.h>
#include "defs.h"
#include <stdlib.h>

void guardarDatos(float datos[])
{
    FILE *apArch;
    register int n;
    apArch = fopen("seno.dat", "w");
    if (apArch == NULL)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    for (n=0;n<MUESTRAS;n++){
        fprintf(apArch,"%f\n", datos[n]);
        //printf("%f \n", datos[n]);
    }
    fclose(apArch);
}