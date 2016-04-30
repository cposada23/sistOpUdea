#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include<stdio.h>

int main(int argc, char *argv[]) {  
    pid_t pid1, pid2, pid3;
    pid1 = fork();
    char *args[] = {"/bin/ls", "-l", ".", NULL};
    switch(pid1){
        case -1:
            printf("error");
            break;
        case 0:
            printf("Forma 1: \n");
            execl("/bin/ls", "/bin/ls", "-l", ".", NULL);
            break;
        default:
            sleep(10);
            pid2 = fork();
            switch (pid2){
                case -1:
                    printf("error");
                    break;
                case 0:
                    printf("Forma 2: \n");
                    execv("/bin/ls", args);
                    break;
                default:
                    sleep(10);
                    pid3 = fork();
                    switch(pid3){
                        case -1:
                            printf("Error");
                        case 0:
                            printf("Forma 3: \n");
                            execvp("/bin/ls", args);
                            break;
                        default:
                            sleep(10);
                            printf("padre termina");
                            break;
                    }
                    break;
            }
            break;
    }
    printf("Ejecutable: \n");
    
    return 0;

}