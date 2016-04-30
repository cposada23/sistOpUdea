#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>



int main(int argc, char* argv[]){
    
    
    int spawn(char* programa, char** argumentos){
        pid_t pid_hijo;
        pid_hijo = fork();
        switch(pid_hijo){
            case 0:
                //Hijo
                execvp(programa, argumentos);//Si ecxec funciona nose ejecuta lo de abajo  
                fprintf(stderr, "Error programa %s", programa);  //
                abort();
                break;
            default:
                wait(NULL);
                printf("Termino %s\n", programa);
                return pid_hijo;
                //Padre
                break;
        }
    }
    
    
    char *argumentos1[] = {"gcc", argv[1],"-o", argv[2], NULL};
    char *argumentos2[] = {argv[2], NULL};
    
    //nombre del programa y la lista
    spawn(argumentos1[0],argumentos1);
    sleep(2);
    spawn(argumentos2[0],argumentos2);
    return 0;
}