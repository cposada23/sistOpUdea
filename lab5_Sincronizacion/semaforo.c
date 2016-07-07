#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define NUMTHREADS 200
#define MAXCNT  1000
// gcc -Wall eval4_posadacamilo.c -o eval4 -lpthread
double counter = 0;

sem_t sem;


void* counting(void *p);

int main (void){
    pthread_t tid[NUMTHREADS];
    int i = 0;
    
    /* Inicio el semaforo */
    sem_init(&sem,0,1);
    for(i = 0; i<NUMTHREADS; i++){
        pthread_create(&tid[i], NULL, &counting, NULL);
    }
    
    for(i = 0; i<NUMTHREADS ;i++){
        pthread_join(tid[i], NULL);
    }
    
    /* Destruyo el semaforo */
    sem_destroy(&sem);
    
    printf("\nEl valor del contador deberia ser: %d\n", MAXCNT*NUMTHREADS);
    printf("\nEl valor que contiene es: %.0f\n", counter);
    return 0;
}


void* counting(void *p){
    int i = 0;
    sem_wait(&sem);
    for(i = 0; i<MAXCNT; i++){
        counter++;
    }
    sem_post(&sem);
    return NULL;
}