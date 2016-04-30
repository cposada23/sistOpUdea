#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//  gcc -o threads 1_threads.c -lpthread
typedef struct{
    
    int k;
    int n;
}str_params;

void *sumkn(void *param){
    
    str_params str_p = *((str_params *)param);
    int *result = (int *)malloc(sizeof(int));
    int x;
    x = (str_p.n - 1)/str_p.k;
    *result = (str_p.k)*x*(x+1)/2; 
    
    
    pthread_exit((void *)result);
    
}

int main(int argc, char *argv[]){
    
    int num[3]; // 3, 5 y 15
    int lim; // 10 
    int i;
    pthread_t id[3];
    str_params param[3];
    int *results[3];
    int resultado = 0;
     // validar en el nuimero de argv
    
    num[0] = atoi(argv[1]);
    num[1] = atoi(argv[2]);
    num[2] = num[0]*num[1];
    lim = atoi(argv[3]);
    
    
    //crear los hilos 
    for(i=0; i<3;i++){
        param[i].k = num[i];
        param[i].n = lim;
        pthread_create(&id[i], NULL, sumkn, (void *)&param[i]);    
    }
    
    
    for(i=0; i<3;i++){
        pthread_join(id[i], (void **)&results[i]);
        printf("Result parcial: %d\n", *results[i]);
    }
    
    resultado = *results[0] + *results[1] - *results[2];
    printf("Resultado: %d\n", resultado);
    
    
    return 0;
}