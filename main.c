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
#define YFOLD "X.txt"
#define YFOLD "Y.txt"

// DEFINICION DE LAS FUNCIONES
int guardarMatrices(double **matriz, int filas, char *ruta);
void crearMatriz(double matriz[10][10], int filas, int columnas, double maximo, double minimo);

int main()
{
    // DECLARACION E INICIALIZACION DE VARIABLES
    int s = 10,          // Cantidad de salidas
        m = 10,          // Cantidad de entradas
        n = 0,           // Empresas que se van a utilizar
        k = 0,           // Empresa que se va a analizar
        iteraciones = 0; // Cantidad de iteraciones que se desean hacer

    double espectroMinimo = 0.0, // Valor mínimo a buscar
        espectroMaximo = 0.0,    // Valor máximo a buscar
        *theta;                  // Declaramos el puntero

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

    // zona martin
    //zona ximo
    double matriz[10][10];
    crearMatriz(matriz, n, m, espectroMaximo, espectroMinimo);

    return 0;
}

// FUNCION GUARDAR MATRICES
int guardarMatrices(double **matriz, int filas, char *ruta)
{
    // DECLARACION E INICIALIZACION DE MEMORIA
    FILE *f;
    int i = 0;

    // ABRO EL FICHERO
    f = fopen(ruta, "wb");
    if (f == NULL)
    {
        printf("ERROR, el fichero no existe o no se ha podido abrir\n");
        return -1;
    }
    else
    {
        // GRABO LINIEA A LINEA LA MATRIZ
        for (i = 0; i < filas; ++i)
        {
            fwrite(ruta[i], sizeof(double), filas, f);
        }
    }

    // CIERRO EL FICHERO
    if (fclose(f))
    {
        printf("Error: fichero NO CERRADO\n");
        return 1;
    }
}

void crearMatriz(double matriz[10][10], int filas, int columnas, double maximo, double minimo)
{
    double numero = 0;

    for (int i = 0; i < columnas; i++) //para desplazarse por las columnas
    {
        for (int j = 0; j < filas; j++) //para desplazarse por las filas
        {
            numero = (double)rand() / (double)(RAND_MAX / maximo);

            while (numero < minimo || numero > maximo)
            {
                numero = (double)rand() / (double)(RAND_MAX / maximo);
            }

            matriz[i][j] = numero; //Agrega numero aleatorio a la posicion ij de la matriz

            printf("\t%.2lf", matriz[i][j]); //imprime elemento de la matriz en pantalla
        }
        printf("\n\n"); //para dejar espacios entre filas.
    }
}