/*
 * Name         : eval2_camiloposada
 * Author       : Camilo Posada Angel
 * Description  : Evaluacion 2. Estructuras
 * Compilation  : gcc -Wall eval2_posadacamilo.c -o eval
 * Execution    : ./eval mascotas.csv perros.csv gatos.csv
*/

/* Including headers or libraries. */
#include <stdio.h>      // printf, scanf, setbuf, fflush
#include <stdlib.h>     // malloc
#include <string.h>

/* Definition of macros and constants. */
#define MAX_CHARS_NAME 50
#define MAX_CHARS_LINE 17

/* Definition of structures. */
typedef struct {
    char especie;
    char nombre[MAX_CHARS_NAME];
    char sexo;
    int edad;
    
} mascota;

/* Declaration of functions (prototypes). */
void getOption(char *_option);
int getNumMascotas(FILE *f);
void registrarMascotas(mascota *masc, FILE *f, int numMascotas);
void mostrarMascotas(mascota *mascota, int numMascotas);
void separarPorEspecies(mascota *mascota, FILE *perros, FILE *gatos, int numMascotas);
void mostrarInfoGrupos(mascota *mascota, int numMascotas);

/* Main function. */
int main(int argc, char *argv[]) {

    /* Local variables. */
    int numMascotas;
    char option = 'x';
    char *fileName, *fileNamePerros, *fileNameGatos;
    FILE *mascotasFile;
    FILE *perrosFile;
    FILE *gatosFile;
    mascota *mascotas;
    int exitValue;
    int mascotasRegistradas= 0;

    // Validation: Number of arguments from console.
    if (argc != 4) {
        printf("Error: Numero de parametros invalido.\nDebe iniciar asi: %s <archivo.csv> <archivosalidaperros> <archivosalidagatos>\n", argv[0]);
		exit(0);
    }
    
    fileName = argv[1];
    printf("file name %s", fileName);
    mascotasFile = fopen(fileName, "r");
    if(mascotasFile == NULL) {
        printf("No se pudo abrir el archivo\n");
        exit(0);
    }
    fileNamePerros = argv[2];
   
    
    numMascotas = getNumMascotas(mascotasFile);
    
    if (numMascotas <= 0) {
        printf("Error: No hay mascotas registradas en el archivo\n");
		exit(0);
    }
    
    printf("Hay %d Mascotas registradas  en el archivo\n", numMascotas);
    
    mascotas = (mascota *)malloc(sizeof(mascota) * numMascotas);

    do {
        getOption(&option);
        switch (option) {
            case 'a':
                printf("registrando mascotas....");
                registrarMascotas(mascotas, mascotasFile, numMascotas);
                printf(" Mascotas registradas  \n\n");
                mascotasRegistradas = 1;
                break;
            case 'b':
                printf("Mascotas registradas \n");
                if(mascotasRegistradas!=0){
                    mostrarMascotas(mascotas, numMascotas); 
                }else{
                    printf("no hay mascotas registradas, primero hacer el paso a)\n\n");
                }
                
				
                break;
            case 'c':
				printf("separando por especie  \n");
                if(mascotasRegistradas!=0){
                    perrosFile = fopen(fileNamePerros, "w+");
                    if(perrosFile == NULL) {
                        printf("No se pudo abrir el archivo\n");
                        exit(0);
                    }
                    fileNameGatos = argv[3];
                    gatosFile = fopen(fileNameGatos, "w+");
                    if(gatosFile == NULL) {
                        printf("No se pudo abrir el archivo\n");
                        exit(0);
                    }
                    separarPorEspecies(mascotas, perrosFile, gatosFile, numMascotas);
                    fclose(perrosFile);
                    fclose(gatosFile);
                }else{
                    printf("no hay mascotas registradas, primero hacer el paso a)\n\n");
                }
                	
                break;
            case 'd':
                printf("mostrando info de grupos\n");
                
                if(mascotasRegistradas!=0){
                    mostrarInfoGrupos(mascotas,numMascotas);
                }else{
                    printf("no hay mascotas registradas, primero hacer el paso a)\n\n");
                }
                break;
            case 'q':
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("La opcion '%c' no es valida. Volviendo al menu.\n", option);
                break;
        }
    } while(option != 'q');
    
    exitValue = fclose(mascotasFile);
    if(exitValue == 0) {
        printf("se cerro el archivo\n");
    }
    
    /* Free memory. */
    free(mascotas);


    return 0;
}

/* Implementation of functions. */

int getNumMascotas(FILE *f) {
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
}

/* Punto 1*/
void registrarMascotas(mascota *masc, FILE *f, int numMascotas) {
    
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
    
}
/*punto extra*/
void mostrarMascotas(mascota *mascota, int numMascotas) {
    int i = 0;
	printf("\nLa lista de mascotas es:\n");	
    printf("|%-12s|%-12s|%-12s|%-12s|\n", "Especie", "Nombre", "Sexo", "Edad");
    for (i = 0; i < numMascotas; i++) {
        printf("|%-12c|%-12s|%-12c|%-12d|\n", mascota->especie, mascota->nombre, mascota->sexo,mascota->edad);
        mascota++;
    }
}

/*punto 2*/
void separarPorEspecies(mascota *mascota, FILE *perros, FILE *gatos, int numMascotas){
    
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

/* punto 3*/
void mostrarInfoGrupos(mascota *mascota, int numMascotas){
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
}