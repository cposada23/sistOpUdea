#include <stdio.h>
int main()
{
	

	char nombre1[10];
	char nombre2[10];
	char nombre3[10];


	float estatura1;
	float estatura2;
	float estatura3;


	printf("Ingrese el nombre de la persona #1: ");
	scanf("%s", nombre1);
	printf("Ingrese la estatura de la persona #1\n");
	scanf("%f", &estatura1);



	printf("Ingrese el nombre de la persona #2: ");
	scanf("%s", nombre2);
	printf("Ingrese la estatura de la persona #2\n");
	scanf("%f", &estatura2);


	printf("Ingrese el nombre de la persona #3: ");
	scanf("%s", nombre3);
	printf("Ingrese la estatura de la persona #3\n");
	scanf("%f", &estatura3);


	printf("|Nombre    |Estatura|\n");
	printf("-------------------\n");
	printf("|%-10.10s|%8.2f|\n",nombre1, estatura1);
	printf("|%-10.10s|%8.2f|\n",nombre2, estatura2);
	printf("|%-10.10s|%8.2f|\n",nombre3, estatura3);




	return 0;
}