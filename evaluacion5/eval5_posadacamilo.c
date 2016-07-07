/*
================================================================================
Name         : eval5_camiloposada.c
Author       : Camilo Posada Angel
Compilation  : gcc -Wall eval5_posadacamilo.c -o eval5 -lpthread -lm -lrt
Execution    : ./eval5
================================================================================
*/

/* Incluyendo cabeceras o bibliotecas */
#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait()..   */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <pthread.h>        
#include <math.h>          
#include <string.h>         
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
/* Declaracion de funciones */
void verificarArgumentos(int numeroArgumentos, char**argumentos);
int sumaDivisores(int numero);

/* Main */
int main(int argc, char *argv[]) {

    sem_t *sem1;
    sem_t *sem2;
    pid_t pid_hijo;
    //pid_t pid;
    int num1, num2, suma1, suma2;
    int i;
    //MEMORIA COMPARTIDA
    int descriptorMC;
    void *direccionMC;
    const char *nombreMC = "NumerosAmigos";
    //----
    
   
    // Se validan los datos
    verificarArgumentos(argc, argv);
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);

    // COMUNICACION Y SINCRONIZACION
    // -------------------------------------------------------------------------
    
    //Creo memoria compartida
    descriptorMC = shm_open(nombreMC, O_CREAT|O_RDWR,0666);
    ftruncate(descriptorMC, sizeof(int)*2);
    
    //Mapear este segemto esta disponible para el proceso
    direccionMC = mmap(0, sizeof(int)*2,PROT_READ|PROT_WRITE, MAP_SHARED, descriptorMC, 0);
    if(direccionMC == MAP_FAILED){
        printf("error");
        return(-1);
    }
    
    sem1 = mmap(0,sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1,0);
    sem2 = mmap(0,sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1,0);
    
    
    if(sem_init(sem1, 1, 0)){
        printf("Error iniciando el primer semaforo\n");
        exit(1);
    }
    sem_init(sem2, 1, 0);
    
    for (i=0;i<3; i++){
        pid_hijo = fork();
        //Proceso hijo
        if(pid_hijo==0){
            switch(i){
                case 0:
                    printf("\n\nSe creo el proceso 1, número a evaluar %d\n", num1);
                    suma1 = sumaDivisores(num1);
                    printf("suma num1 = %d\n", suma1);
                    //direccionMC = suma1;
                    sprintf(direccionMC, "%d\n", suma1); // Escribo en memoria compartida
                    sem_post(sem1);
                    printf("Termino el proceso 1\n");
                    break; 
                case 1:
                    printf("\nSe creo el proceso 2, número a evaluar %d\n", num2);
                    suma2 = sumaDivisores(num2);
                    printf("suma num2 %d\n", suma2);
                    direccionMC+=sizeof(int)+10;
                    sprintf(direccionMC, "%d\n", suma2);
                    sem_wait(sem1);
                    sem_post(sem2);
                    //sem_post(sem1);
                    printf("Termino el proceso 2\n");
                    break;
                case 2:   
                    printf("Espero");
                    printf("\nSe creo el proceso 3 \n"); 
                    sem_wait(sem2);
                    
                    
                    //Leer la memoria compartida
                    suma1 = atoi(direccionMC);
                    direccionMC+=sizeof(int)+10;
                    suma2 = atoi(direccionMC);
                    printf("###################################################\n");
                    if(suma1 == num2 && suma2 == num1){
                        printf("Los números %d y %d son números amigos\n", num1, num2);
                    }else{
                        printf("Los números %d y %d no son números amigos\n", num1, num2);
                    }

                    printf("###################################################\n");
                    printf("Termino el proceso 3\n"); 
                    break;
            }
            exit(0);
        }
    }

    for(i = 0; i<3; i++){
        wait(NULL);
        //pid = wait(NULL);
        //printf("El proceso hijo con PID %d ha terminado\n", (int)pid);
    }
    printf("Proceso padre: Todos mis hijos terminaron\n");

    //Destruyo el segmento de memoria compartida
    if(shm_unlink(nombreMC)==-1){
        printf("error eliminando el segmento de momoria compartida");
    }
    
    //Destruyo los semaforos
    sem_destroy(sem1);
    sem_destroy(sem2);
    // -------------------------------------------------------------------------
    // Finaliza el programa
    printf("Finaliza el programa %s...\n", argv[0]);
    return 0;
}

/* Implementacion de funciones */

// Verifica si los argumentos por consola son los esperados por el programa
void verificarArgumentos(int numeroArgumentos, char **argumentos){
	if(numeroArgumentos != 3) { // Falla la validación
		printf("Error: Número de argumentos no valido\n");
        printf("Se esperaba la siguiente entrada:\n");
    	printf(" %s <numero1> <numero2> \n", argumentos[0]);
		exit(1);
	}
    // Confirmacion: Se pasa la validación
    printf("Se han validado los datos ingresados\n");
    printf("---- Nombre del programa: %s\n", argumentos[0]);
    printf("---- Número 1 %s\n", argumentos[1]);
    printf("---- Número 2 %s\n", argumentos[2]);
}

/*Calcular la suma de los divisores propios*/
int sumaDivisores(int numero){
    int i, suma = 0;
    for(i = 1; i<=numero/2;i++){
        if (numero%i==0){
            suma+=i;
        }
    }
    return suma;
    
}







