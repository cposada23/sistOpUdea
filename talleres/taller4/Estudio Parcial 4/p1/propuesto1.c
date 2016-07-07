/*
 * Name         : Ejercicio propuesto 1 hilos 
 * Author       : Camilo Posada Angel
 * Description  : Ejercicio propuesto del laboratorio de hilos 
 * Compilation  : gcc -Wall propuesto1.c -o propuesto1 -lpthread
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
    
}params;



/* Declaration of functions (prototypes). */
int getNumNumeros(FILE *f);
void mostrarNumeros(int  *n,int cantidadNumeros);
void registrarNumeros(int *n, FILE *f, int numNumeros);
int sumarNormal(int *n, int numNumeros);

int *nums;

/* Main function. */
int main(int argc, char *argv[]) {
    
    
    int numNumeros;
    FILE *numerosFile;
    char *nameNumerosFile;
    int *numeros;
    int exitValue;
    int sumaN;
    clock_t start, end;
    int limiteI,limiteS;
    
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
    numeros =(int *) malloc(sizeof(int)*numNumeros);
    nums=(int *) malloc(sizeof(int)*numNumeros);
    registrarNumeros(numeros,numerosFile,numNumeros);
    mostrarNumeros(numeros,numNumeros);
    start = clock();
    sumaN = sumarNormal(numeros, numNumeros);
    end = clock();
    
    printf("Suma Normal: %d\nTiempo transcurrido: %.2f Milisegundos\n", sumaN, (double)(end - start));
    
    /* Cerrar el archivo */
    exitValue = fclose(numerosFile);
    if(exitValue == 0) {
        printf("se cerro el archivo\n");
    }
    
    /* Liberar memoria */
    free(numeros);
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


void mostrarNumeros(int  *n, int cantidadNumeros){
    int i;
    for(i=0;i<cantidadNumeros;i++){
        printf("N%d: %d ",i,*(n+i));
        printf("Nums %d: %d",i,*(nums+i));
    }
}


void registrarNumeros(int *n, FILE *f, int numNumeros){
    int i;
    for(i=0;i<numNumeros;i++){
        fscanf(f, "%d", n);
    	//printf("%d\n", *n);
	    n++;
    }
    rewind(f);
    for(i=0;i<numNumeros;i++){
        fscanf(f, "%d", (nums+i));
    	//printf("%d\n", *n);
	    
    }
    rewind(f);
}


int sumarNormal(int *n, int numNumeros){
    
    int i, suma = 0;
    
    for(i = 0; i<numNumeros; i++){
        suma += *n;
        n++;
    }
    return suma;
}
