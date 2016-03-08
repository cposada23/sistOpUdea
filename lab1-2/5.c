#include <stdio.h>
#include <stdlib.h>


int main(){
    char palabra[40];
    char c;
    system("clear");
    printf("Ingrese una palabra: ");
    scanf("%s", palabra);
    
    c= palabra[0];
    if(c =='a' || c =='A'|| c=='e'|| c=='E'|| c=='i'|| c=='I'|| c=='o'|| c=='O'|| c=='u'|| c=='U'){
        printf("La palabra %s comienza por la vocal %c\n", palabra, c);
    }
    
    return 0;
  
    
    
}