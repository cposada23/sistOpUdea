#include<stdio.h>
#include<pthread.h>
#define NUMTHREADS 200
#define MAXCNT  1000
// gcc -Wall eval4_posadacamilo.c -o eval4 -lpthread
double counter = 0;
pthread_mutex_t lock;
void* counting(void *p);

int main (void){
    pthread_t tid[NUMTHREADS];
    int i = 0;
    
    
    /*"Inicio el mutex */
    if(pthread_mutex_init(&lock,NULL) != 0){
        printf("inicio de mutex fallo\n");
        return 1;
    }
    
    
    for(i = 0; i<NUMTHREADS; i++){
        pthread_create(&tid[i], NULL, &counting, NULL);
    }
    
    for(i = 0; i<NUMTHREADS ;i++){
        pthread_join(tid[i], NULL);
    }
    
    
    /*Destruir el mutex*/
    pthread_mutex_destroy(&lock);
    
    
    printf("\nEl valor del contador deberia ser: %d\n", MAXCNT*NUMTHREADS);
    printf("\nEl valor que contiene es: %.0f\n", counter);
    return 0;
}


void* counting(void *p){
    int i = 0;
    
    pthread_mutex_lock(&lock);
    
    for(i = 0; i<MAXCNT; i++){
        counter++;
    }
    
    pthread_mutex_unlock(&lock);
    return NULL;
}