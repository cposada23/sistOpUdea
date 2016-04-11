#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXCHAR 20
#define MAXITEMS 100

void newBill(int *codes,int *values);
void printBill(int n, int *quantity, int *value, int total, int *totals, int *code);
void checkItem(int *codes, char (*description)[MAXCHAR], int *values);

int main(int argc, char *argv[]){
	
	int codes[MAXITEMS] = {101,102,103,104,105,106};
	char descriptions[MAXITEMS][MAXCHAR] = {"Articulo#1", "Articulo#2", "Articulo#3","Articulo#4","Articulo#5", "Articulo#6"};
	int values[MAXITEMS]={300,500,250,100,900,600};
	char option;

	while(option!='q'){

		printf("Ingrese \n a. Nueva factura \n b. Consultar articulo \n c. Ingresar articulo \n q. Salir \n");
		setbuf(stdin, NULL);
		scanf("%c", &option);

		 if (option=='a'){
		 	//Creating a new ticket
		 	newBill(codes, values );
		 } else  if(option=='b'){
		 	//Checking an item
		 	checkItem(codes, (char (*)[MAXCHAR])descriptions[0], values);
		 } else  if(option=='c'){
		 	//Add new item to list
		 	
		 } else  if(option=='q'){
		 	return 0;
		 } else{
		 	 printf("Opcion no valida\n");
		 }
	}
	return 0;
}

void newBill(int *codes, int *values){
	int numItems;
	int inCode;
	int flag=0;
	int i=0;
	int j=0;

	int *pCodes;	
	int *pQuantities;
	int *pTotalPerCode;
	int total = 0;

	printf("Numero de articulos a facturar: ");
	scanf("%d", &numItems);

	pCodes = (int *)malloc(sizeof(int)*numItems);
	pQuantities = (int *)malloc(sizeof(int)*numItems);
	pTotalPerCode = (int *)malloc(sizeof(int)*numItems);

	while ( i<numItems ){
		setbuf(stdin, NULL);
		printf("\n\nArticulo #%d\n", i+1);
		printf("Codigo: \n");
		scanf("%d", &inCode);
		flag=0;
		//Para validar que el codigo es de un articulo existente		
		for (j=0; j<MAXITEMS;j++){
			if(inCode == codes[j]){
				pCodes[i] = inCode;

				printf("Cantidad: \n" );
				scanf("%d", pQuantities+i);
	
				pTotalPerCode[i] = values[j]*pQuantities[i];
				total += pTotalPerCode[i];

				printf("Valor: %d --- Acumulado:  %d \n", pTotalPerCode[i], total);
		
				flag=1;
				i++;
			}	
		}
		if(flag==0){
			printf("El articulo con codigo %d no se encontró\n", inCode);
		}
		
	}

	printBill(numItems, pQuantities,  values, total, pTotalPerCode,codes );
	
}

void printBill(int n, int *quantity, int *value, int total, int *totals, int *code){
	printf("\n\n\t\tFactura de Venta\n");
	printf("\t\t Nombre Empresa \n");
	
	printf("Cantidad  | Codigo | V. unit   | Total\n");
	int i;
	for (i=0; i<n;i++){
		printf("%-8d  | %-5d  | %-10.2d| %d\n", quantity[i], code[i], value[i], totals[i] );
	}
	printf("Total: %d\n\n",total );
}

void checkItem(int *codes, char (*description)[MAXCHAR], int *values){

	int inCode;
	int flag = 0;
	printf("\nCodigo Articulo: ");
	scanf("%d", &inCode);

	int cnt;
	for (cnt=0; cnt<MAXITEMS;cnt++){
		if(inCode==codes[cnt]){
			printf("%s --> %d \n\n", (char *)(description+cnt), *(values+cnt) );	
			flag=1;		
		}
	}
	if(flag == 0)
		printf("El articulo con codigo %d no se encontró\n", inCode);
}
