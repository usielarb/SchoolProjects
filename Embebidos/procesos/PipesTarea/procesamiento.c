#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

void burbuja(int *datos)
{
    //imprimirArreglo(datos);
    //printf ("---");
    int aux;
    for (int j = 0; j < N; j++)
    {
        for (int  i = 0; i < N-j; i++)
        {
            if (datos[i] > datos[i+1])
            {
                aux = datos[i];
                datos[i] = datos[i+1];
                datos[i+1] = aux;
            }
        }
    }
    //imprimirArreglo(datos);
}
void MultiC(int *datos)
{
    for (int i = 0; i < N; i++)
        datos[i] = datos[i] * constante;
}
int sacarPromedio(int *datos)
{
    int suma = 0, promedio = 0;
    int register i;
    for ( i = 0; i < N; i++)
        suma+=datos[i];
    promedio = suma / N;
    return promedio;    
}
int contarPares(int *datos)
{
    int cont = 0;
    int register i;
    for ( i = 0; i < N; i++)
    {
        if (!(datos[i] % 2))
            cont++;
    }
    //printf ("%d pares\n", cont);
    return cont;
}