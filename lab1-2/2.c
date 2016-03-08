git#include <stdio.h>
//#include<math.h>   op matematicas  P= sqrt(x+1)/pow(y,2);
int main()
{
	float base, altura, cateto1, cateto2, area, perimetro;
	printf("Ingrese la altura del triangulo: ");
	scanf("%f", &altura);

	printf("\nIngrese la base del triangulo: ");
	scanf("%f", &base);

	printf("\nIngrese el cateto1 del triangulo: ");
	scanf("%f", &cateto1);

	printf("\nIngrese la cateto2 del triangulo: ");
	scanf("%f", &cateto2);

	area = (base * altura)/2;
	perimetro = base +cateto1 + cateto2;

	printf("\nEl área del triángulo de base %.2f cm y altura %.2f cm es %.2fcm2.\n", base, altura, area);

	printf("\nEl perímetro del triángulo de base %.2f cm y altura %.2f cm es %.2fcm.\n", base, altura, perimetro);
	

	//printf("El numero es: %d\n",n );
	return 0;
}