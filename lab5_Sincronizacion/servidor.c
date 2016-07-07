#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define SHMSZ 27


int main(){
    
    char c,k;
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
    
    //pongo datos en el segmento para el que el porceso clinte los lea

    s = shm;
    for( c = 'a'; c<='z'; c++){
        *s++ = c;
        for(k='A';k<='Z';k++){
            *s++ = k;
        }
    }
    *s =NULL;
    
    while(*shm != '*'){
        sleep(1);
    }
    return(0);
}