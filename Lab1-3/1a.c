#include<stdio.h>
#include <stdlib.h>

#define MAX_CHARS_NAME 10

int main(){
    
    int total = 100;
    int n = 0, i = 0;
    int *numero;
    
    numero = (int (*))malloc(sizeof(int));
    
    
    printf("Cantidad de numeros? :");
    
    setbuf(stdin, NULL);
    scanf("%d", &n);
    
    printf("N: %d" ,n);
    
    
    while(i<n){
        printf("ingrese el numero #%d", i+1);
        setbuf(stdin, NULL);
        scanf("%d", numero);
        total = total - *numero;
        i++;
    }
    printf("Total %d", total);
    
    
    return 0;

}