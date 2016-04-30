#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>


int main(){
    pid_t pid;
    pid = getpid();
    printf("ID del procesooooo : %d\n",(int)pid);
    printf("ID del padre de este proceso: %d\n", (int)getppid());
    printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa"); printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa"); printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa"); printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
     printf("Holaaa");
    printf("Holaaa");
    printf("Holaaa");
    
    printf("llamando a kill");
    kill(pid,9);
    printf("????");
    return 0;
}