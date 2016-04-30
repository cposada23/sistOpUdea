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
            printf("Lo ejecutado por el hijo con pid: %d\n pid_hijo case 0 : %d\n", (int)getpid(), (int)pid_hijo);
            break;
        default:
            printf("Ejecutado por el padre con pid %d : proceso hijo con PID %d\n", (int)getpid(),(int)pid_hijo);
            
    }
    printf("Ambos procesos? \n");
    return 0;
}