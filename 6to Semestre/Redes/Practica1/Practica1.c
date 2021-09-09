#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int inicio;
    int fin;
    int npalabras;
}parametro;

typedef struct 
{
    int *v;
    int total;
}val_return;


char ncuento[20][80];
char **palabras;
void nombresc();
void *hilo(void*arg);
int main(int argc, char *argv[])
{
    int nhilos, res, npr, final, npalabras, ini=0, i;
    if (argc < 2) printf("No se han intoducido los parámetros requeridos\n");
    else
    {
        nombresc();
        nhilos = atoi (*(argv + 1));
        npalabras = atoi (*(argv + 2));
        if (nhilos > 20) nhilos = 20;
        pthread_t *t;
        parametro *parametros;

        palabras = (char**)malloc(sizeof(char*)*npalabras);
        t = (pthread_t*)malloc(sizeof(pthread_t)*nhilos);
        parametros = (parametro*)malloc(sizeof(parametro)*nhilos);

        //printf("%d}}}}}}}}}}", npalabras);
        for (i = 0; i < npalabras; i++)
        {
            palabras[i]=(char*)malloc(sizeof(char)*sizeof(argv[i+3]));
            palabras[i]=argv[i+3];
            //printf ("%s, %lu\n", palabras[i], sizeof(argv[i+3]));
        }
        
        
        res = 20 % nhilos;
        npr = (20 - res) /nhilos;

        //printf("--%d--\n", nhilos);
        for (i = 0; i < nhilos; i++)
        {
            final = ini + npr - 1;
            (parametros + i)->inicio = ini;
            (parametros + i)->fin = final;
            (parametros + i)->npalabras = npalabras;
            pthread_create((t+i), NULL, hilo, (void*)(parametros+i));
            ini = final + 1;
            printf("%d--\n", i);
        }
        printf ("%d 99990999999999999\n", nhilos);
        fflush(stdout);
        for(i=0;i < nhilos;i++)
		    pthread_join(*(t+i),);
        printf ("%d´´´´´´´´´´", nhilos);
        fflush(stdout);

        free(t);
        printf ("\nfffffffffffffffff\n");
        fflush(stdout);
        free(parametros);
        // for (i = 0; i < npalabras; i++) 
        //       free(palabras[i]);
         free(palabras);
        
    }
    

}

void *hilo(void* arg)
{

    parametro *aux;
    aux = (parametro*) arg;

    int contador =0, a, ;

    FILE *archivo;
    int diferencia;
    val_return *valores;
    
    char palabra[20];

    diferencia=(aux->fin)-(aux->inicio);
    a = aux->npalabras;
    valores = (val_return*)malloc(sizeof(val_return)*((aux->fin)-(aux->inicio)));
    for(int i=0;i < ((aux->fin)-))
        valores[i]->v=(int*)malloc((sizeof(int)*a));
    int contadorp[a];
    printf("\n\nhilo %d xxx %d\n",aux->inicio, aux->fin );
    for(int i = aux->inicio ; i <= (aux->fin) ; i++)
    {
        valores[i]->total = 0;
        for (int j = 0; j < a; j++) contadorp[j]=0;
        archivo = fopen(ncuento[i], "r");
        
        if (archivo==NULL) printf("Archivo \"%s\" no encontrado\n\n", ncuento[i]);
        else
        {
            while (feof(archivo)==0)
            {
                
                fscanf(archivo, "%s", palabra);
                for (int j = 0; j < aux->npalabras; j++)
                {
                    if (strcmp(palabras[j], palabra) == 0)
                        contadorp[j]++;
                }
                
                contador++;
            }
            for (int j = 0; j < aux->npalabras; j++)
            {
                printf("%s -> %d \t",palabras[j], contadorp[j]);
            }
            
            printf("total palabras:%d\t%d\n", contador, i);
            
        }
            fclose(archivo);
        
    }
    printf ("1111111111 %d --- %d\n", aux->inicio, aux->fin);
    return 0;
}

void nombresc()
{
    char val[2];
    for (int i=0;i<20;i++)
    {
        strcpy(ncuento[i],"");
        sprintf(val, "%d",i+1);
        strcat(ncuento[i], "/home/usielarb/Escritorio/Practica1/Cuentos/Cuento");
        strcat(ncuento[i], val);
        strcat(ncuento[i], ".txt");
        
    }
    
}

