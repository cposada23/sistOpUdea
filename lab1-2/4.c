#include <stdio.h>
#include <stdlib.h>

int main(){
    //short edad; preguntar??
    int edad, meses;
    system("clear");
    printf("Ingrese su edad en años: "); 
    scanf("%d" , &edad);
    meses = edad *12;
    printf("--------------------------------------------------\n");
    printf("|%-24.24s|%-24.24s|\n", "Calsificación", "Edad en meses");
    printf("--------------------------------------------------\n");
    if (edad<=2){
        printf("|%23.23s|%24d|\n", "Bebe", meses);
    }
    else if (edad>2 && edad <=12){
        printf("|%23.23s|%24d|\n", "Niño", meses);
    }
    else if (edad>13 && edad <=17){
        printf("|%23.23s|%24d|\n", "Adolecente", meses);
    }
    else if (edad>17){
        printf("|%23.23s|%24d|\n", "Adulto", meses);
    }
    
    printf("--------------------------------------------------\n");
    
    return 0;
}