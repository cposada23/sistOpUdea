#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define max 3

void generarArreglo(int *numeros, int size);
void mostrarArreglo(int numeros[max], int size);

int main (){
    int numeros[max];
    
    generarArreglo(numeros, max);
    mostrarArreglo(numeros, max);
    
    
    return 0;
    
}
void mostrarArreglo(int numeros[max], int size){
    int i;
    for (i = 0; i < size; i++) {
        printf("Numero #%d: %d\n", i+1, numeros[i]);
    }
}
void generarArreglo(int *numeros, int size){
    
    int i; 
    int random; 
    srand(time(NULL));
    for ( i = 0; i < size; i++) {
        random = rand()%100;
        *(numeros+i) = random;
    }
}