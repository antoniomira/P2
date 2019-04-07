typedef struct resultado
{
    int numeroSolucion;
    int numeroEmpresa;
    double *theta;
    double valorMaximo;
    double *S1;
    double *S2;
    double sumatorioS1;
    double sumatorioS2;
    int restriccionIncumplida;
} res;

void quicksort(res *V, int izq, int der);
int seleccionar_pivote(res *V, int izq, int der);
void intercambiar(res *V, int i, int d);
