#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR 50


/*-------- Funciones ---------*/
void getOpcion(char *opcion);
void registrar(int *trabajadoresInscritos, int max, char (*nombres)[MAX_CHAR]  , float *salarios, float *horasextra);
void calculaNomina(char (*nombres)[MAX_CHAR]  ,float *salarios,float *horasextra, int trabajadoresInscritos, int valorHoraExtra);
void mostrarListaEmpleados(char (*nombres)[MAX_CHAR], float *salarios,float *horasextra, int trabajadoresInscritos);

int main(int argc, char *argv[]){
    
    int max = 0; /* numero maximo de trabajadores que se van a registrar */
    int trabajadoresInscritos = 0;
    char opcion= 'z';
    char (*nombres)[MAX_CHAR];
    float *salarios;
    float *horasextra;
    float valorHoraExtra = 0;
    
    /* -----  Validación de los argumentos ---- */
    if (argc<=2){
        printf("ERROR: Se esperaba el maximo numero de empleados y el valor de la hora extra; se esperaba %s <numero empleados> <Valor Hora Extra>\n", argv[0]);
        exit(0);
    }else{
        max = atoi(argv[1]);
        valorHoraExtra = atof(argv[2]);
        if(max <=0){
            printf("ERROR: argumento no valido se esperaba un numero de trabajadores a registrar positivo mayor que 0: %s\n", argv[1]);
            exit(0);
         }if(valorHoraExtra<=0){
             printf("ERROR: argumento no valido <valor Hora Extra>\n");
         }
         
         
    }
    /* Memoria dinamica */
    
    nombres = (char (*)[MAX_CHAR])malloc(sizeof(char[MAX_CHAR])*max);
    salarios =(float *) malloc(sizeof(float)*max);
    horasextra = (float *)malloc(sizeof(float)*max);
    
    do{
        getOpcion(&opcion);
        switch(opcion){
            case 'a':
                registrar(&trabajadoresInscritos,  max, nombres,salarios,horasextra);
                break;
                
            case 'b':
                mostrarListaEmpleados(nombres, salarios, horasextra,trabajadoresInscritos);
                break;
            case 'c':
                calculaNomina(nombres, salarios, horasextra,trabajadoresInscritos,valorHoraExtra);
                break;
            case 'q':
                printf("\nsaliendo del programa...\n");
                break;
            default:
                printf("---- ****Opción incorrecta %c****------\n\n",opcion);
                break;
        }
    }while(opcion!='q');
    
    printf("\n");
    return 0;
    
}
/* ---- Mostrar e menú ---- */
void getOpcion(char *opcion){
    

    
    printf("\nMENU DE OPCIONES\n");
    printf("\ta) Registrar trabajadores.\n");
    printf("\tb) Ver lista de trabajadores\n");
    printf("\tc) Calcular nomina.\n");
    printf("\tq) salir del programa.\n");
    printf("Seleccione una opcion: ");
    setbuf(stdin, NULL);
    scanf("\n%c", opcion);
}

/* ---- Registrar empleados ---- */
void registrar(int *_trabajadoresInscritos, int max, char (*nombres)[MAX_CHAR] , float *salarios, float *horasextra){
    int aRegistrar = 0, i;
    if (*_trabajadoresInscritos==max){
        printf("\n\n**** Ya se han registrado el numero maximo de trabajadores****\n\n");
    }else{
        printf("Cuandos trabajadores va a registrar: ");
        setbuf(stdin, NULL);
        scanf("\n%d", &aRegistrar);
        if ((aRegistrar + *_trabajadoresInscritos)>max){
            printf("No se pueden registrar %d trabajadores, ya que excede el limite máximo que es %d y ya hay %d trabajadores registrados",aRegistrar,max,*_trabajadoresInscritos);
        }else{
         
            for (i = 0; i < aRegistrar; i++) {
                printf("Ingrese el nombre del trabajador %d: ",i+1);
                scanf("%s", (char *)(nombres+i+*(_trabajadoresInscritos)));
                printf("\nIngrese el salario del trabajador %d: ", i+1);
                scanf("%f",  (salarios+i+*_trabajadoresInscritos));
                printf("\nIngrese las horas extras del trabajador %d: ", i+1);
                scanf("%f",  (horasextra+i+*(_trabajadoresInscritos)));
            }
             *_trabajadoresInscritos += aRegistrar;
             printf("\nSe registraron %d nuevos trabajadores", aRegistrar);
             
        }
        
    }
    
}

/* ---- Calcular nomina ----*/
void calculaNomina(char (*nombres)[MAX_CHAR]  ,float *salarios,float *horasextra, int trabajadoresInscritos, int valorHoraExtra){
    //  Nombre Salario base Salario extra Total
    int i;
    float salarioExtra = 0;
    float total = 0;
    float totalSalarios = 0;
    if (trabajadoresInscritos<=0){
        printf("\n\n**** No se han registrado trabajadores ****\n\n");
    }else{
        printf("\n\t** Lista de trabajadores ** \n");
        printf("Nombre de la empresa    NIT.#######");
        printf("\n_____________________________________________________________________________________________");
        printf("\n|%-20s | %-21s | %-21s | %-21s|\n","Nombre","Salario base", "Salario extra", "Total");
        printf("____________________________________________________________________________________________\n");
        for (i = 0; i < trabajadoresInscritos; i++) {
           salarioExtra = (*(horasextra+i)*valorHoraExtra);
           total = *(salarios+i)+salarioExtra;
           totalSalarios+=total;
           printf("|%-20s | $%-20.2f |$ %-20.2f | $%-20.32|\n",*(nombres+i), *(salarios+i), salarioExtra, total);
        }
        printf("---------------------------------------------------------------------------------------------\n");
        printf("|Total: $%-84.2f|\n",totalSalarios);
        printf("_____________________________________________________________________________________________");
    }
    
   
}

/* ---- Mostrar lista de empleados ---- */
void mostrarListaEmpleados(char (*nombres)[MAX_CHAR], float *salarios,float *horasextra, int trabajadoresInscritos){
    int i;
    if(trabajadoresInscritos<=0){
        printf("\n\n**** No se han registrado trabajadores ****\n\n");
    }else{
        
        printf("\n\n\nLista de trabajadores     \n");
        printf(" ________________________________________________________________\n");
        printf("|%-20s | %-21s|%-20s|\n", "Nombre","Salario Base","Horas Extra");
        printf("-----------------------------------------------------------------\n");
        for (i = 0; i < trabajadoresInscritos; i++) {
            printf("|%-20s | $%-20.2f|%-20.1f|\n", *(nombres+i), *(salarios+i), *(horasextra+i));
        }
        printf(" ________________________________________________________________");
        
    }
        
    
    
}