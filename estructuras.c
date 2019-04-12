#include "estructuras.h"
#include <stdio.h>

// FUNCION QUICKSORT
void quicksort(res *V, int izq, int der)
{

    // DECLARAMOS E INICIALIZAMOS LAS VARIABLES
    int i = 0, d = 0, p = 0;
    double pivote = 0.0;

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
        medio = (izq + der) / 2 + 1;
    else
        medio = (izq + der) / 2;

    
    // CALCULAMOS EL PIVOTE
    if ((izq <= medio && medio <= der) || (der <= medio && medio <= izq))
        return medio;

    if ((der <= izq && izq <= medio) || (medio <= izq && izq <= der))
        return izq;

    if ((medio <= der && der <= izq) || (izq <= der && der <= medio))
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