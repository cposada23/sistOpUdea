#include<stdio.h>

#define SIZE 3  //macro

void getData(float numbers[], int size);
void printData(float numbers[], int size);

int main(){
    
    
    float numbers[SIZE];
    getData(numbers, SIZE);
    printData(numbers, SIZE);
    
    return 0;
    
}


void getData(float numbers[], int size){
    int i;
    
    printf("Ingrese los %d valores \n", size);
    for(i = 0; i<size; i++){
        scanf("%f",&numbers[i]);
    }
    
}


//scanf me pide la direccion, el puntero tiene la direccion
void printData(float numbers[], int size){
    
    int i;
    
    printf("los %d valores son \n", size);
    for(i = 0; i<size; i++){
        printf("%f \n",numbers[i]);
    }
}

// MEMORIA DINAMICA -> MAN MALLOC 