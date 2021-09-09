#include <stdio.h>
#include "defs.h"
#include <stdlib.h>

void guardarDatos(float datos[], char  archivo[])
{
    FILE *apArch;
    register int n;
    apArch = fopen(archivo, "w");
    if (apArch == NULL)
    {
        perror("Error al abrir el archivo");
        printf("%s\n", archivo);
        exit(EXIT_FAILURE);
    }
    for (n=0;n<N;n++){
        fprintf(apArch,"%f\n", datos[n]);
        //printf("%f \n", datos[n]);
    }
    fclose(apArch);
}

void leerDatos(float datos[], char archivo[])
{
    FILE *apArch;
    
    register int n;
    int aux;
    apArch = fopen(archivo, "r");
    if (apArch == NULL)
    {
        perror("Error al abrir el archivo");
        printf("%s\n", archivo);
        exit(EXIT_FAILURE);
    }
    for (n=0;n<N;n++){
        //fprintf(apArch,"%f\n", datos[n]);
        //printf("%f \n", datos[n]);
        fscanf(apArch,"%d", &aux);
        datos[n] = aux - 2200;
    }
    fclose(apArch);

}

