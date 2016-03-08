#include<stdio.h>
#include <stdlib.h>

#define NC 10

void llenarDatos(char (*materias)[NC],int cantMaterias, float *notas);
void mostrarDatos(char(*materias)[NC],int cantMaterias, float *notas);
float promedioPonderado(int cantMaterias, float *notas);
int main(int argc, char *argv[]){
    
    char (*materias)[NC];
    float *notas;
    int cantidadMaterias;
    cantidadMaterias = atoi(argv[1]);
    
    materias = (char (*)[NC])malloc(sizeof(char[NC])*cantidadMaterias);
    notas = malloc(sizeof(float) * cantidadMaterias);
    
    //char materias [3][10];
    
    llenarDatos(materias,cantidadMaterias,notas);
    mostrarDatos(materias,cantidadMaterias,notas);
    return 0;
    
}
void llenarDatos(char (*materias)[NC], int cantMaterias, float *notas){
    
    int i;
    for(i = 0; i<cantMaterias; i++ ){
        printf("\nIngrese el nombre de la materia #%d: ", i);
        scanf("%s", materias+i);
        printf("\nIngrese la nota de la materia #%d: ", i);
        scanf("%f", (notas +i));
    }
    
}

void mostrarDatos(char(*materias)[NC],int cantMaterias, float *notas){
    
    int i;
    float promedio;
    printf(" _______________________\n");
    printf("|%-10s | %-10s|\n", "Materia", "Nota");
    printf(" -----------------------\n");
    for(i=0; i<cantMaterias;i++){
        printf("|%-10s | %-10.1f|\n",(char *)(materias + i), *(notas+i));
    }
    printf(" -----------------------\n");
    promedio = promedioPonderado(cantMaterias,notas);
    printf("|Promedio ponderado: %.3f\n", promedio);
    
}

float promedioPonderado(int cantMaterias, float *notas){
    int i;
    float promedio = 0;
    for(i = 0; i<cantMaterias; i++ ){
        promedio = promedio + *(notas+i);
    }
    promedio = promedio/cantMaterias;
    return promedio;
}
