#include <stdio.h>
#include <stdlib.h>
int main(){
    
    char x;
    float n1, n2, res;
    do{
        
        printf("MENU\n");
        printf("1. Suma\n");
        printf("2. Resta\n");
        printf("3. Multiplicaciòn\n");
        printf("4. Divisiòn\n");
        printf("q. Salir\n");
        scanf("%s", &x);
        
        if (x != 'q'){
            printf("Ingrese el primer nùmero: ");
            scanf("%f", &n1);
            printf("Ingrese el segundo nùmero: ");
            scanf("%f", &n2);
            
        }
        
        switch(x){ 
            
            case 'q':
                printf("\nSaliendo...\n");
                break;
            case '1':
                res = n1+n2;
                printf("\n%.4f + %.4f = %.4f\n\n", n1, n2, res);
                break; 
            case '2': 
                res = n1-n2;
                printf("\n%.4f - %.4f = %.4f\n\n", n1, n2, res);
                break;
            case '3':
                res = n1*n2;
                printf("\n%.4f * %.4f = %.4f\n\n", n1, n2, res);
                break; 
            case '4': 
                res = n1/n2;
                printf("\n%.4f / %.4f = %.4f\n\n", n1, n2, res);
                break; 
            
            default: 
                printf("\nOpcion incorrecta\n");
                break;
        } 
        
    }while(x!='q');
    
    /*while(x!='q'){
        printf("Ingrese un caracter: ");
        scanf("%s", &x);
    };*/
    
    return 0;
}