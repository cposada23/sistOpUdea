
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include<stdlib.h>  // para exit

int value = 5;

int main (){
    pid_t pid;
    pid = fork();
    if(pid==0){
        value +=15;
        return 0;
    }else if(pid>0){
        wait(NULL);
        printf("parent: Value = %d", value);
        return 0;
    }
    return 0;
    
    
}