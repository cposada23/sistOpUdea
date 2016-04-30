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
    pid_t  pid2;
    pid_t pid[4];
    for(i = 0; i<numhijos; i++){
        pid[i] = fork();
        if(pid[i]==-1){
            printf("No fue posible crear un hijo\n");
        }else if(pid[i]==0){
            switch(i){
                case 0:
                printf("funciona case");
                    op = a+b;
                    break;
                case 1:
                    op = a-b;
                    break;
                case 2:
                    op = a/b;
                    break;
                case 3:
                    op = a*b;
                    break;
            }
            exit(op);
        }
        
    }
    printf("proceso padre");
    for (i = 0; i<numhijos; i++){
        pid2 = wait(&resultado);
        switch((int)pid2){
            case (int)pid[1]:
                printf("a + b = %d\n",WEXITSTATUS(resultado));
        }
    }
    
    /*for ( i = 0; i < numhijos; i++) {
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
    }*/
    
    
    
    return 0;
}