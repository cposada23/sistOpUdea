#include <stdio.h>
#include <stdlib.h>


//promedio y elemento mayor de un array 

//#define SIZE 3

void getData(float data[], int size);
void getDataPtr(float *data, int size);
void printData(float data[], int size);
void printDataPtr(float *data, int size);
float average(float data[] , int size);
float mayor(float data[], int size);
float averageptr(float *data , int size);
float mayorptr(float *data, int size);


int main(int argc, char *argv[]){
	
	int size;
	//float numbers[SIZE];			//Static
	float *numbers;
  	float promedio = 0; 
  	float m = 0;
	size = atoi(argv[1]);
	numbers = malloc(sizeof(float)*size);		

	printf("%d", size);


	getDataPtr(numbers, size);	
	printDataPtr(numbers, size);
	promedio = average(numbers, size);
	printf("El promedio es %f \n" , promedio);
	m = mayor(numbers, size); 
	printf("El mayor es %f \n", m);
	
	
	m = mayorptr(numbers,size);
	printf("El mayor es %f \n", m);
	
	promedio = averageptr(numbers, size);
	printf("El promedio es %f \n" , promedio);
	free(numbers);
	return 0;
}

float mayor(float data[], int size){
	int i;
	float mayor = data[0];
	
	for(i=0; i<size; i++){
	  if(data[i]>mayor){
	    mayor = data[i];
	  }
	}
	
	return mayor;
}
float mayorptr(float *data, int size){
	int i;
	float mayor = *data;
	for(i = 0; i<size ; i++){
		if (*(data+i)>mayor){
			mayor = *(data+i);
		}
	}
	return mayor;
}


float average(float data[] , int size){
  	int i;
  	float promedio = 0;
  	for(i=0; i<size; i++){
  		promedio = promedio + data[i];
  	}
  	promedio = promedio/size;
  	return promedio;
}

float averageptr(float *data, int size){
	int i;
	float promedio = 0;
	for ( i = 0; i < size; i++) {
		promedio  = promedio + *(data+i);
	}
	promedio = promedio / size;
	return promedio;
}


void getData(float data[], int size){
	
	int i;
	printf("ingrese %d datos\n", size);
	for(i=0; i<size; i++){
		scanf("%f", &data[i]);
	}
}

void getDataPtr(float *data, int size){
	
	int i;
	printf("\ningrese %d datos\n", size);
	for(i=0; i<size; i++){
		scanf("%f", data+i);
	}
}


void printData(float data[], int size){

	int i;
	printf("Los datos son: \n");
	for(i=0; i<size; i++){
		printf("%.1f\n", data[i]);
	}
}

void printDataPtr(float *data, int size){

	int i;
	printf("Los datos son: \n");
	for(i=0; i<size; i++){
		printf("%.1f\n", *(data+i));
	}
}