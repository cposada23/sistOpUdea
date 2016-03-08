#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR 15

void ingresarpacientes(char (*nombres)[MAX_CHAR], int *edades,  float *alturas, int numeropacientes);
void mostrarpacientes(char (*nombres)[MAX_CHAR], int *edades, float *alturas, int numeropacientes);

int main(int argc, char *argv[]){
    
    int *edades;
    float *alturas;
    char (*nombres)[MAX_CHAR];
    int numeropacientes= 0;
    
    if (argc<=1){
        printf("Se esperaba el numero de pacientes %s <numeropacientes>\n", argv[0]);
        exit(0);
    }else{
        numeropacientes= atoi(argv[1]);
        printf("numero de pacientes: %d\n", numeropacientes);
    }
    
    edades =(int (*))malloc(sizeof(int)*numeropacientes);
    alturas = (float (*))malloc(sizeof(float)*numeropacientes);
    nombres = (char (*)[MAX_CHAR])malloc(sizeof(char[MAX_CHAR])*numeropacientes);
    
    ingresarpacientes(nombres,edades, alturas, numeropacientes);
    mostrarpacientes(nombres, edades, alturas, numeropacientes);
    
    printf("\n\n Saliendo--- \n\n");
    return 0;
}

void ingresarpacientes(char (*nombres)[MAX_CHAR], int *edades,  float *alturas, int numeropacientes){
    int i;
    
    for (i = 0; i < numeropacientes; i++) {
        printf("\nIngrese el nombre del paciente #%d", i+1);
        setbuf(stdin,NULL);
        scanf("%s", (char *)(nombres + i));
        
        printf("\nIngrese la edad del paciente #%d", i+1);
        setbuf(stdin,NULL);
        scanf("%d", edades+i);
        
        printf("\nIngrese la altura del paciente #%d", i+1);
        setbuf(stdin,NULL);
        scanf("%f", alturas+i);
        
        
    }
}

void mostrarpacientes(char (*nombres)[MAX_CHAR], int *edades, float *alturas, int numeropacientes){
    int i;
    printf("\n __________________________________________ \n");
    printf("|%20s|%10s|%10s|\n", "Nombre","Edad","Altura");
    printf(" ------------------------------------------ \n");
    for ( i = 0; i < numeropacientes; i++) {
        printf("|%-20s|%-10d|%-10.3f|\n", *(nombres+i),*(edades+i), *(alturas+i));
    }
    printf(" ------------------------------------------\n");
}