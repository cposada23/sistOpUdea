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
#include <sys/wait.h>


//gcc -Wall principal.c  -o principal -lpthread -lm -lrt                         

void verificarArgumentos(int numeroArgumentos, char**argumentos);

int main(int argc, char *argv[]){
    
    pid_t pid1, pid2;
    //int i;
    //semaforo con nombre
    sem_t *semaforo, *semaforo2;
    int descriptorMC;
    void *direccionMC;
    const char *nombreMC = "prom";
    float promedio;
    
    semaforo = sem_open("/Hola", O_CREAT, 0644, 0);
    semaforo2 = sem_open("/Hola2", O_CREAT, 0644, 0);
    
   
    verificarArgumentos(argc, argv);
    
    
    
    pid1 = fork();
    if(pid1 <0){
        printf("Error: No se creo el primer proceso hijo\n");
        exit(-1);
    }else if(pid1 == 0 ){
        printf("Hola soy el proceso hijo y calculare el promedio de las notas");
        //execl("./test", "test",argv[1], NULL);
        execl("./promedio", "promedio",argv[1], NULL);
        exit(0);
    }else{
        
        pid2 = fork();
        if(pid2<0){
            printf("Error: No se creo el proceso 2\n");
        }else if(pid2 == 0){
            sem_wait(semaforo);
            printf("Hola soy el proceso 2 claculare la desviacion estandar\n");
            
            descriptorMC = shm_open(nombreMC, O_CREAT|O_RDWR,0666);
           
            
            //Mapear este segemto esta disponible para el proceso
            direccionMC = mmap(0, sizeof(float),PROT_READ|PROT_WRITE, MAP_SHARED, descriptorMC, 0);
            if(direccionMC == MAP_FAILED){
                printf("error");
                return(-1);
            }
            promedio = atof(direccionMC);
            printf("Promedio en el proceso 2 %f\n" , promedio);
            sem_post(semaforo2);
            exit(0);
        }
        
        else{
            printf("El proceso padre esta eperando a los  hijos");
            sem_wait(semaforo2);
        }
       
        /*
        for(i = 0; i<4; i++){
            printf("%f\n", atof(direccionMC+i));
        }*/
        //wait(NULL);
    }
    printf("El proceso padre termino");
    return 0;
}


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