/*
	Example: How to use system call fork
	compile: gcc -o fork fork_ejemplo.c
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include<stdlib.h>  // para exit

int main(){

	pid_t pid;
	int value = 5;
	pid  =  fork();  //retorna 0 al proceso hijo y al padre le retorna pid del proceso hijo 
	
	printf("HOLA");
	if( pid < 0 ){		/*Error */ 
		fprintf(stderr, "Fork failed ");
		exit(1);
	}	
	if( !pid  ){ 	//Child
		value += 15;
		printf("\nCHILD: value = %d \n", value ); //LINE B
		return 0;
	}
	else if( pid > 0 ){		//Parent
		wait(NULL);
		printf("\nPARENT: value = %d\n", value ); //LINE A
		return 0;

	}
	
	
	return 0;
}

