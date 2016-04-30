#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>


int main(int args, char *argv[]){
    int i;
    int numhijos = 4;
    int a = 5; 
    int b = 2;
    int op;
    int resultado;
    pid_t pid, pid2;
    for ( i = 0; i < numhijos; i++) {
        pid = fork();
        if(pid == -1){
            printf("No fue posible crear un hijo\n");
            return -1;
        }
        if(pid ==0){
            switch(i){
                case 0:
                    op = a+b;
                    //printf("op + %d\n" , op);
                    break;
                    
                case 1:
                    op = a-b;
                    //printf("op -  %d\n" , op);
                    break;
                    
                case 2:
                    op = a/b;
                    //printf("op /  %d\n" , op);
                    break;
                    
                case 3:
                    op = a*b;
                    //printf("op *  %d\n" , op);
                    break;
                
            }
            exit(op);
        }
        else{
            pid2=wait(&resultado);
            switch(i){
                case 0:
                    printf("suma: ");
                    break;
                    
                case 1:
                    printf("resta: ");
                    break;
                    
                case 2:
                    printf("div: ");
                    break;
                    
                case 3:
                    printf("mult: ");
                    break;
                
            }
            printf(" %d pid2: %d resultado: %d\n", WEXITSTATUS(resultado), (int)pid2, *resultado );
        }
    }
    
    
    
    return 0;
}