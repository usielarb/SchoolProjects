    #include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void* productor(void* arg);
void* consumidor(void* arg);
void iniciar_compro_sem(int n_cri, int *tam_cri);
//void crear_archivos(int n_archivos, int n_produc);
void imprimir_archivos (char caracter);
void crear_archivos (char caracter);

typedef struct 
{
    int n_cri;
    int *tam_cri;
    int n_i;
    char val;
}parametros;

typedef struct 
{
    int n_cri;
    int n_cons;
    //int n_i;
    int *tam_cri;
}parametros2;


int **productos;
sem_t **s_t, **s_t2;
sem_t *s_global;
sem_t s_global2;
char val[4]= {'0', 'A', 'a', '!'};


int main (int argc, char *argv[])
{
    int n_c, n_p, n_cri, n_con, n_i;
    int *tam_cri;
    parametros *parametro;
    parametros2 *parametro2;
    pthread_t *t_productor, *t_consumidor;
    
    n_p = atoi(*(argv + 1));
    n_c = atoi(*(argv + 2));
    n_i = atoi(*(argv + 3));
    n_cri = atoi(*(argv + 4));

    if (argc != 5 + n_cri) 
    {   
        printf("Datos ingresados incorrectamente\n<Número de Productores><Número de Consumidores><Número de iteraciones a realizar><Númerode zonas críticas>\n<Tamaño de la zona crítica 1><Tamaño de la zona crítica 2> ... <Tamaño de la zona crítica n>");
        exit(-1);
    }

    tam_cri = (int*)malloc(sizeof(int)*n_cri);

    for (int i = 0; i < n_cri; i++)
        tam_cri[i] = atoi(*(argv + 5 + i));  

    if (n_c > n_p * n_i) n_c = n_p * n_i;
    
    n_con = (n_p * n_i * n_cri) /  n_c ;
    printf (">>>>>>> %d <<<<<<<<\n", n_con);
    t_productor = (pthread_t*)malloc(sizeof(pthread_t)*n_p);
    t_consumidor = (pthread_t*)malloc(sizeof(pthread_t)*n_c);
    parametro = (parametros*)malloc(sizeof(parametros)*n_p);
    parametro2 = (parametros2*)malloc(sizeof(parametros2)*n_c);

    for (int i = 0; i < n_cri; i++)
    {
        parametro[i].tam_cri = (int*)malloc(sizeof(int)*n_cri);
        parametro2[i].tam_cri = (int*)malloc(sizeof(int)*n_cri);
    }

    iniciar_compro_sem(n_cri, tam_cri);
    //crear_archivos(n_cri,n_p);

    for (int i = 0; i < n_p; i++)
    {
        parametro[i].n_cri = n_cri;
        parametro[i].val = i;
        parametro[i].n_i = n_i;
        parametro[i].tam_cri = tam_cri;
        pthread_create(&t_productor[i], NULL, productor,(void*)&parametro[i]);
    }
    
    for (int i = 0; i < n_c; i++)
    {
        parametro2[i].n_cri = n_cri;
        parametro2[i].n_cons = n_con;
        //parametro2[i].n_i = n_i;
        parametro2[i].tam_cri = tam_cri;

        if (i<((n_p * n_i * n_cri) % n_c)) parametro2[i].n_cons ++;
            pthread_create(&t_consumidor[i], NULL, consumidor,(void *)&parametro2[i] );
    }

    for (int i = 0; i < n_p; i++)  
        pthread_join (t_productor[i], NULL);

    for (int i = 0; i < n_c; i++)
        pthread_join (t_consumidor[i], NULL);

    for (int i = 0; i < n_cri; i++)
    {
        for (int j = 0; j < tam_cri[i]; j++)
        {
            sem_destroy(&s_t[i][j]);
            sem_destroy(&s_t2[i][j]);
        }
    }
    for (int i = 0; i < n_cri; i++)
        sem_destroy(&s_global[i]);

    sem_destroy(&s_global2);

    free(parametro);
    free(t_consumidor);
    free(t_productor);
    free(s_t);
    free(s_t2);
    free(productos);
    free(s_global);
    return 0;
}


void* productor(void* arg){
    parametros* aux;
    int j=0, check;
    aux = (parametros*)arg;

    printf ("-Hilo productor de ");
    for (int i = 0; i < aux->n_cri; i++)
    {
        printf("%c ",val[i % 4] + aux->val);
        crear_archivos(val[i % 4] + aux->val);
    }
    printf (" %d-\n", aux->n_i);
    
    for (int i =0;i<aux->n_i;i++)
    {
        //printf("------\n");
        for(int k=0; k<aux->n_cri;k++)
        {
            sem_wait(&s_global[k]);
                check=0;
                j=0;
                while (check==0)
                {
                    j++;
                    if (j>= aux->tam_cri[k]) j=0;
                    sem_getvalue(&s_t[k][j], &check);
                    //printf ("[%d][%d] - %d\n",k,j, check);
                }
                sem_wait(&s_t[k][j]);
            sem_post(&s_global[k]);


            productos[k][j] = val[k % 4] + aux->val;
            //printf ("%d.- Produciendo %c en el espacio [%d][%d]\n",i, productos[k][j],k,j);
            sem_post(&s_t2[k][j]);
        }
    }
    return 0;
}
void* consumidor(void* arg){

    parametros2* aux;
    aux = (parametros2*)arg;
    int check, j=0, k=0;
    printf ("+Hilo Consumidor %d+\n", aux->n_cons);
    for (int i = 0; i < aux->n_cons; i++)
    {
        sem_wait(&s_global2);
        check=0;
        while (check==0)
        {
            j++;
            if (j>= aux->tam_cri[k]) 
                {
                    j=0;
                    k++;
                    if (k >= aux->n_cri) k=0;
                }
            sem_getvalue(&s_t2[k][j], &check);
            //printf("con - [%d][%d]->%d\n",k,j,check);
        }
        sem_wait(&s_t2[k][j]);
        //printf("####");
        imprimir_archivos(productos[k][j]);
        sem_post(&s_global2);

        //printf ("%d.- Consumiendo %c del espacio [%d][%d]\n",i, productos[k][j],k,j); 
        sem_post(&s_t[k][j]);
    }
    return 0;

}
//No iniciar el semaforo dentro de algún hilos porque solo sera accesible para este hilo
void iniciar_compro_sem(int n_cri, int *tam_cri)
{   
    s_t = (sem_t **)malloc(sizeof(sem_t*)*n_cri);
    for (int i = 0; i < n_cri; i++)
        s_t[i] = (sem_t *)malloc(sizeof(sem_t)*tam_cri[i]);
    
    s_t2 = (sem_t **)malloc(sizeof(sem_t*)*n_cri);
    for (int i = 0; i < n_cri; i++)
        s_t2[i] = (sem_t *)malloc(sizeof(sem_t)*tam_cri[i]);

    productos = (int**)malloc(sizeof(int*)*n_cri);
    for (int i = 0; i < n_cri; i++)
        productos[i] = (int *)malloc(sizeof(int)*tam_cri[i]);

    s_global = (sem_t *)malloc (sizeof(sem_t)*n_cri);    
    //s_global2 = (sem_t *)malloc (sizeof(sem_t)*n_cri);    

    for (int i = 0; i < n_cri; i++)
    {
        for (int j = 0; j < tam_cri[i]; j++)
        {       
            if (sem_init(&s_t[i][j], 0, 1 ) < 0 )
            {
                printf ("Error al crear el semáforo 1 - %d %d\n", i, j);
                exit(-1);
            }
        }
    }
    for (int i = 0; i < n_cri; i++)
    {
        for (int j = 0; j < tam_cri[i]; j++)
        {       
            if (sem_init(&s_t2[i][j], 0, 0 ) < 0 )
            {
                printf ("Error al crear el semáforo 2 - %d %d\n", i, j);
                exit(-1);
            }
        }
    }

    for (int j = 0; j < n_cri; j++)
    {       
        if (sem_init(&s_global[j], 0, 1 ) < 0 )
        {
            printf ("Error al crear el semáforo global 1 - %d\n", j);
            exit(-1);
        }
    }
    
        
    if (sem_init(&s_global2, 0, 1 ) < 0 )
    {
        printf ("Error al crear el semáforo global 2 - \n");
        exit(-1);
    }
    
}
// void crear_archivos(int n_archivos, int n_produc)
// {
//     char nombre_c[20], c;
//     FILE *archivo = NULL;
//     for (int i = 0; i < n_produc; i++)
//     {
//         for (int j = 0; j < n_archivos; j++)
//         {
//             strcpy(nombre_c,"");
//             c = val[j%4] + i;
//             strcat(nombre_c, &c);
//             //sprintf(&c_val, "%d", val[j%4] + i);
//             strcat(nombre_c, ".txt");
//             archivo = fopen(nombre_c, "w");
//             if (archivo==NULL)  printf("Error al crear %s",nombre_c);
//             else printf ("archivo abierto %s-\n",nombre_c);
//             fclose(archivo);
//         }
//     }
//     //return 0;
// }

void imprimir_archivos (char caracter)
{
    char nombre_c[20];
    FILE *archivo = NULL;
    strcpy(nombre_c, "");
    strcat(nombre_c,&caracter);
    strcat(nombre_c,".txt");
    archivo = fopen(nombre_c, "a"); 
    if (archivo == NULL) 
    {
        printf ("Error al imprimir %c \n", caracter);
        exit(-1);
    }
    fprintf(archivo, "%c\n",caracter);
    fclose(archivo);
}
void crear_archivos (char caracter)
{
    char nombre_c[20];
    FILE *archivo = NULL;
    strcpy(nombre_c, "");
    strcat(nombre_c,&caracter);
    strcat(nombre_c,".txt");
    archivo = fopen(nombre_c, "w"); 
    if (archivo == NULL) 
    {
        printf ("Error al imprimir %c \n", caracter);
        exit(-1);
    }
    //fprintf(archivo, "%c\n",caracter);
    fclose(archivo);
}