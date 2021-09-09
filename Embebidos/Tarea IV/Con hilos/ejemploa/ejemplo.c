#include <stdio.h>
#include <stdlib.h>
int main()
{
    int numero;
    FILE *archivo;
    archivo =  fopen("PulseSensor.dat", "r");
    int i;
    for ( i = 0; i < 4096; i++)
    {
        fscanf(archivo, "%d", &numero);
        printf("%d\n", numero);
    }
    
}