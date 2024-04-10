/* Luis Daniel Villalobos Ensaldo #368617
Actividad 9   22/03/2024    5/04/2024
Programacion estructurada   gpo:432
1.- LLENAR VECTOR .- V números aleatoriamente, de 100 al 200 (no repetidos)
2.- LLENAR MATRIZ .- 4x4 con números aleatoriamente de 1 al 16  (no repetidos)
3.- IMPRIMIR VECTOR .- Imprime el vector que se envíe, donde la función recibe como parámetro el vector, tamaño, nombre del vector.
4.- IMPRIMIR MATRIZ.-  Imprime la matriz sin importar el tamaño de la matriz recibiendo como parámetros la matriz, la cantidad de renglones y columnas, así como nombre que se le dará a la matriz
5.- ORDENAR VECTOR.- Usar función que ordene el vector por el método de ordenación de la Burbuja mejorada.
6.- BUSCAR VALOR EN VECTOR.-  Buscar un valor en el vector usando el método de búsqueda secuencial.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "luis.h"
#define N 4
#define V 15

//*** PROTOTIPOS DE FUNCIONES  ******
int valinum(int ri, int rf, char msge[]);
int msges();
void menu();
int vectrand(int vect[], int m, int ri, int rf);
int llenarmat(int mat[][N], int m, int n, int ri, int rf);
void printvect(int vect[], int m, char nombre[] = "Vector");
void printmat(int mat[][N], int m, int n, char nombre[] = "Matriz");
int ordvect(int vect[], int m);
int searchvect(int vect[], int m, int num, bool ordenado = 0);

//****  main principal  *********
int main()
{
    srand(time(NULL));
    menu();

    return 0;
}
//  *** DESARROLLO DE LAS FUNCIONES  ******
//*********************
int msges()
{
    int op;
    system("CLS");
    printf("   M  E   N   U \n");
    printf("1.- llenar vector\n");
    printf("2.- llenar matriz\n");
    printf("3.- imprimir vector \n");
    printf("4.- Imprimir matriz \n");
    printf("5.- Ordenar vector\n");
    printf("6.- Buscar valor en vector\n");
    printf("0.- SALIR  \n");
    op = valinum(0, 6, "ESCOGE UNA OPCION: ");
    return op;
}
//****************
void menu()
{
    int op, vect[V], mat[N][N], pos, num;
    bool vector = 0, matriz = 0, orden = 0;
    do
    {
        op = msges();
        switch (op)
        {
        case 1:
            system("CLS");
            vector = vectrand(vect, V, 100, 200);
            printf("Ya se lleno el vector\n");
            orden = 0;
            system("PAUSE");
            break;
        case 2:
            system("CLS");
            matriz = llenarmat(mat, N, N, 1, 16);
            printf("Matriz llenada\n");
            system("PAUSE");
            break;
        case 3:
            system("CLS");
            if (vector)
            {
                printvect(vect, V, "Vector aleatorio");
            }
            else
            {
                printf("No se ha llenado el vector\n");
            }
            system("PAUSE");

            break;
        case 4:
            system("CLS");
            if (matriz)
            {
                printmat(mat, N, N, "Matriz aleatoria");
            }
            else
            {
                printf("No se ha llenado la matriz\n");
            }
            system("PAUSE");

            break;
        case 5:
            system("CLS");
            if (vector)
            {
                orden = ordvect(vect, V);
                printf("Ya se ordeno el vector\n");
            }
            else
            {
                printf("No se ha llenado el vector\n");
            }
            system("PAUSE");

            break;
        case 6:
            system("CLS");
            if (vector)
            {
                num = valinum(100, 200, "Buscar valor entre 100-200:\n");
                pos = searchvect(vect, V, num, orden);
                if (pos == -1)
                {
                    printf("No se encontro el valor\n");
                }
                else
                {
                    printf("El valor esta en la posicion[%d]\n", pos);
                }
            }
            else
            {
                printf("No se ha llenado el vector\n");
            }
            system("PAUSE");

            break;
        }

    } while (op != 0);
}

//*********************
int vectrand(int vect[], int m, int ri, int rf)
{
    //  VARIALES LOCALES
    int rango, num, j, i;
    rango = (rf - ri) + 1;
    //  AQUI DESARROLLO PROGRAMA
    for (i = 0; i < m; i++)
    {
        vect[i] = (rand() % rango) + ri;
        num = vect[i];
        j = 0;
        while (j < i)
        {
            if (num == vect[j])
            {
                i--;
            }
            j++;
        }
    }
    return 1;
}

//*************************
int llenarmat(int mat[][N], int m, int n, int ri, int rf)
{

    //  VARIALES LOCALES
    int rango, compr[m * n], acum = 0, i, j;
    //  AQUI DESARROLLO PROGRAMA
    vectrand(compr, m * n, 1, 16);

    for (i = 0; i < m; i++)
    {
        j = 0;
        while (j < n)
        {
            mat[i][j] = compr[acum];
            acum++;
            j++;
        }
    }
    return 1;
}
//****************************
void printvect(int vect[], int m, char nombre[])
{
    //  VARIALES LOCALES
    //  AQUI DESARROLLO PROGRAMA
    printstr(nombre);
    for (int i = 0; i < m; i++)
    {
        printf("i %d: [%d]\n", (i), vect[i]);
    }

    printf("\n");
}

void printmat(int mat[][N], int m, int n, char nombre[])
{
    //  VARIALES LOCALES
    //  AQUI DESARROLLO PROGRAMA
    printstr(nombre);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("[%d] ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int ordvect(int vect[], int m)
{
    int temp, j;
    for (int i = 0; i < m - 1; i++)
    {
        for (j = i + 1; j < m; j++)
        {
            if (vect[j] < vect[i])
            {
                temp = vect[i];
                vect[i] = vect[j];
                vect[j] = temp;
            }
        }
    }
    return 1;
}

int searchvect(int vect[], int m, int num, bool ordenado)
{
    int i;

    if (ordenado)
    {
        int bajo = 0, centro, alto = m;
        do
        {
            centro = (bajo + alto) / 2;
            if (vect[centro] < num)
            {
                bajo = centro + 1;
            }
            else
            {
                if (vect[centro] == num)
                {
                    return centro;
                }
                else
                {
                    alto = centro - 1;
                }
            }
        } while (alto>bajo);
    }
    else
    {
        for (i = 0; i < m; i++)
        {
            if (vect[i] == num)
            {
                return i;
            }
        }
    }
    return -1;
}
