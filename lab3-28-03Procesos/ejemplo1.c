#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]){
    int valor_retornado;
    printf("El id del proceso es: %d\n",(int)getpid());
    printf("El valor del id padre del proceso es: %d\n",(int)getppid());
    valor_retornado = system("cal");
    valor_retornado = system("ls -l .");
    return valor_retornado;
   
};