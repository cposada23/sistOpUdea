#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

// gcc -Wall ejemplo2.c -o ejemplo2 -lpthread
//Estuctura para pasarle parametros a la funcion que ejecuta el hilo
/*struct parametros_hilo{
    char caracter;
    
    int contador;
    
};*/

typedef struct{
    
    char caracter;
    int contador;
    
}parametros_hilo;

void * imprimir_caracter(void * params){
    //Casting al ripo correcto 
    parametros_hilo p_hilo = *((parametros_hilo *)params);
    int i;
    for ( i = 0; i < p_hilo.contador; i++) {
        fputc( p_hilo.caracter, stderr);
    }
    
    return NULL;    
}

int main(){
    
    pthread_t id_hilo[2];
    parametros_hilo parametros[2];
    int i;
    printf("antes\n");
    for ( i = 0; i < 2; i++) {
        printf("Creando hilo %d\n", i);
        if (i == 0) {
            parametros[i].caracter = 'x';
            parametros[i].contador = 1000;
        }
        
        else{ 
            parametros[i].caracter = 'o';
            parametros[i].contador = 2000;
        }
        pthread_create(&id_hilo[i], NULL, &imprimir_caracter, &parametros[i]);
    }
    for(i=0; i<2;i++){
        pthread_join(id_hilo[i], NULL);
    }
    
    printf("terminado\n");
    
    return 0;
    
}