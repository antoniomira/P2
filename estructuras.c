#include "estructuras.h"

// FUNCION QUICKSORT
void quicksort(res *V, int izq, int der)
{
    // DECLARAMOS E INICIALIZAMOS LAS VARIABLES
    int i = 0, d = 0, p = 0;
    double pivote = 0;

    // CALCULAMOS EL PIVOTE
    p = seleccionar_pivote(V, izq, der);

    if (p > 0)
    {
        pivote = V[p].valorMaximo;
        i = izq;
        d = der;

        while (i <= d)
        {
            while (V[i].valorMaximo > pivote)
                i++;

            while (V[d].valorMaximo < pivote)
                d--;

            if (i <= d)
            {
                intercambiar(V, i, d); // TENGO QUE PASARLE EL VALOR DEL ARRAY
                i++;
                d--;
            }
        }

        if (izq < d)
            quicksort(V, izq, d);

        if (i < der)
            quicksort(V, i, der);
    }
}

// FUNCION SELECCIONAR PIVOTE
int seleccionar_pivote(res *V, int izq, int der)
{
    // DECLARAMOS E INICIALIZAMOS LAS VARIABLES
    int medio = 0;

    // CALCULO EL MEDIO DEL VECTOR
    if (der % 2 != 0)
        medio = V[(izq + der) / 2 + 1].valorMaximo;
    else
        medio = V[(izq + der) / 2].valorMaximo;

    // CALCULAMOS EL PIVOTE
    if ((izq <= V[medio].valorMaximo && V[medio].valorMaximo <= der) || (der <= V[medio].valorMaximo && V[medio].valorMaximo <= izq))
        return V[medio].valorMaximo;

    if ((der <= izq && izq <= V[medio].valorMaximo) || (V[medio].valorMaximo <= izq && izq <= der))
        return izq;

    if ((V[medio].valorMaximo <= der && der <= izq) || (izq <= der && der <= V[medio].valorMaximo))
        return der;

    return 0;
}

// FUNCION INTERCAMBIAR PUNTEROS
void intercambiar(res *V, int i, int d)
{
    // DECLARAMOS E INICIALIZAMOS LAS VARIABLES
    res a, b;

    // COPIAMOS LOS VALORES EN DOS VARIABLES DISTINTAS
    a = V[i];
    b = V[d];

    // INTERCAMBIAMOS EL VALOR DE LA POSICION i por d DEL VECTOR V
    V[i] = b;
    V[d] = a;
}