#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4
#define M 10

//*** PROTOTIPOS DE FUNCIONES  ******
int msges();
void menu();
int valinum(int ri = 0, int rf = 64000, char msge[] = "Numero entero: ");
void vectrand(int vect[], int m, int ri, int rf);
void unirvect(int vacio[], int vect1[], int vect2[], int m);
void llenarmat(int mat[][N], int m, int n, int vect[], int vect2[]);
void printvect(int vect[], int m);
void printmat(int mat[][N], int m, int n);
void vectman(int vect[], int m);

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
    printf("1.- llenar vector manualmente\n");
    printf("2.- llenar vector aleatoriamente\n");
    printf("3.- Llenar vector con los 2 \n");
    printf("4.- imprimir vector \n");
    printf("5.- llenar matriz\n");
    printf("6.- imprimir matriz\n");
    printf("0.- SALIR  \n");
    printf("ESCOGE UNA OPCION: ");
    scanf("%d", &op);
    return op;
}
//****************
void menu()
{
    int op, vect1[M], vect2[M], vect3[M * 2], mat[N][N];
    bool manual = 0, aleatorio = 0, vectores = 0, matriz = 0;
    do
    {
        op = msges();
        switch (op)
        {
        case 1:
            system("CLS");
            printf("   llenar vector manual\n");
            vectman(vect1, M);
            manual = 1;
            break;
        case 2:
            system("CLS");
            printf("   llenar vector aleatorio\n");
            vectrand(vect2, M, 1, 20);
            aleatorio = 1;
            break;
        case 3:
            system("CLS");
            if (manual && aleatorio)
            {
                printf("   llenar vector con 2 anteriores\n");
                unirvect(vect3, vect1, vect2, (M * 2));
                vectores = 1;
            }
            else
            {
                printf("No se han llenado los vectores\n");
                system("PAUSE");
            }
            break;
        case 4:
            system("CLS");
            if (vectores)
            {
                printf("   Imprimir vectores \n Manual:\n");
                printvect(vect1, M);
                printf("   Aleatorio:\n");
                printvect(vect2, M);
                printf("   Unidos:\n");
                printvect(vect3, (2 * M));
            }
            else
            {
                printf("No se han llenado los vectores\n");
                system("PAUSE");
            }
            break;
        case 5:
            system("CLS");
            if (manual && aleatorio)
            {
                printf("   llenar matriz\n");
                llenarmat(mat, N, N, vect1, vect2);
                matriz = 1;
            }
            else
            {
                printf("No se han llenado los vectores\n");
                system("PAUSE");
            }
            break;
        case 6:
            if (matriz)
            {
                printf("   Imprimir matriz \n");
                printmat(mat, N, N);
            }
            else
            {
                printf("No se ha llenado la matriz\n");
                system("PAUSE");
            }
            break;
        }

    } while (op != 0);
}

int valinum(int ri, int rf, char msge[])
{
    char xnum[30];
    int num;
    do
    {
        printf("%s", msge);
        fflush(stdin);
        gets(xnum);
        num = atoi(xnum);
        if (num < ri or num > rf)
        {
            printf("Error\nvalor debe ser entre (%d-%d)\n", ri, rf);
            system("PAUSE");
        }
    } while (num < ri or num > rf);
    return num;
}
//************************
void vectman(int vect[], int m)
{
    //  VARIALES LOCALES
    system("CLS");
    //  AQUI DESARROLLO PROGRAMA
    for (int i = 0; i < m; i++)
    {
        printf("Valor [%d]: ", i);
        vect[i] = valinum(30, 70);
    }

    printf("\n");
    system("PAUSE");
}
//*********************
void vectrand(int vect[], int m, int ri, int rf)
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

    printf("Ya se lleno el vector");

    printf("\n");
    system("PAUSE");
}

//*************************

void unirvect(int vacio[], int vect1[], int vect2[], int m)
{
    //  VARIALES LOCALES
    int i, mitad = (m / 2);
    //  AQUI DESARROLLO PROGRAMA
    for (i = 0; i < mitad; i++)
    {
        vacio[i] = vect1[i];
    }
    while (i < m)
    {
        vacio[i] = vect2[i - mitad];
        i++;
    }
    printf("Ya se lleno el vector");
    printf("\n");
    system("PAUSE");
}
//****************************
void printvect(int vect[], int m)
{
    //  VARIALES LOCALES
    //  AQUI DESARROLLO PROGRAMA
    for (int i = 0; i < m; i++)
    {
        printf("i %d: [%d]\n", (i), vect[i]);
    }

    printf("\n");
    system("PAUSE");
}

void llenarmat(int mat[][N], int m, int n, int vect[], int vect2[])
{

    //  VARIALES LOCALES
    int acum = 0;
    //  AQUI DESARROLLO PROGRAMA
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (acum < 10)
            {
                mat[i][j] = vect[acum];
            }
            else
            {
                mat[i][j] = vect2[acum - M];
            }
            acum++;
        }
    }
    printf("Ya se lleno la matriz\n");
    system("PAUSE");
}

void printmat(int mat[][N], int m, int n)
{
    //  VARIALES LOCALES
    system("CLS");
    //  AQUI DESARROLLO PROGRAMA
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("[%d] ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    system("PAUSE");
}