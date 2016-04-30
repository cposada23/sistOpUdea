#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int args, char *argv[]){
    int i;
    int numhijos = 3;
    pid_t pid;
    for ( i = 0; i < numhijos; i++) {
        pid = fork();
        if(pid == -1){
            printf("No fue posible crear un hijo\n");
            return -1;
        }
        if(pid ==0){
            printf("Soy el hijo #%d con PID: %d\n" ,i+1, getpid());
            exit(0);
        }
    }
    
    return 0;
}