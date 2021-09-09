#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void proceso_hijo(int np, int * datos)
{
    int resultado;
    printf("Ejecutando proceso hijo: %d\n", np);
    if (np == 0)
        resultado = buscarMayor(datos);
    else if (np == 1)
        resultado = buscarMenor(datos);
    else if (np == 2)
        resultado = sacarPromedio(datos);
    else if (np == 3)
        resultado = contarPares(datos);
    
        exit(resultado);
}

void proceso_padre()
{
    register int np;
    pid_t pid;
    int estado;
    for(np = 0 ; np < NUM_PROC; np++)
    {
        pid = wait(&estado);
            printf("El hijo con pid %d encontro este resultado: %d\n", pid, estado>>8);
        
        
    }
}