#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CHAR 30

typedef struct{
    char descripcion[MAX_CHAR];
    float valor;
    int codigo;
}str_item;




void registerItems(str_item * items, FILE *file, int numItems);
void mostrarInfoItems(str_item *items, int numItems);
void imprimirFactura(str_item *items, FILE *factura, int numItems);
void getOption(char *option);
int getNumItems(FILE *file);

int main(int argc, char*argv[]){
        
    str_item *items;
    FILE *itemsFile;
    char *fileName;
    char *factura = "ticket.txt";
    FILE *fact;
    char opcion = 's';
    int numeroItems;
    short registrados = 0;
    if (argc != 2){
        printf("Error: Se esperaba el siguiente formato\n");
        printf("--> %s <archivoEntrada>.txt\n",argv[0]);
        exit(0);
    }
    
    
    fileName = argv[1];
    //Abro el archivo items
    itemsFile = fopen(fileName, "r");
    
    //Lo pudo abrir?
    if (itemsFile==NULL){
        printf("No se pudo leer el archivo %s\n", argv[1]);
        exit(0);
    }
    
    numeroItems = getNumItems(itemsFile);
    printf("Hay %d items registrados en el archivo\n", numeroItems);
    
    //memoria dinamica
    items =(str_item*) malloc(sizeof(str_item)*numeroItems);
    
    do{
        getOption(&opcion);
        switch(opcion){
            case 'a':
                printf("registrando items...\n");
                registerItems(items, itemsFile, numeroItems);
                registrados = 1;
                break;
            case 'b':
                printf("Info items...\n");
                if(registrados==1){
                    mostrarInfoItems(items, numeroItems);
                }else{
                    printf("No se han registrado items... registrar primero");
                }
                break;
            case 'c':
                system("clear");
                printf("Imprimiendo factura.... \n");
                if(registrados==1){
                    fact = fopen(factura, "a");
                    if (fact== NULL){
                        printf("No se pudo abrir/crear el archivo %s", factura);
                        exit(0);
                    }
                    imprimirFactura(items,fact,numeroItems);
                    fclose(fact);
                    printf("factura lista\n");
                }else{
                    printf("No se han registrado items... registrar primero");
                }
                break;
            case 'd':
                printf("saliendo del pograma... \n");
                fclose(itemsFile);
                break;
        }
    }while(opcion!='d');
    return 0;
}

void getOption(char *option){
    setbuf(stdin,NULL);
    printf("\tOPCIONES\n");
    printf("a) Registrar items\n");
    printf("b) Mostrar Info items\n");
    printf("c) Imprimir factura\n");
    printf("d) Salir\n");
    setbuf(stdin, NULL);
    scanf("\n%c", option);
}

int getNumItems(FILE *file){
    
    int num = 0;
    char buffer[MAX_CHAR];
    while(!feof(file)){
        fgets(buffer,MAX_CHAR , file);
        num++;
    }
    rewind(file);
    return num/3;
}

void registerItems(str_item *items, FILE *file, int numItems){
    
    int i;
    for (i = 0; i < numItems; i++) {
        
        fscanf(file, "%d", &items->codigo);
	    printf("%d\n",items->codigo);
		
        fscanf(file, "%s", &items->descripcion[0]);
		printf("%s\n", items->descripcion);
		
		fscanf(file, "%f", &items->valor);
		printf("%f\n",items->valor);
		
        items++;
    }
}

void mostrarInfoItems(str_item *items, int numItems){
    int i;
    printf("|%10s|%15s|%10s|\n","Codigo", "Descripcion","valor");
    printf("---------------------------------------\n");
    for(i=0;i<numItems;i++){
        printf("|%10d|%15s|%10.2f|\n",items->codigo,items->descripcion,items->valor);
        items++;
    }
}

void imprimirFactura(str_item *items, FILE *factura, int numItems){
    int i;
    fprintf(factura,"\t\tFactura de venta\n");
    fprintf(factura,"\tNombre empresa \tnit.xxxxxxxx\n");
    fprintf(factura,"|%10s|%15s|%10s|\n", "Codigo", "Descripcion","Valor");
    for (i = 0; i < numItems; i++) {
        fprintf(factura, "|%10d|%15s|%10.2f|\n", items->codigo, items->descripcion, items->valor);
        items++;
    }
}










