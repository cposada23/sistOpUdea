#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[20];
    float grade;
    int credits;
}stcSubject;



int main(int argc, char * argv[]){
    
    //abrir un archivo 
    FILE *file;
    char *fileName;
    fileName = argv[2];
    stcSubject subject;
    file = fopen(fileName,"r");
    if (file == NULL){
        printf("no se abrio el archivo");
    }
    
    
    //lectura del archivo
    while(feof(file)){
        fscanf(file, "%s", subject.name);
        printf("%s", subject.name);
        
        fscanf(file."%f",&subject.grade)
        printf("%f", subject.grade );
    }
    return 0;
}