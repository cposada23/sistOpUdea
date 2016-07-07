#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define SHMSZ 27


int main(){
    

    int shmid;
    key_t key;
    char *shm, *s;
    
    //Nombre del segmento de mmoria ompartida
    key = 1234;
    
    //se crea el segmento de memoria 
    if((shmid = shmget(key,SHMSZ, IPC_CREAT | 0666))<0){
        perror("shmget");
        exit(1);
    }
    
    //Se adhiere al segmento creado
    if((shm = shmat(shmid, NULL, 0))==(char * )-1){
        
        perror("shmat");
        exit(1);
    }
    
    for(s = shm; *s!='\0'; s++){
        putchar(*s);
    }
   putchar('\n');
   
   //indico que e leido el segmento
   *shm = '*';
    exit(0);
}