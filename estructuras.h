/*
This file is part of P2.

P2 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

P2 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with P2.  If not, see <https://www.gnu.org/licenses/>.
*/
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
