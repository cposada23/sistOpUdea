/*
 * Name         : Ejercicio propuesto 1 hilos 
 * Author       : Camilo Posada Angel
 * Description  : Ejercicio propuesto del laboratorio de hilos 
 * Compilation  : gcc -Wall propuesto1a.c -o propuesto1 -lpthread
 * Execution    : ./propuesto1 numeros.csv
*/

/* Including headers or libraries. */
#include <stdio.h>      // printf, scanf, setbuf, fflush
#include <stdlib.h>     // malloc
#include <string.h>
#include <pthread.h>
#include <time.h>  

/* Definition of macros and constants. */
#define MAX_CHARS_NAME 50
#define MAX_CHARS_LINE 17

typedef struct{
    
    int inicio;
    int fin;
    
}paramsHilos;



/* Declaration of functions (prototypes). */
int getNumNumeros(FILE *f);
void mostrarNumeros(int cantidadNumeros);
void registrarNumeros( FILE *f, int numNumeros);
int sumarNormal( int numNumeros);
void *sumarHilos(void * params);

int *nums;

/* Main function. */
int main(int argc, char *argv[]) {
    
    
    int numNumeros;
    FILE *numerosFile;
    char *nameNumerosFile;
    int exitValue;
    int sumaN;
    clock_t start, end;
    int limiteI,limiteS;
    pthread_t idHilos[2];
    int i;
    paramsHilos parametros[2];
    int *sumas[2];
    int sumaHilos = 0;
    
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
    limiteI = numNumeros/2;
    
    printf("Numero de numeros en el archivo: %d, limiteI: %d", numNumeros, limiteI);
    nums=(int *) malloc(sizeof(int)*numNumeros);
    registrarNumeros(numerosFile,numNumeros);
    //mostrarNumeros(numNumeros);
    start = clock();
    sumaN = sumarNormal( numNumeros);
    end = clock();
    
    printf("Suma Normal: %d\nTiempo transcurrido: %.2f Milisegundos\n", sumaN, (double)(end - start));
    
    
    //Preparar los parametros para los hilos
    for(i = 0; i < 2; i++){
        if (i == 0){
            parametros[i].inicio = 0;
            parametros[i].fin = numNumeros/2 + 1;
        }
        else{
            parametros[i].inicio = parametros[i-1].fin;
            parametros[i].fin = numNumeros;
        }
    }
    start = clock();
    for (i = 0; i < 2; i++){
        pthread_create(&idHilos[i],NULL, sumarHilos, (void *)&parametros[i]);
    }
    
    for(i = 0; i<2; i++){
        pthread_join(idHilos[i], (void **)&sumas[i]);
        sumaHilos += *sumas[i];
        printf("suma %d: %d", i, *sumas[i]);
        free(sumas[i]);
    }
    end =  clock();
    printf("La suma total es %d y tardo %f", sumaHilos, (double)(end-start));
    
    /* Cerrar el archivo */
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
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num - 1;
    
}


void mostrarNumeros( int cantidadNumeros){
    int i;
    for(i=0;i<cantidadNumeros;i++){
        printf("Nums %d: %d",i,*(nums+i));
    }
}


void registrarNumeros( FILE *f, int numNumeros){
    int i;
    
    for(i=0;i<numNumeros;i++){
        fscanf(f, "%d", (nums+i));
    	//printf("%d\n", *n);
	    
    }
    rewind(f);
}


int sumarNormal( int numNumeros){
    
    int i, suma = 0;
    
    for(i = 0; i<numNumeros; i++){
        suma += *(nums+i);
       
    }
    return suma;
}

void *sumarHilos(void * params){
    int i;
    int *suma = (int *)malloc(sizeof(int));
    paramsHilos parametro = *((paramsHilos *)params);
    printf("inicio %d, fin %d\n", parametro.inicio,parametro.fin);
    for(i = parametro.inicio; i<parametro.fin; i++){
        *suma += *(nums+i);
    }
    pthread_exit((void *)suma);
}
