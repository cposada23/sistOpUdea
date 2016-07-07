#include <stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
// gcc -Wall ejemplo3.c -o ejemplo3 -lpthread
int x = 0;

void ft(){
    
    int i;
    printf("Identificador del hilo: %d. \tx: %d\n", (int)getpid(),x);
    for(i=1;i<=1000;i++) x++;
}

int main(){
    pthread_t hilos[4];
    int i;
    for ( i = 0; i < 4; i++) {
        pthread_create(&hilos[i],NULL, (void *)ft, NULL);
    }
    for(i = 0; i < 4; i++){
        pthread_join(hilos[i], NULL);
    }
    
    printf("\n\n X: %d", x);
    return 0;
}