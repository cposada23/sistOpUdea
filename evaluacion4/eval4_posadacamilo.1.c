/*
 * Name         : Evaluacio 4 hilos 
 * Author       : Camilo Posada Angel
 * Description  : Evaluacion 4 
 * Compilation  :
 * Execution    : ./eval4 numeros.csv
*/

/* Including headers or libraries. */
#include <stdio.h>      // printf, scanf, setbuf, fflush
#include <stdlib.h>     // malloc
#include <string.h>
#include <pthread.h>
#include <time.h>  

/* Definition of macros and constants. */
#define MAX_CHARS_NAME 50
#define MAX_NUM_HILOS 30
#define MAX_CHARS_LINE 500





/* Declaracion de funciones */
int getNumNumeros(FILE *f);
void mostrarNumeros(int cantidadNumeros);
void registrarNumeros( FILE *f, int numNumeros);

/*"Funcion para los hilos*/
void *esPerfecto(void * params);

/* Para guardar todos los numeros del archivo */
int *nums;


int main(int argc, char *argv[]) {
    
    
    int numNumeros;
    FILE *numerosFile;
    char *nameNumerosFile;
    int exitValue;
    pthread_t idHilos[MAX_NUM_HILOS];
    int i;
    int *numerosPerfectos[MAX_NUM_HILOS];
    int cantidadPerfectos = 0;
    
    /* Validacion del numero de argumentos de la consola */
    if(argc != 2){
        printf("Error: Numero de parametros invalido.\n Se debe ejecutar el programa de la siguiente manera: %s <archivoVectorNumeros.csv> \n", argv[0]);
        exit(0);        
    }
    
    /* Lectura del archivo con los numeros */
    nameNumerosFile = argv[1];
    numerosFile = fopen(nameNumerosFile, "r");
    if(numerosFile==NULL){
        printf("No se pudo leer el archivo\n");
    }
    numNumeros = getNumNumeros(numerosFile);
    printf("Número de números en el archivo: %d\n", numNumeros);
    /*Memoria dinamica */
    nums = (int *) malloc(sizeof(int)*numNumeros);
    registrarNumeros(numerosFile,numNumeros);
    
    // Creacion de hilos
    for (i = 0; i < numNumeros; i++){
        pthread_create(&idHilos[i],NULL, esPerfecto, (void *)(nums+i));
    }
    
    //Esperar los hilos
    for(i = 0; i<numNumeros; i++){
        pthread_join(idHilos[i], (void **)&numerosPerfectos[i]);
        if(*numerosPerfectos[i] >0 ){
        	printf("El numero %d es perfecto\n", *numerosPerfectos[i]);
        	cantidadPerfectos++;
        }
    }

    if (cantidadPerfectos > 0){
    	printf("Porcentaje de numeros perfectos en el archivo: %.1f %%\n",(((float)cantidadPerfectos/(float)numNumeros)*100));
    }else{
    	printf("Porcentaje de numeros perfectos en el archivo: 0 %%\n");
    }


    exitValue = fclose(numerosFile);
    if(exitValue == 0) {
        printf("se cerro el archivo\n");
    }
    
    /* Liberar memoria */
    free(nums);
    return 0;
}

/* Implementation of functions. */


int getNumNumeros(FILE *f){
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    char *token;
    fgets(buffer,MAX_CHARS_LINE,f);
    fgets(buffer,MAX_CHARS_LINE,f);
    token = strtok(buffer, ";");
    while(token!=NULL) {
        num++;
        token = strtok(NULL, ";");
    }
    rewind(f);
    return num;
}


void mostrarNumeros( int cantidadNumeros){
    int i;
    for(i=0;i<cantidadNumeros;i++){
        printf("Nums %d: %d",i,*(nums+i));
    }
}


void registrarNumeros( FILE *f, int numNumeros){
    int i = 0;
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    char *token;
    fgets(buffer,MAX_CHARS_LINE,f);
    fgets(buffer,MAX_CHARS_LINE,f);
    token = strtok(buffer, ";");
    while(token!=NULL) {
        num++;
        *(nums + i) = atoi(token);
        token = strtok(NULL, ";");
        i++;
    }
    rewind(f);
}

/*Punto 1*/
void *esPerfecto(void * params){
    int i, suma = 0;
    int nu = *((int *)params);
    //printf("El num es: %d\n", nu);
    int *numero = (int *)malloc(sizeof(int));
    for(i = 1; i<=nu/2;i++){
        if (nu%i==0){
            suma+=i;
        }
    }
    if(suma == nu){
    	*numero = nu;
    }else{
    	*numero = 0;	
    }
    pthread_exit((void *)numero);
}
