#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define XMIN 0.0
#define XMAX 10.0
#define YMIN 100.0
#define YMAX 500.0
#define XFOLD "X.txt"
#define YFOLD "Y.txt"

// DEFINICION DE LAS FUNCIONES
int guardarMatrices(double **matriz, int filas, int columnas, char *ruta);
void crearMatriz(double **matriz, int filas, int columnas,  double maximo, double minimo);
double** declararMatriz(int filas, int columnas);
void liberarMemoriaMatriz(double** matriz, int filas);

int main()
{
	// Declaración e iniciación de variables
    int s = 10, // Cantidad de salidas 
        m = 10, // Cantidad de entradas
        n = 10, // Empresas que se van a utilizar
        k = 10, // Empresa que se va a analizar
        iteraciones = 10; // Cantidad de iteraciones que se desean hacer

    double espectroMinimo = 10.0, // Valor mínimo a buscar
        espectroMaximo = 15.0, // Valor máximo a buscar
        *theta, // Declaramos el puntero
		**X,
		**Y;

    // Se asigna el tamaño del vector theta
    theta = (double *)malloc(sizeof(double) * n);

    //Se inicia la semilla aleatoria
    srand(time(NULL));

    /* COMIENZA LA PARTE 1 DEL ENUNCIADO */

    // Se piden los datos por pantalla del Usuario

    // Se pide la cantidad de empresas a generar
    /*printf("¿Cuántas empresas se van a utilizar? ");
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
    scanf("%i", &iteraciones);*/

    printf("Cantidad de empresas: %i\n", n);
    printf("Empresa elegida: %i\n", k);
    printf("Espectro maximo: %lf\n", espectroMaximo);
    printf("Espectro minimo: %lf\n", espectroMinimo);
    printf("Cantidad de salidas: %i\n", s);
    printf("Cantidad de entradas: %i\n", m);


    X = declararMatriz(n,m);

	printf("Se crea la matriz X\n");
    crearMatriz(X, n, m, XMAX, XMIN);

    printf("Se guarda la matrix X X\n");
	guardarMatrices(X, n, m,XFOLD);


	Y = declararMatriz(n,s);

    printf("Se crea la matriz Y\n");
    crearMatriz(Y, n, s, YMAX, YMIN);

    printf("Se guarda la matrix Y\n");
	guardarMatrices(Y, n, s,YFOLD);
    

    printf("Se libera la memoria");
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
			for( j = 0; j < columnas-1; j++)
			{
				fprintf( f, "%.2lf, ", matriz[i][j]);	
			}
			
			fprintf( f, "%.2lf\n", matriz[i][j]);
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

void crearMatriz(double **matriz, int filas, int columnas,  double maximo, double minimo){
    int i = 0,
		j = 0;
	double numero = 0;

    for (i=0; i<filas; i++) //para desplazarse por las filas
    {
        for (j=0; j<columnas; j++) //para desplazarse por las columnas
        {
            do {
                numero = (double)rand()/(double)(RAND_MAX/maximo);
            } while(!(numero > minimo && numero < maximo));
			

            matriz[i][j] = numero; //Agrega numero aleatorio a la posicion ij de la matriz

            printf("\t%.2lf", matriz[i][j]); //imprime elemento de la matriz en pantalla
        }
        printf("\n\n"); //para dejar espacios entre filas.
    }
}

double** declararMatriz(int filas, int columnas)
{
	// Puntero auxiliar para declarar la matriz
	double **aux;

	// Variables para iterar
	int i = 0;
	
	aux = (double**) malloc(sizeof(double*)*filas);
	
	for(i = 0; i < filas; i++)
	{
		aux[i] = (double*) malloc(sizeof(double)*columnas);		
	}

	return aux;
}

void liberarMemoriaMatriz(double** matriz, int filas)
{
	int i = 0;

	for(i = 0; i < filas; i++)
	{
		free(matriz[i]);
	}

	free(matriz);
}