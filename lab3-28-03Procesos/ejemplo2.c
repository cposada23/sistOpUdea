#include<unistd.h>
#include<stdio.h>

int main(int args, char *argv[]){
    pid_t pid_hijo;
    printf("Ejemplo fork\n");
    printf("pid programa principal %d\n",(int)getpid() );
    switch(pid_hijo = fork()){
        case -1:
            printf("Error al crear el proceso\n");
            return -1;
        case 0:
            printf("Lo ejecutado por el hijo\n");
            break;
        default:
            printf("Ejecutado por el padre: proceso hijo con PID %d\n", (int)pid_hijo);
            
    }
    printf("Ambos procesos? \n");
    return 0;
}