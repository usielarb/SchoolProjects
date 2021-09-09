
#include <stdio.h>
#include "archivos.h"
#include "procesamiento.h"
#include "defs.h"

int main ()
{
    float seno[MUESTRAS];
    genera_seno(seno);
    guardarDatos(seno);
    return 0;
}


// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>
// #define MUESTRAS 512

// void generaSeno(float datos[]);
// void guardarDatos(float seno[]);

// int main ()
// {
//     float seno[MUESTRAS];
//     generaSeno(seno);
//     guardarDatos(seno);
//     return 0;
// }

// void generaSeno(float seno[]){
//     float f = 1000, fs =45000;
//     register int n;
//     for (n = 0; n < MUESTRAS; n++)
//     {
//         seno[n] = sinf (2 *  M_PI * f * n / fs);
//     }
// }

// void guardarDatos(float datos[])
// {
//     FILE *apArch;
//     register int n;
//     apArch = fopen("seno.dat", "w");
//     if (apArch == NULL)
//     {
//         perror("Error al abrir el archivo");
//         exit(EXIT_FAILURE);
//     }
//     for (n=0;n<MUESTRAS;n++){
//         fprintf(apArch,"%f\n", datos[n]);
//         printf("%f \n", datos[n]);
//     }
//     fclose(apArch);
// }

