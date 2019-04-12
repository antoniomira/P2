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
	// Iteradores
	int i, j, l;
	// Declaración e iniciación de variables
	int s = 0,			 // Cantidad de salidas
		m = 0,			 // Cantidad de entradas
		n = 0,			 // Empresas que se van a utilizar
		k = 0,			 // Empresa que se va a analizar
		iteraciones = 0, // Cantidad de iteraciones que se desean hacer
		valorNegativo = 0;

	double espectroMinimo = 0.0, // Valor mínimo a buscar
		espectroMaximo = 0.0,	// Valor máximo a buscar
		sumatorio = 0.0,
		//*theta, // Declaramos el puntero
		*S1,
		*S2,
		**X,
		**Y;

	res *resultados;

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

	// Se introducen las entradas y salidas
	printf("Introduce la cantidad de salidas ");
	scanf("%i", &s);
	printf("Introduce la cantidad de entradas ");
	scanf("%i", &m);

	// Se pide la cantidad de iteraciones que se va a realizar
	// Cantidad de iteraciones = a cantidad de soluciones
	printf("\n¿Cuántas iteraciones de búsqueda desea? ");
	scanf("%i", &iteraciones);

	// Se reserva memoria a los vectores
	/*S1 = (double *)malloc(sizeof(double) * n);
	S2 = (double *)malloc(sizeof(double) * n);*/
	resultados = (res *)malloc(sizeof(res) * iteraciones);

	X = declararMatriz(n, m);
	Y = declararMatriz(n, s);

	// Las matrices son invariables
	// Se almacenan los valores de la matriz X
	crearMatriz(X, n, m, XMAX, XMIN);

	// Se almacenan los valores de la matriz Y
	crearMatriz(Y, n, s, YMAX, YMIN);

	// Los valores de Theta cambian por cada iteración

	for (l = 0; l < iteraciones; l++)
	{
		printf("=========ITERACION %i=============\n",l);

		resultados[l].numeroSolucion = l;
		resultados[l].numeroEmpresa = k;
		resultados[l].theta = (double *)malloc(sizeof(double) * n);
		resultados[l].S1 = (double *)malloc(sizeof(double) * s);
		resultados[l].S2 = (double *)malloc(sizeof(double) * m);
		resultados[l].restriccionIncumplida = 0;
		rellenarTheta(resultados[l].theta, espectroMinimo, espectroMaximo, n);
		// Se almacenan los valores del vector Theta
		//theta = (double *)malloc(sizeof(double) * n);
		//rellenarTheta(theta, espectroMinimo, espectroMaximo, n);
		printf("Theta acaba de rellenarse bien\n");
		// Se ejecuta el algoritmo
		resultados[l].sumatorioS1 = resultados[l].sumatorioS2 = 0;
		
		// Primera restricción
		for (i = 0; i < s; i++)
		{
			// Se inicializa el sumatorio para cada ecuación
			sumatorio = 0.0;
			// printf("\n\nSumatorio %i: %.5lf",i, sumatorio);
			// Se calcula el sumatorio
			for (j = 0; j < n; j++)
			{
				sumatorio += (Y[j][i] * resultados[l].theta[j]);
				// printf(" + (%.5lf * %.5lf)",Y[j][i], theta[j]);
				// fflush(stdout);
			}
			resultados[l].S1[i] = sumatorio - Y[k][i];
			resultados[l].sumatorioS1+=resultados[l].S1[i];

			if (resultados[l].S1[i] < 0)
			{
				resultados[l].restriccionIncumplida = 1;
			}
			// printf("\nRestriccion%d --> S1[%d] = %.5f - %.5f = %.5f",i,i,sumatorio,Y[k][i],S1[i]);
		}

		// Segunda restricción
		for (i = 0; i < m; i++)
		{
			// Se inicializa el sumatorio para cada ecuación
			sumatorio = 0.0;
			// printf("\n\nSumatorio %i: %.5lf",i, sumatorio);
			// Se calcula el sumatorio
			for (j = 0; j < n; j++)
			{
				sumatorio += (X[j][i] * resultados[l].theta[j]);
				// printf(" + (%.5lf * %.5lf)",Y[j][i], theta[j]);
				// fflush(stdout);
			}
			resultados[l].S2[i] = sumatorio - X[k][i];
			resultados[l].sumatorioS2+=resultados[l].S2[i];

			if (resultados[l].S2[i] < 0)
			{
				resultados[l].restriccionIncumplida = 1;
			}
			// printf("\nRestriccion%d --> S1[%d] = %.5f - %.5f = %.5f",i,i,sumatorio,Y[k][i],S1[i]);
		}

		resultados[l].valorMaximo = resultados[l].sumatorioS2+resultados[l].sumatorioS1;
	}
	
	printf("Antes de quicksort\n");
	quicksort(resultados, 1, iteraciones);

	
	for (l = 0; l < iteraciones; l++)
	{

		printf("Numero de la solucion: %i\n", resultados[l].numeroSolucion);
		printf("Empresa elegida: %i\n", resultados[l].numeroEmpresa);
		printf("Valor sumatorio S1: %.5lf\n", resultados[l].sumatorioS1);
		printf("Valor sumatorio S2: %.5lf\n", resultados[l].sumatorioS2);
		printf("Valor maximo: %.5lf\n", resultados[l].valorMaximo);


		printf("Valor del vector Theta\n");
		for (i = 0; i < n; i++)
		{
			printf("%.5lf  ", resultados[l].theta[i]);
		}
		printf("\n\n");

		printf("Valor del vector S1\n");
		for (i = 0; i < s; i++)
		{
			printf("%.5lf  ", resultados[l].S1[i]);
		}
		printf("\n\n");

		printf("Valor del vector S2\n");
		for (i = 0; i < m; i++)
		{
			printf("%.5lf  ", resultados[l].S2[i]);
		}
		printf("\n\n");
	}

	// Se guardan en disco las matrices
	guardarMatrices(X, n, m, XFOLD);
	guardarMatrices(Y, n, s, YFOLD);

	// Se termina la ejecución y se libera memoria
	//free(S1);
	//free(S2);
	//free(theta);
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
	double numero = 0.0;

	for (i = 0; i < filas; i++) //para desplazarse por las filas
	{
		for (j = 0; j < columnas; j++) //para desplazarse por las columnas
		{
			do
			{
				numero = (double)rand() / (double)(RAND_MAX / maximo);
			} while (!(numero > minimo && numero < maximo));

			matriz[i][j] = numero; //Agrega numero aleatorio a la posicion ij de la matriz
		}
	}
}

double **declararMatriz(int filas, int columnas)
{
	// Puntero auxiliar para declarar la matriz
	double **aux;

	// Variables para iterar
	int i, j;

	aux = (double **)malloc(sizeof(double *) * filas);

	for (i = 0; i < filas; i++)
	{
		//printf("Valor de i: %i", i);
		aux[i] = (double *)malloc(sizeof(double) * columnas);
		for (j = 0; j < columnas; j++)
		{
			aux[i][j] = 0;
		}
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