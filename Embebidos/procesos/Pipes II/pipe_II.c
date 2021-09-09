#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 4

void proceso_hijo(int np, int pipefd[]);
void proceso_padre(int pipefd[NUM_PROC][2]);

int *datos;
int main()
{
    srand(getpid());
    pid_t pid;
    int pipefd[NUM_PROC][2], edo_pipe;
    printf("Probando procesos...\n");
    for (register int np = 0; np < NUM_PROC; np++)
    {
    edo_pipe = pipe(&pipefd[np][0]);
        if (edo_pipe == -1)
        {
            perror("Error al crear la tuberia...");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("Error al crear el proceso...");
            exit(EXIT_FAILURE);
        }
        if (!pid)
        {
            proceso_hijo(np, &pipefd[np][0]);
        }
    }
    proceso_padre(pipefd);
    return 0;
    
}
void proceso_hijo(int np, int pipefd[])
{
    int num1 = 20, num2 = 4 , suma, resta, multi, div;
    close(pipefd[0]);
    if (np == 0)
    {
        suma = num1 + num2;
        write (pipefd[1], &suma, sizeof(int));
        }
    else if (np ==1)
    {
        resta = num1 - num2; 
        write (pipefd[1], &resta, sizeof(int));
        }
    else if (np ==2)
    {
        multi = num1 * num2; 
        write (pipefd[1], &multi, sizeof(int));
        }
    else if (np ==3)
    {
        div = num1 / num2; 
        write (pipefd[1], &div, sizeof(int));
        }
    
    
     
    close(pipefd[1]);
    exit(np);
}

void proceso_padre(int pipefd[NUM_PROC][2])
{
    register int np;
    pid_t pid;
    int estado, nproc, resultado;
    for(np = 0 ; np < NUM_PROC; np++)
    {
        pid = wait(&estado);
        nproc = estado >> 8;
        printf("Proceso %d terminado.\n", nproc);
        read(pipefd[nproc][0], &resultado, sizeof(int));
        close(pipefd[nproc][1]);

        switch (nproc)
        {
        case 0:
            printf ("El proceso %d con pind %d encontró que la suma es: %d\n", estado, pid, resultado);
            break;
        case 1:
            printf ("El proceso %d con pind %d encontró que la resta es: %d\n", estado, pid, resultado);
            break;
        case 2:
            printf ("El proceso %d con pind %d encontró que la multiplicación es: %d\n", estado, pid, resultado);
            break;
        case 3:
            printf ("El proceso %d con pind %d encontró que la división es: %d\n", estado, pid, resultado);
            break;
        
        default:
            printf("error, no se encontro opcion para este hijo\n");
            break;
        }
        close(pipefd[nproc][0]);
    }
}
