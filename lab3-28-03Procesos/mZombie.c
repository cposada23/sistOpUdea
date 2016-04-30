#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include<stdio.h>
int main () {
    pid_t child_pid;
    //int status;
    /* Creacion del proceso hijo. */
    child_pid = fork ();
    if (child_pid > 0) {
        /* Este es el proceso padre el cual duerme por 20 segundos. */
        printf("padre esperando 20seg");
        sleep (10);
        printf("padre despierta");
        //wait(&status);
        //printf("padre espero %d", WEXITSTATUS(status));
        printf("padre espero");
    }
    else {
        /* Este es el proceso hijo el cual culmina inmediatamente. */
        printf("proceso hijo finaliza");
        exit (25);
    }
    printf("padre termina");
    return 0;
}