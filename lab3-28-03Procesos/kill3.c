#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include <wait.h>


int main(){
    pid_t pid;
    pid = fork();
    //int res;
    switch(pid){
        case -1:
            printf("Error no se creo el hijo");
            break;
        case 0:
            printf("Hijo pid: %d getpid():%d\n", (int)pid, (int)getpid());
            printf("Hijo pid: %d getpid():%d\n", (int)pid, (int)getpid());
            //exit(12);
            break;
        default:
           // wait(&res);
            printf("proceso padre con pid: %d y pidHijo:%d\n", (int)getpid(), (int)pid);
            kill(pid,9);
            break;
    }
    /*printf("llamando a kill");
    kill(pid,9);
    printf("????");*/
    return 0;
}