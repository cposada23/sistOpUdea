#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>
#include <pthread.h>


#define MAX_CHARS_LINE 500


typedef struct{
    int * nums;
    int n;
}parametrosHilos;

int getNumNumeros(FILE *f);
void mostrarNumeros(int cantidadNumeros);
void registrarNumeros( FILE *f, int numNumeros);

void *esPerfecto(void * params);

int *nums;

int main(int argc, char *argv[]) {
    
    int numNumeros;
    FILE * file;
    char *fileName;
    pthread_t idHilos[30];
    int i;
    int *numerosPerfectos[30];
    
    parametrosHilos params[30]
    

    fileName = argv[1];
    numerosFile = fopen(fileName, "r");
    if(fileName==NULL){
        printf("No se pudo leer el archivo\n");
    }
    numNumeros = getNumNumeros(file);
    nums = (int *) malloc(sizeof(int)*numNumeros);
    registrarNumeros(file,numNumeros);
    for (i = 0; i < numNumeros; i++){
        params[i].n = *(nums + i);
        pthread_create(&idHilos[i],NULL, esPerfecto, (void *)(nums+i));
    }
    for(i = 0; i<numNumeros; i++){
        pthread_join(idHilos[i], (void **)&numerosPerfectos[i]);
        if(*numerosPerfectos[i] >0 ){
        	printf("El numero %d es perfecto\n", *numerosPerfectos[i]);
        }
    }
    return 0;
}


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
