#include <stdio.h>
int main()
{
	char nombre1[40];
	char nombre2[40];
	char nombre3[40];
	char nombre4[40];
	char nombre5[40];


	float estatura1,estatura2,estatura3,estatura4,estatura5;

	printf("Ingrese el nombre del paciente #1: ");
	fgets(nombre1, 40, stdin);
	printf("\nIngrese la estatura del paciente #1: ");
	scanf("%f", &estatura1 );

	setbuf(stdin, NULL);
	printf("Ingrese el nombre del paciente #2: ");
	fgets(nombre2, 40, stdin);
	printf("\nIngrese la estatura del paciente #2: ");
	scanf("%f", &estatura2 );

	setbuf(stdin, NULL);
	printf("Ingrese el nombre del paciente #3: ");
	fgets(&nombre3[0], 40, stdin);
	printf("\nIngrese la estatura del paciente #3: ");
	scanf("%f", &estatura3);

	setbuf(stdin, NULL);
	printf("Ingrese el nombre del paciente #4: ");
	fgets(&nombre4[0], 40, stdin);
	printf("\nIngrese la estatura del paciente #4: ");
	scanf("%f", &estatura4 );

	setbuf(stdin, NULL);
	printf("Ingrese el nombre del paciente #5: ");
	fgets(&nombre5[0], 40, stdin);
	printf("\nIngrese la estatura del paciente #5: ");
	scanf("%f", &estatura5);

	printf("El paciente #1 %s mide %f metros\n",nombre1, estatura1);
	printf("El paciente #2 %s mide %f metros\n",nombre2, estatura2);
	printf("El paciente #1 %s mide %f metros\n",nombre3, estatura3);
	printf("El paciente #1 %s mide %f metros\n",nombre4, estatura4);
	printf("El paciente #1 %s mide %f metros\n",nombre5, estatura5);
	return 0;
}