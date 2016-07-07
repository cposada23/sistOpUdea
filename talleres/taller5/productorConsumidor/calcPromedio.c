/*
================================================================================
Name         : TallerSincronizacion.c
Author       : Juan Guillermo Restrepo Pineda
Version      : 1.0
Compilation  : gcc -Wall calcPromedio.c -o promedio -lpthread -lm -lrt
Execution    : ./sincro.out notas.csv
================================================================================
*/

/* Incluyendo cabeceras o bibliotecas */
#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait()..   */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <pthread.h>        /* sem_init(), sem_post(), sem_wait(), sem_destroy() */
#include <math.h>           /* powf(), sqrtf()          */
#include <string.h>         /* strtok()                 */
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>

/* Declaracion de funciones */
void verificarArgumentos(int numeroArgumentos, char**argumentos);
FILE* abrirArchivo(char* nombreDeArchivo);
int obtenerNumeroDeNotas(FILE* archivo);
void obtenerNotas(FILE* archivo, int numeroNotas, float* listaNotas);
void imprimirNotas(float* listaNotas, int numeroNotas);
float calcularPromedio(int numeroNotas, float* listaNotas);
void cerrarArchivo(FILE* archivo);

/* Main */
int main(int argc, char *argv[]) {

    FILE* archivo;
    int numeroNotas;
    //int i;
    float* listaNotas;
    //sem_t *sem1;
    //sem_t *sem2;
    //pid_t pid1, pid2;
    //MEMORIA COMPARTIDA
    int descriptorMC;
    void *direccionMC;
    const char *nombreMC = "prom";
    //----
    float promedio;
    sem_t *semaforo;
    semaforo = sem_open("/Hola", O_CREAT, 0644, 0);
    //float desviacion;

    // Se validan los datos
    verificarArgumentos(argc, argv);

    // Se abre el archivo
    archivo = abrirArchivo(argv[1]);
    printf("Se abre el archivo %s exitosamente\n", argv[1]);

    // Se lee el archivo obteniendo las notas
    numeroNotas = obtenerNumeroDeNotas(archivo);
    listaNotas = (float *) malloc (sizeof(float) * numeroNotas);
    obtenerNotas(archivo, numeroNotas, listaNotas);
    printf("Se obtiene un total de %d notas desde archivo\n", numeroNotas);
    //imprimirNotas(listaNotas, numeroNotas);

    // COMUNICACION Y SINCRONIZACION
    // -------------------------------------------------------------------------
    //Creo memoria compartida
    descriptorMC = shm_open(nombreMC, O_CREAT|O_RDWR,0666);
    ftruncate(descriptorMC, sizeof(float));
    
    //Mapear este segemto esta disponible para el proceso
    direccionMC = mmap(0, sizeof(float),PROT_READ|PROT_WRITE, MAP_SHARED, descriptorMC, 0);
    if(direccionMC == MAP_FAILED){
        printf("error");
        return(-1);
    }
    
    
    promedio = calcularPromedio(numeroNotas, listaNotas);
    sprintf(direccionMC, "%f\n", promedio);
    printf("El promedio es %f\n", promedio);
    
    /*for(i = 0; i<numeroNotas;i++){
        printf(" %f ",*(listaNotas+i));
        printf(direccionMC, " %f\n ",*(listaNotas+i));
        direccionMC++;
        //sprintf((direccionMC+i), " %f\n ",*(listaNotas+i));
    }*/
    /*sprintf(direccionMC, "%f\n", promedio); // Escribo en memoria compartida
    printf("promedio en la memoria compartida %f\n",atof(direccionMC));
    direccionMC++;
    sprintf(direccionMC,"%f\n",0.000075);
    direccionMC++;
    sprintf(direccionMC,"%f\n",promedio);*/
    /*direccionMC++;
    sprintf(direccionMC, "%f\n", 0.75);
    direccionMC++;
    sprintf(direccionMC, "%f\n", 0.75);
    */
    // -------------------------------------------------------------------------

    // Se libera la memoria dinamica
    free(listaNotas);
    printf("Se libera la memoria dinamica\n");

    // Se cierra el archivo
    cerrarArchivo(archivo);
    printf("Se cierra el archivo %s exitosamente\n", argv[1]);

    // Finaliza el programa
    printf("Finaliza el programa %s...\n", argv[0]);
    sem_post(semaforo);
    return 0;
}

/* Implementacion de funciones */

// Verifica si los argumentos por consola son los esperados por el programa
void verificarArgumentos(int numeroArgumentos, char **argumentos){
	if(numeroArgumentos != 2) { // Falla la validación
		printf("Error: Numero de argumentos no valido\n");
        printf("Se esperaba la siguiente entrada:\n");
    	printf(" %s notas.csv \n", argumentos[0]);
		exit(1);
	}
    // Confirmacion: Se pasa la validación
    printf("Se han validado los datos ingresados\n");
    printf("---- Nombre del programa: %s\n", argumentos[0]);
    printf("---- Nombre del archivo: %s\n", argumentos[1]);
}

// Abre el archivo de notas en modo sólo lectura
FILE* abrirArchivo(char* nombreDeArchivo){
	FILE* archivo = fopen(nombreDeArchivo,"r");
	if(archivo == NULL) { // Fallo al abrir el archivo
		printf("Error: No fue posible abrir el archivo %s", nombreDeArchivo);
		exit(1);
	}
	return archivo;
}

// Lee el archivo y obtiene el numero de notas
int obtenerNumeroDeNotas(FILE* archivo){
    char bufferLinea[256];
    char *token;
    int numeroNotas = 0;

    while (fgets (bufferLinea, sizeof(bufferLinea), archivo)) {
        token = strtok(bufferLinea, ";");
        while( token != NULL ) {
            numeroNotas++;
            token = strtok(NULL, ";");
        }
    }
    rewind(archivo);
    return numeroNotas;
}

// Lee el archivo y obtiene las notas
void obtenerNotas(FILE* archivo, int numeroNotas, float* listaNotas){
    char bufferLinea[256];
    char *token;

    while (fgets (bufferLinea, sizeof(bufferLinea), archivo)) {
        token = strtok(bufferLinea, ";");
        while( token != NULL ) {
            *listaNotas = atof(token);
            token = strtok(NULL, ";");
            listaNotas++;
        }
    }
    rewind(archivo);
}

// Verifica que las notas esten en memoria dinamica
void imprimirNotas(float* listaNotas, int numeroNotas) {
    int i = 0;
    printf("Listado de notas:\n");
    for (i = 0; i < numeroNotas; i++) {
        printf("---- Nota (%d): %.1f\n", i+1, *listaNotas);
        listaNotas++;
    }
}

// Calcula el promedio de notas
float calcularPromedio(int numeroNotas, float* listaNotas){
    float promedio = 0;
    float sumatoria = 0;
	int i;

	for(i=0; i<numeroNotas; i++){
		sumatoria += *listaNotas;
		listaNotas++;
	}
	promedio = sumatoria/numeroNotas;
	return promedio;
}

// Cierra el archivo de notas
void cerrarArchivo(FILE* archivo){
	int salida = fclose(archivo);
	if(salida!=0) { // Fallo al cerrar el archivo
		printf("Error: No fue posible cerrar el archivo");
	}
}
