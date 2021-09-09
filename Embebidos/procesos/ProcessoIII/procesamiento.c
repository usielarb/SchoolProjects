#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

int buscarMayor(int *datos)
{
    int mayor = 0;
    //printf("Buscando mayor");
    for (int i = 0; i < N; i++)
    {
        if (mayor <= datos[i])
            mayor = datos[i];
        //printf ("%d M ", mayor);
    }
    printf("\n");
    return mayor;
}

int buscarMenor(int *datos)
{
    int menor = 0;
    //printf("Buscando menor");
    menor = datos[0];
    for (int i = 0; i < N; i++)
    {
        if (menor >= datos[i])
            menor = datos[i];
            //printf ("%d m ", menor);}
    }
    //printf("MENOR %d\n", menor);
    
    return menor;
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