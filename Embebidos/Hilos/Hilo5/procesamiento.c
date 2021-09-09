#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "defs.h"
#include "helper.h"

//extern int* datos;

void burbuja(int* datos)
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
}int sacarPromedio(int* datos)
{
    int suma = 0, promedio = 0;
    int register i;
    for ( i = 0; i < N; i++)
        suma+=datos[i];
    promedio = suma / N;
    return promedio;    
}
int contarPares(int* datos)
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
int contarPrimos(int* datos)
{
    int arrPrimos[54], k = 0, cont = 0;
    char esPrimo;
    for (int register i = 2; i < 256; i++)
    {
        esPrimo = 1;
        for (int register j = 2 ; j < i ;  j++)
        {
            if (!(i % j))
            {
                esPrimo = 0;
                break;
            }
        }
        if (esPrimo)
        {
            arrPrimos[k] = i;
            //printf("%d . ", i);
            k++;
        }
    }
    printf("\n\t<PRIMOS>\n");
    for (int register i = 0; i < N; i++)
    {
        for (int register  j = 0; j < 54; j++)
        {
            if (datos[i] < arrPrimos[j])
                break;

            if (datos[i] == arrPrimos[j])
            {
                printf ("%3d ",datos[i]);
                cont ++;
                if (!(cont%16))
                    printf ("\n");
                break;
            }
        }
    }
    printf ("\n\n");
    return cont;
    
}