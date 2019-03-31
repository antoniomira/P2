#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
	// Declaración de variables
	int s = 0, // Cantidad de salidas 
		m = 0, // Cantidad de entradas
		n = 0, // Empresas que se van a utilizar
		k = 0, // Empresa que se va a analizar
		iteraciones = 0; // Cantidad de iteraciones que se desean hacer

	double espectroMinimo = 0.0, // Valor mínimo a buscar
		espectroMaximo = 0.0, // Valor máximo a buscar
		*theta; // Declaramos el puntero


	// Se asigna el tamaño del vector theta
	theta = (double*) malloc(sizeof(double)*n);

	/* COMIENZA LA PARTE 1 DEL ENUNCIADO */

	// Se piden los datos por pantalla del Usuario

	// Se pide la cantidad de empresas a generar
	printf("¿Cuántas empresas se van a utilizar? ");
	scanf("%i", &n);

	// Se pide cual de ellas se va a generar
	printf("\n¿Qué empresa se quiere analizar? ");
	scanf("%i", &k);

	// Se piden los valores máximos y mínimos del espectro
	printf("\n¿En qué espectro del valores quiere buscar?");
	printf("\nMínimo ");
	scanf("%lf", &espectroMinimo);
	printf("\nMáximo ");
	scanf("%lf", &espectroMaximo);

	// Se pide la cantidad de iteraciones que se va a realizar
	// Cantidad de iteraciones = a cantidad de soluciones
	printf("\n¿Cuántas iteraciones de búsqueda desea? ");
	scanf("%i", &iteraciones);

	
	return 0;
}
