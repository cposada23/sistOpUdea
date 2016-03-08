#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR 50

/*-------- Funciones ---------*/
void getOpcion(char *opcion);
void registrar(int *trabajadoresInscritos, int max, char (*nombres)[MAX_CHAR]  , float *salarios);
void calculaPago(float *salarios, int trabajadoresInscritos);
void mostrarListaEmpleados(char (*nombres)[MAX_CHAR], float *salarios, int trabajadoresInscritos);

int main(int argc, char *argv[]){
    
    int max = 0, trabajadoresInscritos = 0;
    char opcion= 'z';
    char (*nombres)[MAX_CHAR];
    float *salarios;
    
    /* -----  Validación de los argumentos ---- */
    if (argc<=1){
        printf("ERROR: maximo numero de empleados; se esperaba %s <numero empleados>\n", argv[0]);
        exit(0);
    }else{
        max = atoi(argv[1]);
        if(max <=0){
            printf("ERROR: argumento no valido: %s\n", argv[1]);
            exit(0);
         }
    }
    /* Memoria dinamica */
    // (char (*)[MAX_CHARS_NAME]) malloc(sizeof(char[MAX_CHARS_NAME]) * max_employees);
    nombres = (char (*)[MAX_CHAR])malloc(sizeof(char[MAX_CHAR])*max);
    salarios =(float *) malloc(sizeof(float)*max);
    
    do{
        getOpcion(&opcion);
        switch(opcion){
            case 'a':
                registrar(&trabajadoresInscritos,  max, nombres,salarios);
                break;
                
            case 'b':
                calculaPago(salarios,trabajadoresInscritos);
                break;
            case 'q':
                mostrarListaEmpleados(nombres, salarios, trabajadoresInscritos);
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
    printf("\tb) Obtener el pago total.\n");
    printf("\tq) Mostrar la lista y salir del programa.\n");
    printf("Seleccione una opcion: ");
    setbuf(stdin, NULL);
    scanf("\n%c", opcion);
}

/* ---- Registrar empleados ---- */
void registrar(int *_trabajadoresInscritos, int max, char (*nombres)[MAX_CHAR] , float *salarios){
    int aRegistrar = 0, i;
    printf("Cuandos trabajadores va a registrar: ");
    setbuf(stdin, NULL);
    scanf("\n%d", &aRegistrar);
    if ((aRegistrar + *_trabajadoresInscritos)>max){
        printf("No se pueden registrar %d trabajadores, ya que excede el limite máximo que es %d y ya hay %d trabajadores registrados",aRegistrar,max,*_trabajadoresInscritos);
    }else{
        for (i = 0; i < aRegistrar; i++) {
            printf("Ingrese el nombre del trabajador %d: ",i);
            scanf("%s", (char *)(nombres+i));
            printf("\nIngrese el salario del trabajador %d: ", i);
            scanf("%f",  (salarios+i));
        }
         *_trabajadoresInscritos += aRegistrar;
         printf("\nSe registraron %d nuevos trabajadores", aRegistrar);
         
    }
}

/* ---- Calcular pago a los empleados ----*/
void calculaPago(float * salarios, int trabajadoresInscritos){
    int i;
    float pago = 0;
    for (i = 0; i < trabajadoresInscritos; i++) {
        pago = pago + *(salarios+i);
    }
    printf("Pago total %.3f$", pago);
}

/* ---- Mostrar lista de empleados ---- */
void mostrarListaEmpleados(char (*nombres)[MAX_CHAR], float *salarios, int trabajadoresInscritos){
    int i;
    printf("\n\n\n<NOMBRE DE LA EMPRESA>      NIT:#######\n");
    printf(" ___________________________________________\n");
    printf("|%20s | %20s|\n", "Nombre","Salario");
    printf("---------------------------------------------\n");
    for (i = 0; i < trabajadoresInscritos; i++) {
        printf("|%20s | %20.3f|\n", *(nombres+i), *(salarios+i));
    }
    printf(" ___________________________________________\n\n");
}