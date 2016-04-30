/*
 * Name         : eval3_camiloposada
 * Author       : Camilo Posada Angel
 * Description  : Evaluacion 3. Procesos
 * Compilation  : gcc -Wall eval3_posadacamilo.c -o eval3
 * Execution    : ./eval3 complejos.csv
*/

/* Including headers or libraries. */
#include <stdio.h>      // printf, scanf, setbuf, fflush
#include <stdlib.h>     // malloc
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/* Definition of macros and constants. */
#define MAX_CHARS_NAME 50
#define MAX_CHARS_LINE 17

/* Definition of structures. */
typedef struct {
    int parte_Real;
    int parte_Imaginaria;
    
} complejo;

/* Declaration of functions (prototypes). */
void almacenarComplejos(complejo *complejos, FILE *f, int numComplejos);
int getNumComplejos(FILE *f);
void suma(complejo * complejos, int numComplejos);

void resta(complejo * complejos, int numComplejos);
void multiplicacion(complejo * complejos, int numComplejos);
void suma(complejo * complejos, int numComplejos);

/* Main function. */
int main(int argc, char *argv[]) {

    /* Local variables. */
   
    char *fileName;
    FILE *complejosFile;
    int numComplejos;
    complejo *complejos;
    int exitValue;
    int numProcesos = 3, i;
    pid_t pid_hijo,pid;
    

    // Validation: Number of arguments from console.
    if (argc != 2) {
        printf("Error: Numero de parametros invalido.\nDebe iniciar asi: %s <archivoNumeroComplejoss> \n", argv[0]);
		exit(0);
    }
    

    //Lectura y almacenamiento de datos
    fileName = argv[1];
    printf("file name %s", fileName);
    complejosFile = fopen(fileName, "r");
    if(complejosFile == NULL) {
        printf("No se pudo abrir el archivo\n");
        exit(0);
    }

    numComplejos = getNumComplejos(complejosFile);
    if (numComplejos <= 0) {
        printf("Error: No hay informacion registrada en el archivo\n");
        exit(0);
    }
    printf("hay %d numeros complejos en el archivo\n\n", numComplejos);
    complejos = (complejo *)malloc(sizeof(complejo)*numComplejos);
    almacenarComplejos(complejos,complejosFile, numComplejos);
    printf("todo Bien inicia el fork() \n\n");
    

    for (i=0;i<numProcesos; i++){
        pid_hijo = fork();
        //Proceso hijo
        if(pid_hijo==0){
            switch(i){
                case 0:
                    suma(complejos,numComplejos);
                    break; 
                case 1:
                    resta(complejos, numComplejos);
                    break;
                case 2:
                    multiplicacion(complejos, numComplejos);
                    break;
            }
            exit(0);
        }else{
            pid = wait(NULL);
            printf("El proceso hijo con PID %d ha terminado\n\n\n", (int)pid);
        }
        
    }
    

    exitValue = fclose(complejosFile);
    if(exitValue == 0){
        printf("Se cerro el archivo\n");
    }
    free(complejos);

    return 0;
}

/* Implementation of functions. */

/*Punto 1*/
int getNumComplejos(FILE *f) {
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num - 1;
}

void almacenarComplejos(complejo *complejos, FILE *f, int numComplejos) {
    
    int i = 0;
    char *token;
    char lines[MAX_CHARS_LINE];
    
    for (i = 0; i < numComplejos; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
        complejos-> parte_Real = atoi(token);
        token = strtok(NULL, ";");
        complejos-> parte_Imaginaria = atoi(token);
        complejos++;
    }
    
}

/*Punto 2 */

void suma(complejo * complejos, int numComplejos){
    int i = 0;
    int p_real;
    int p_imaginaria;
    printf("\nSoy un proceso hijo con PID %d, ejecutare la suma de complejos:",(int)getpid());
    printf("\nSUMA DE COMPLEJOS\n");
    for (i = 0; i < numComplejos/2; i++) {
        p_real = 0;
        p_imaginaria = 0;
        p_real += complejos->parte_Real;
        p_imaginaria += complejos->parte_Imaginaria;
        complejos++;
        p_real += complejos->parte_Real;
        p_imaginaria += complejos->parte_Imaginaria;
        printf("La suma de la pareja #%d es: %d + %di\n",i+1, p_real, p_imaginaria);
        complejos++;
    }
    printf("\n FIN SUMA COMPLEJOS \n");
}

void resta(complejo *complejos, int numComplejos){
    int i = 0;
    int p_real;
    int p_imaginaria;

    printf("Soy un proceso hijo con PID %d, ejecutare la resta de complejos:",(int)getpid());
    printf("\nRESTA DE COMPLEJOS\n");
    for (i = 0; i < numComplejos/2; i++) {
        
        
        p_real = complejos->parte_Real;
        p_imaginaria = complejos->parte_Imaginaria;
        complejos++;
        p_real -= complejos->parte_Real;
        p_imaginaria -= complejos->parte_Imaginaria;
        printf("La resta de la pareja #%d es: %d + %di\n", i+1,p_real, p_imaginaria);
        complejos++;
    }
    printf("\n FIN RESTA COMPLEJOS \n");
}

void multiplicacion(complejo *complejos, int numComplejos){
    int i = 0;
    int a,c ; //partes reales
    int b,d; //partes imaginarias
    int p_real;
    int p_imaginaria;
    printf("Soy un proceso hijo con PID %d, ejecutare la multiplicación de complejos:",(int)getpid());
    printf("\nMULTIPLICACION DE COMPLEJOS\n");
    for (i = 0; i < numComplejos/2; i++) {
        
        a = complejos->parte_Real;
        b = complejos->parte_Imaginaria;
        complejos++;
        c = complejos->parte_Real;
        d = complejos->parte_Imaginaria;
        p_real = a*c - b*d;
        p_imaginaria = a*d + b*c;
        printf("La multiplicacion de la pareja #%d es: %d + %di\n",i+1,p_real, p_imaginaria);
        complejos++;
    }
    printf("\n FIN MULTIPLICACION COMPLEJOS \n");
}


/*int getNumMascotas(FILE *f) {
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num - 1;
}

void getOption(char *_option) {
  printf("\nMENU DE OPCIONES\n");
  printf("\ta) Registrar mascotas (punto1)\n");
  printf("\tb) Mostrar registro de mascotas(punto extra) \n");
  printf("\tc) Separar por especie (punto2)\n");
  printf("\td) Mostrar info de grupos (punto3)\n");
  printf("\tq) Salir del programa\n");
  printf("Seleccione una opcion: ");
  setbuf(stdin, NULL);
  scanf("\n%c", _option);
}*/

/* Punto 1*/
/*void registrarMascotas(mascota *masc, FILE *f, int numMascotas) {
    
    int i = 0;
    char *token;
    char lines[MAX_CHARS_LINE];
    
    for (i = 0; i < numMascotas; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
        masc->especie = *token;
        //strcpy((char *)masc->especie, token);
        token = strtok(NULL, ";");
        strcpy((char *)masc->nombre, token);
        token = strtok(NULL, ";");
        masc->sexo = *token;
        token = strtok(NULL, ";");
        masc->edad = atoi(token);
        masc++;
    }
    
}*/
/*punto extra*/
/*void mostrarMascotas(mascota *mascota, int numMascotas) {
    int i = 0;
	printf("\nLa lista de mascotas es:\n");	
    printf("|%-12s|%-12s|%-12s|%-12s|\n", "Especie", "Nombre", "Sexo", "Edad");
    for (i = 0; i < numMascotas; i++) {
        printf("|%-12c|%-12s|%-12c|%-12d|\n", mascota->especie, mascota->nombre, mascota->sexo,mascota->edad);
        mascota++;
    }
}*/

/*punto 2*/
/*void separarPorEspecies(mascota *mascota, FILE *perros, FILE *gatos, int numMascotas){
    
    int i;
    fprintf(perros, "Perros\n");
    fprintf(gatos, "Gatos\n");
    fprintf(perros, "|%-12s|%-12s|%-12s|%-12s|\n", "Especie", "Nombre", "Sexo", "Edad");
    fprintf(gatos, "|%-12s|%-12s|%-12s|%-12s|\n", "Especie", "Nombre", "Sexo", "Edad");
    for (i = 0; i<numMascotas;i++){
        if (mascota->especie=='C'){
            fprintf(perros,"|%-12c|%-12s|%-12c|%-12d|\n", mascota->especie, mascota->nombre, mascota->sexo,mascota->edad);
        }else{
            fprintf(gatos,"|%-12c|%-12s|%-12c|%-12d|\n", mascota->especie, mascota->nombre, mascota->sexo,mascota->edad);
        }
        mascota++;
        
    }
    
}
*/
/* punto 3*/
/*void mostrarInfoGrupos(mascota *mascota, int numMascotas){
    int i;
    int gatos7meses=0, gatosEdadReproductiva=0,gatosmayoresde17=0;
    int perros10meses=0, perrosEdadReproductiva=0,perrosmayoresde10=0;
    for(i = 0; i<numMascotas; i++){  
        if(mascota->especie == 'C'){
            if(mascota->edad<10){
                perros10meses ++;
            }
            if(mascota->edad>=10 && mascota->edad<=120){
                perrosEdadReproductiva++;
            }if(mascota->edad>120){
                perrosmayoresde10++;
            }
            
        }else{
            if(mascota->edad<7){
                gatos7meses ++;
            }
            if(mascota->edad>=7 && mascota->edad<=204){
                gatosEdadReproductiva++;
            }if(mascota->edad>204){
                gatosmayoresde17++;
            }
        }
        mascota++;
    }
    printf("\n____________________________________\n");
    printf("|%-35s|\n","Gatos");
    printf("|%-24s|%-10d|\n", "Menores de 7 meses", gatos7meses);
    printf("|%-24s|%-10d|\n", "En edad reproductiva", gatosEdadReproductiva);
    printf("|%-25s|%-10d|\n", "Mayores de 17 años", gatosmayoresde17);
    printf("|-----------------------------------|\n");
    printf("|%-35s|\n", "perros");
    printf("|%-24s|%-10d|\n", "Menores de 10 meses", perros10meses);
    printf("|%-24s|%-10d|\n", "En edad reproductiva", perrosEdadReproductiva);
    printf("|%-25s|%-10d|\n", "Mayores de 10 años", perrosmayoresde10);
    printf("\n____________________________________\n");
}*/