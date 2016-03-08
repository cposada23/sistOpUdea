#include<stdio.h>

int main(){
    int a = 3;
    int c= 7;
    int b = 4;
    int *p = &a;
    *p = 5;
    p = p + 1;
    *p = 6;
    printf("a: %d b: %d c: %d \n", a,b,c);
    
    return 0;
}