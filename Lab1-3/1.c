#include <stdio.h>

int main(){
    
    
    int A[6] = {2,3,1,0,9,6};
    
    int a = *(A+1);
    printf("a: %d \n" ,a);
    int b = *A + 1;
    printf("b: %d \n", b);
    
    *p1 = A;
    
    
    /*int *p1;
    int *p2 = &A[5];
    p1 = A;
    */
    /*printf("p2: %d \n", *p2);
    printf("p1: %d \n", *p1);
    p1 +=2;
    printf("p1: %d \n", *p1);
    *p1 = 5;
    printf("p1: %d \n", *p1);
    
    p2--;
    printf("*(p2-1): \n" , (*p2));
    printf("p2 --: %d \n", *p2);
  
    printf("p2 --: %d \n", *p2);
    
    printf("A : %d", *A);
    */
    
    
    return 0;
}