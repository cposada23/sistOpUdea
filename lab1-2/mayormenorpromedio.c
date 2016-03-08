#include<stdio.h>

#define MAX 10

float promedio(float *numeros, int n);
void mostrarNUmeros(float *numeros, int n);

int main(){
    
    float numeros[MAX], prom=0.0; 
    char letra='s';
    char nmg []= "Número más grande";
    char nmp []= "Número más pequeño";
    float mayor, menor;
    int i = 0;
    while(i<MAX){
        i++;
        printf("Ingrese el numero #%d: " , i);
        scanf("%f",numeros+(i-1));
        if(i == 1){
            mayor = *(numeros);
            menor = *(numeros);
        }else{
            if(*(numeros+(i-1))<menor){
                menor = *(numeros+(i-1));
            }
            
            if(*(numeros+(i-1))>mayor){
                mayor = *(numeros+(i-1));
            }
        }
        printf("¿desea continuar?... digite x para terminar ");
        scanf("%s",&letra);
        //printf("letra %c", letra);
        if(letra =='x' || letra =='X'){
            break;
        }
    }
    prom = promedio(numeros,i);
    //mostrarNUmeros(numeros, i);
    printf("\n");
    printf(" ___________________________________________\n");
    printf("|%31.20s | %-10d|\n","Números ingresados",i);
    printf(" -------------------------------------------\n");
    printf("|%33.21s | %-10.3f|\n",nmp,menor);
    printf(" -------------------------------------------\n");
    printf("|%32.20s | %-10.3f|\n",nmg,mayor);
    printf(" -------------------------------------------\n");
    printf("|%30.20s | %-10.3f|\n","Promedio", prom);
    printf(" -------------------------------------------\n");
    printf("\n");
    return 0;
}

void mostrarNUmeros(float *numeros, int n){
    int i;
    
    for ( i = 0; i < n; i++) {
         printf("%.2f ",*(numeros+i));
    }
}

float promedio(float *numeros, int n){
    int i;
    float promedio = 0.0;
    
    for (i = 0; i < n; i++) {
        promedio = promedio + *(numeros+i);
    }
    promedio = promedio / n;
    return promedio;
}