#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
void* productor(void* arg);
void* consumidor(void* arg);
void iniciar_compro_sem(int n_cri);

typedef struct 
{
    int n_cri;
    int n_i;
    char val;
}parametros;

typedef struct 
{
    int n_cri;
    char n_cons;
    int n_i;
}parametros2;


char val[4]= {'0','A', 'a', '!'};
int *nproductos;
int *nproductos2;
sem_t *s_t, *s_t2;
sem_t *s2_t, *s2_t2;
sem_t s_global, s_global2;
sem_t s2_global, s2_global2;

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

    tam_cri = (int *)malloc(sizeof(int)*n_cri);

    for (int i=0; i<)

    if (argc != 5) exit(-1);

    if (n_c>n_p*20) n_c=n_p*10;
    n_con = (n_p * 20) /  n_c ;

    t_productor = (pthread_t*)malloc(sizeof(pthread_t)*n_p);
    t_consumidor = (pthread_t*)malloc(sizeof(pthread_t)*n_c);
    parametro = (parametros*)malloc(sizeof(parametros)*n_p);
    parametro2 = (parametros2*)malloc(sizeof(parametros2)*n_c);

    iniciar_compro_sem(n_cri);

    for (int i = 0; i < n_p; i++)
    {
        parametro[i].n_cri = n_cri;
        parametro[i].val = i;
        parametro[i].n_i = n_i;
        pthread_create(&t_productor[i], NULL, productor,(void*)&parametro[i]);
    }
    
    for (int i = 0; i < n_c; i++)
    {
        parametro2[i].n_cri = n_cri;
        parametro2[i].n_cons = n_con;
        parametro2[i].n_i = n_i;

        if (i<(n_p*20 % n_c)) parametro2[i].n_cons ++;
        pthread_create(&t_consumidor[i], NULL, consumidor,(void *)&parametro2[i] );
    }

    for (int i = 0; i < n_p; i++)  
        pthread_join (t_productor[i], NULL);

    for (int i = 0; i < n_c; i++)
        pthread_join (t_consumidor[i], NULL);

    for (int i = 0; i < n_cri; i++)
    {
        sem_destroy(&s_t[i]);
        sem_destroy(&s_t2[i]);
    }
    sem_destroy(&s_global);
    sem_destroy(&s_global2);

    free(parametro);
    free(t_consumidor);
    free(t_productor);
    free(s_t);
    free(s_t2);
    free(nproductos);
    free(s_global);
    free(s2_global);
    free(s2_global2);
    free(s_global2);
    return 0;
}
void* productor(void* arg){
    parametros* aux;
    int j=0, val;
    aux = (parametros*)arg;

    printf ("-Hilo productor de %c-\n", aux->val);
    for (int i =0;i<aux->n_i;i++)
    {
        val=0;
        sem_wait(&s_global);
            while (val==0)
            {
                if (j == aux->n_cri) j=0;
                sem_getvalue(&s_t[j], &val);
                j++;
                //printf ("%d - %d\n",j%aux->n_cri, val);
            }
            sem_wait(&s_t[j]);
        sem_post(&s_global);


        nproductos[j] = aux->val;
        printf ("%d.- Produciendo %c\n",i+1, nproductos[j]);
        sem_post(&s_t2[j]);

        val=0;
        sem_wait(&s2_global);
            while (val==0)  
            {
                if (j == aux->n_cri) j=0;
                sem_getvalue(&s2_t[j], &val);
                j++;
                //printf ("%d - %d\n",j%aux->n_cri, val);
            }
            sem_wait(&s2_t[j]);
        sem_post(&s2_global);


        nproductos[j] = aux->val;
        printf ("%d.- Produciendo %c\n",i+1, nproductos[j%aux->n_cri]);
        sem_post(&s_t2[j%aux->n_cri]);
    }
    return 0;
}
void* consumidor(void* arg){
    printf ("+Hilo Consumidor+\n");
    parametros2* aux;
    aux = (parametros2*)arg;
    int val, j=0;
    for (int i = 0; i < aux->n_i; i++)
    {
        val=0;
        sem_wait(&s_global2);
        while (val==0)
        {
            j++;
            sem_getvalue(&s_t2[j%(aux->n_cri)], &val);
        }
        sem_wait(&s_t2[j%(aux->n_cri)]);
        sem_post(&s_global2);

        printf ("-%d.-Consumiendo %c\n",i+1, nproductos[j%(aux->n_cri)]); 
        sem_post(&s_t[j%(aux->n_cri)]);
    }
    return 0;

}
//No iniciar el semaforo dentro de algún hilos porque solo sera accesible para este hilo
void iniciar_compro_sem(int n_cri)
{   
    s_t = (sem_t *)malloc(sizeof(sem_t)*n_cri);
    s_t2 = (sem_t *)malloc(sizeof(sem_t)*n_cri);
    s2_t = (sem_t *)malloc(sizeof(sem_t)*n_cri);
    s2_t2 = (sem_t *)malloc(sizeof(sem_t)*n_cri);
    nproductos = (int*)malloc(sizeof(int)*n_cri);
    nproductos2 = (int*)malloc(sizeof(int)*n_cri);
    

    for (int i = 0; i < n_cri; i++)
    {
        if (sem_init(&s_t[i], 0, 1 ) < 0 )
        {
            printf ("Error al crear el semáforo 1\n");
            exit(-1);
        }
    }
    
    for (int i = 0; i < n_cri; i++)
    {
        if (sem_init(&s_t2[i], 0, 0 ) < 0 )
        {
            printf ("Error al crear el semáforo 2\n");
            exit(-1);
        }
    }
    for (int i = 0; i < n_cri; i++)
    {
        if (sem_init(&s2_t[i], 0, 1 ) < 0 )
        {
            printf ("Error al crear el semáforo 1\n");
            exit(-1);
        }
    }
    
    for (int i = 0; i < n_cri; i++)
    {
        if (sem_init(&s2_t2[i], 0, 0 ) < 0 )
        {
            printf ("Error al crear el semáforo 2\n");
            exit(-1);
        }
    }
     if (sem_init(&s_global, 0, 1 ) < 0 )
        {
            printf ("Error al crear el semáforo Global\n");
            exit(-1);
        }

    if (sem_init(&s_global2, 0, 1 ) < 0 )
    {
        printf ("Error al crear el semáforo Global\n");
        exit(-1);
    }
     if (sem_init(&s2_global, 0, 1 ) < 0 )
        {
            printf ("Error al crear el semáforo Global\n");
            exit(-1);
        }

    if (sem_init(&s2_global2, 0, 1 ) < 0 )
    {
        printf ("Error al crear el semáforo Global\n");
        exit(-1);
    }
}