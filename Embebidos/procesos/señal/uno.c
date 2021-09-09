#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void manejador (int sig);
int main ()
{
    if (signal (SIGINT, manejador) == SIG_ERR)
    {
        perror("Error en el manejador de SIGINT\n");
    }
    if (signal (SIGTERM, manejador) == SIG_ERR)
    {
        perror("Error en el manejador de SIGINT\n");
    }
    while (1)
    {
        pause();
    }
    return 0;
}
void manejador (int sig)
{
    if (sig == SIGINT)
        printf ("No voy a terminar...\n");
    else if (sig == SIGTERM)
        printf("Que no lo hare!\n");
    
}
