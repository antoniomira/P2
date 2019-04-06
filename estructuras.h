typedef struct resultado
{
    int numeroSolucion;
    int numeroEmpresa;
    double valorMaximo;
    double *S1;
    double *S2;
} res;

void quicksort(res *V, int izq, int der);
int seleccionar_pivote(res *V, int izq, int der);
void intercambiar(res *V, int i, int d);
