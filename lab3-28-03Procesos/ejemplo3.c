#include<unistd.h>
#include<stdio.h>

int main(int args, char *argv[]){
    pid_t hijo1, hijo2, hijo3, nieto;
    int i = 0;
    printf("Ejemplo fork\n");
    printf("pid programa principal %d\n",(int)getpid() );
    switch(hijo1 = fork()){
        case -1:
            printf("Error al crear el proceso\n");
            return -1;
        case 0:
            i++;
            printf("Hijo 1: i: %d\n",i)
            switch(nieto = fork()){
                case -1:
                    printf("Error al crear el nieto\n");
                    break;
                case 0:
                    
            }
            printf("Lo ejecutado por el hijo con pid: %d\n pid_hijo case 0 : %d\n", (int)getpid(), (int)pid_hijo);
            break;
        default:
            printf("Ejecutado por el padre con pid %d : proceso hijo con PID %d\n", (int)getpid(),(int)pid_hijo);
            break;
    }
    printf("Ambos procesos? \n");
    return 0;
}