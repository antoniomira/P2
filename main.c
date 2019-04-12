#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estructuras.h"

#define XMIN 0.0
#define XMAX 10.0
#define YMIN 100.0
#define YMAX 500.0
#define XFOLD "X.txt"
#define YFOLD "Y.txt"

// DEFINICION DE LAS FUNCIONES
int guardarMatrices(double **matriz, int filas, int columnas, char *ruta);
void crearMatriz(double **matriz, int filas, int columnas, double maximo, double minimo);
double **declararMatriz(int filas, int columnas);
void liberarMemoriaMatriz(double **matriz, int filas);
void rellenarTheta(double *theta, double minimo, double maximo, int tamano);

int main()
{
	res resultado;
	double *vector1, *vector2, valorMaximo = 0;
	int i = 0, j = 0, random1 = 0, random2 = 0;
	srand(time(NULL));

	// RESERVAMOS MEMORIA
	res *resultados = (res *)malloc(20 * sizeof(res));

	resultado.numeroEmpresa = 2;
	resultado.numeroSolucion = 5;
	resultado.S1 = vector1;
	resultado.S2 = vector2;
	resultado.valorMaximo = 22.3;

	for (i = 0; i < 20; i++)
	{
		resultados[i].numeroEmpresa = i;
		resultados[i].numeroSolucion = i;
		resultados[i].S1 = (double *)malloc(20 * sizeof(double));
		resultados[i].S2 = (double *)malloc(20 * sizeof(double));
		for (j = 0; j < 20; j++)
		{
			random1 = rand() % 9 + 1;
			random2 = rand() % 9 + 1;
			resultados[i].S1[j] = random1;
			resultados[i].S2[j] = random2;
			valorMaximo += random1 + random2;
		}
		resultados[i].valorMaximo = valorMaximo;
		valorMaximo = 0;
		printf("Empresa %i \nNumero de la solucion %i \nValor maximo %.2lf \n\n", resultados[i].numeroEmpresa, resultados[i].numeroSolucion, resultados[i].valorMaximo);
	}

	quicksort(resultados, 0, 19);

	printf("############################### Resultado de la ordenacion ######################\n");
	for (i = 0; i < 20; i++)
	{
		printf("Empresa %i \nNumero de la solucion %i \nValor maximo %.2lf \n\n", resultados[i].numeroEmpresa, resultados[i].numeroSolucion, resultados[i].valorMaximo);
		// printf("%i ", vector[i]);
	}
	printf("\n");

	return 0;
}

int main1()
{
	// Declaración e iniciación de variables
	int s = 10,			 // Cantidad de salidas
		m = 10,			 // Cantidad de entradas
		n = 10,			 // Empresas que se van a utilizar
		k = 0,			 // Empresa que se va a analizar
		iteraciones = 0; // Cantidad de iteraciones que se desean hacer

	double espectroMinimo = 0.0, // Valor mínimo a buscar
		espectroMaximo = 0.0,	// Valor máximo a buscar
		*theta,					 // Declaramos el puntero
		**X,
		   **Y;

	// Se asigna el tamaño del vector theta
	theta = (double *)malloc(sizeof(double) * n);

	//Se inicia la semilla aleatoria
	srand(time(NULL));

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
	X = declararMatriz(n, m);

	// Se introducen las entradas y salidas
	printf("Introduce la cantidad de salidas ");
	scanf("%i", &s);
	printf("Introduce la cantidad de entradas ");
	scanf("%i", &m);

	// Se pide la cantidad de iteraciones que se va a realizar
	// Cantidad de iteraciones = a cantidad de soluciones
	printf("\n¿Cuántas iteraciones de búsqueda desea? ");
	scanf("%i", &iteraciones);
	X = declararMatriz(n, m);

	rellenarTheta(theta, espectroMinimo, espectroMaximo, n);

	// printf("Llega aqui");
	crearMatriz(X, n, m, XMAX, XMIN);

	guardarMatrices(X, n, m, XFOLD);

	Y = declararMatriz(n, s);
	crearMatriz(Y, n, s, YMAX, YMIN);

	guardarMatrices(Y, n, s, YFOLD);

	liberarMemoriaMatriz(X, n);
	liberarMemoriaMatriz(Y, n);

	return 0;
}

// FUNCION GUARDAR MATRICES
int guardarMatrices(double **matriz, int filas, int columnas, char *ruta)
{
	// DECLARACION E INICIALIZACION DE MEMORIA
	FILE *f;
	int i = 0,
		j = 0;

	// ABRO EL FICHERO
	f = fopen(ruta, "w");
	if (f == NULL)
	{
		printf("ERROR, el fichero no existe o no se ha podido abrir\n");
		return -1;
	}
	else
	{
		// GRABO LINEA A LINEA LA MATRIZ
		for (i = 0; i < filas; ++i)
		{
			for (j = 0; j < columnas - 1; j++)
			{
				fprintf(f, "%.2lf, ", matriz[i][j]);
			}

			fprintf(f, "%.2lf\n", matriz[i][j]);
			// fwrite(matriz[i], sizeof(double),columnas, f);
		}
	}

	// CIERRO EL FICHERO
	if (fclose(f))
	{
		printf("Error: fichero NO CERRADO\n");
		return 1;
	}
	return 0;
}

void crearMatriz(double **matriz, int filas, int columnas, double maximo, double minimo)
{
	int i = 0,
		j = 0;
	double numero = 0;

	for (i = 0; i < filas; i++) //para desplazarse por las filas
	{
		for (j = 0; j < columnas; j++) //para desplazarse por las columnas
		{
			do
			{
				numero = (double)rand() / (double)(RAND_MAX / maximo);
			} while (!(numero > minimo && numero < maximo));

			matriz[i][j] = numero; //Agrega numero aleatorio a la posicion ij de la matriz

			printf("\t%.2lf", matriz[i][j]); //imprime elemento de la matriz en pantalla
		}
		printf("\n\n"); //para dejar espacios entre filas.
	}
}

double **declararMatriz(int filas, int columnas)
{
	// Puntero auxiliar para declarar la matriz
	double **aux;

	// Variables para iterar
	int i = 0;

	aux = (double **)malloc(sizeof(double *) * filas);

	for (i = 0; i < filas; i++)
	{
		aux[i] = (double *)malloc(sizeof(double) * columnas);
	}

	return aux;
}

void liberarMemoriaMatriz(double **matriz, int filas)
{
	int i = 0;

	for (i = 0; i < filas; i++)
	{
		free(matriz[i]);
	}

	free(matriz);
}

void rellenarTheta(double *theta, double minimo, double maximo, int tamano)
{
	int i = 0;
	double numero = 0;
	// printf("THETA: ");
	for (i = 0; i < tamano; i++)
	{
		do
		{
			numero = (double)rand() / (double)(RAND_MAX / maximo);
		} while (!(numero > minimo && numero < maximo));

		theta[i] = numero; //Agrega numero aleatorio a la posicion i del vector

		printf("\t%.2lf ", theta[i]); //imprime elemento del vector en pantalla
	}
	printf("\n\n");
}