/* Luis Daniel Villalobos Ensaldo #368617
Actividad 13   17/05/2024    20/05/2024
Programacion estructurada   gpo:432
1.- AGREGAR (AUTOM 100 REGISTROS)
2.- EDITAR REGISTRO
3.- ELIMINAR REGISTRO (lógico)
4.- BUSCAR
5.- ORDENAR
6- IMPRIMIR
7.- GENERAR ARCHIVO TEXTO
8.- VER ARCHIVO TEXTO
9.- CREAR ARCH BINARIO
10.- CARGAR ARCH BINARIO
11.- MOSTRAR ELIMINADOS
*/
#include <stdio.h>
#include <stdlib.h>
#include "luis.h"
#include <string.h>
// cantidad de registros automaticos
#define N 100
// regsitros maximos
#define M 5000
typedef struct _talum
{
    int status;
    long matricula;
    char appat[20];
    char apmat[20];
    char nombre[20];
    int edad;
    char sexo[10];
} Talum;

//*** PROTOTIPOS DE FUNCIONES  ******
int msges();
void menu();
void QuickSort(Talum regis[], int men, int may);
int Dividir(Talum regis[], int men, int may);
void Print_reg(Talum registros, int pos);
int Cargar_bin(Talum vect[], int m, int reg_act);
Talum Generar_reg(Talum registros[], int m);
void Gen_Arch(Talum registros[], int m);
int Buscar(Talum registros[], int m, int matri, short ordenado = 0);
int Case_4(Talum registros[], int m, short ordenado = 0);
short Ediciones(Talum registros[], int m, int pos, int op, short ordenado);
void Eliminar(Talum registros[], int m, short ordenado = 0);
int Ordenar(Talum registros[], int m, short ordenado);
void Mostrar_todo(Talum registros[], int m);
short Editar_reg(Talum registros[], int m, short ordenado);
void Printtxt(void);
void Crear_bin(Talum registros[], int m);
void Eliminados(void);
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
    printf("1.- Agregar \n");
    printf("2.- Editar registro \n");
    printf("3.- Eliminar Registro \n");
    printf("4.- Buscar \n");
    printf("5.- Ordenar \n");
    printf("6.- Imprimir \n");
    printf("7.- Generar Archivo \n");
    printf("8.- Ver archivo \n");
    printf("9.- Generar binario \n");
    printf("10.- Cargar binario \n");
    printf("11.- Mostrar eliminados \n");
    printf("0.- SALIR  \n");
    op = valinum(0, 11, "ESCOGE UNA OPCION: ");

    return op;
}
void menu()
{
    int op, no_reg = 0, nuev_reg = 0;
    short ordenado = 0;
    bool binario = 0;
    Talum registros[M];
    do
    {
        op = msges();
        switch (op)
        {
        case 1:
        {
            system("CLS");

            if (no_reg <= (M - N))
            {
                for (int i = 0; i < N; i++)
                {
                    registros[no_reg] = Generar_reg(registros, no_reg);
                    no_reg++;
                }
                nuev_reg += N;
                if (nuev_reg > (no_reg * .10))
                {
                    ordenado = 0;
                }
                else
                {
                    ordenado = 2;
                }
                printf("Se han agregado %d registros\n", N);
            }
            else
            {
                printf("No caben mas registros");
            }
            system("PAUSE");
            break;
        }
        case 2:
            ordenado = Editar_reg(registros, no_reg, ordenado);
            break;
        case 3:
            system("CLS");
            Eliminar(registros, no_reg, ordenado);
            system("PAUSE");

            break;
        case 4:
            Case_4(registros, no_reg, ordenado);
            break;
        case 5:
            system("CLS");
            if (ordenado == 1)
            {
                printf("Ya esta ordenado\n");
            }
            else
            {
                ordenado = Ordenar(registros, no_reg, ordenado);
                nuev_reg = 0;
                printf("Se ha ordenado\n");
            }
            system("PAUSE");
            break;
        case 6:
            system("CLS");
            Mostrar_todo(registros, no_reg);
            system("PAUSE");
            break;
        case 7:
            if (no_reg == 0)
            {
                printf("Todavia no hay registros\n");
                system("PAUSE");
            }
            else
            {
                Gen_Arch(registros, no_reg);
            }
            break;
        case 8:
            Printtxt();
            break;
        case 9:
            if (no_reg == 0)
            {
                printf("Todavia no hay registros\n");
                system("PAUSE");
            }
            else
            {
                Crear_bin(registros, no_reg);
            }
            break;
        case 10:
            if (binario)
            {
                printf("Solo se puede cargar una vez\n");
            }
            else
            {
                no_reg += Cargar_bin(registros, (M - no_reg), no_reg);
                binario = 1;
            }
            break;
        case 11:
            Eliminados();
            break;
        }

    } while (op != 0);
}
// Ordenacion*********************
void Merge(Talum regis[], int izq, int mitad, int ult)
{
    int i, j, k;
    int n1 = mitad - izq + 1;
    int n2 = ult - mitad;

    Talum L[n1], R[n2];

    for (i = 0; i < n1; ++i)
        L[i] = regis[izq + i];
    for (j = 0; j < n2; ++j)
        R[j] = regis[mitad + 1 + j];
    i = 0;
    j = 0;
    k = izq;

    while (i < n1 && j < n2)
    {
        if (L[i].matricula <= R[j].matricula)
        {
            regis[k] = L[i];
            ++i;
        }
        else
        {
            regis[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        regis[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        regis[k] = R[j];
        ++j;
        ++k;
    }
}
void MergeSort(Talum regis[], int izq, int ult)
{
    if (izq < ult)
    {
        int mitad = izq + (ult - izq) / 2;
        MergeSort(regis, izq, mitad);
        MergeSort(regis, mitad + 1, ult);
        Merge(regis, izq, mitad, ult);
    }
}
int Dividir(Talum regis[], int men, int may)
{
    long pivote = regis[may].matricula;
    int i = (men - 1);

    for (int j = men; j <= may - 1; j++)
    {
        if (regis[j].matricula < pivote)
        {
            i++;
            // cambiar
            Talum temp = regis[i];
            regis[i] = regis[j];
            regis[j] = temp;
        }
    }
    // cambiar pivote con el elemento en i+1
    Talum temp = regis[i + 1];
    regis[i + 1] = regis[may];
    regis[may] = temp;

    return (i + 1);
}
void QuickSort(Talum regis[], int men, int may)
{
    if (men < may)
    {
        int pi = Dividir(regis, men, may);
        QuickSort(regis, men, pi - 1);
        QuickSort(regis, pi + 1, may);
    }
}
//*********************
Talum Generar_reg(Talum registros[], int m)
{
    Talum reg;
    reg.status = 1;
    char nombres[20][20] = {"JUAN", "LUIS", "DANIEL", "SAUL", "JACOB", "ANGEL", "ALAN", "YAHIR", "GABRIEL", "ISRAEL", "WALTER"};
    char mujeres[20][20] = {"ANGELA", "SOFIA", "VIVIANA", "ANA", "MARIA", "PAOLA", "PAULA", "SONIA", "VANESSA", "HANNA", "LOLA"};
    char appat[20][20] = {"SOTO", "VILLALOBOS", "VICTORIO", "PEREZ", "PINEDA", "HERNANDEZ", "LEAL", "ESPINOZA", "IBARRA", "DIAZ", "DOMINGUEZ", "MARTINEZ"};
    char apmat[20][20] = {"WAYNE", "CRUZ", "CHAVEZ", "CARMINE", "RUIZ", "ORTIZ", "TORRES", "OROZCO", "GARCIA", "PAREDES", "ACOSTA", "CASAS"};
    int sexo;
    reg.edad = (rand() % 12) + 18;

    copystr(reg.appat, appat[rand() % 12]);
    copystr(reg.apmat, apmat[rand() % 12]);
    sexo = (rand() % 2) + 1;
    if (sexo == 1)
    {
        copystr(reg.sexo, "HOMBRE");
        copystr(reg.nombre, nombres[rand() % 11]);
    }
    else
    {
        copystr(reg.sexo, "MUJER");
        copystr(reg.nombre, mujeres[rand() % 11]);
    }
    int resul;
    do
    {
        reg.matricula = (rand() % 99999) + 300000;
        resul = Buscar(registros, m, reg.matricula);
    } while (resul != -1);

    return reg;
}
int Buscar(Talum registros[], int m, int matri, short ordenado)
{
    int i;
    if (ordenado == 1)
    {
        int bajo = 0, centro, alto = m - 1;
        do
        {
            centro = (bajo + alto) / 2;
            if (registros[centro].matricula < matri)
            {
                bajo = centro + 1;
            }
            else
            {
                if (registros[centro].matricula == matri)
                {
                    return centro;
                }
                else
                {
                    alto = centro - 1;
                }
            }
        } while (alto >= bajo);
    }
    else
    {
        for (i = 0; i < m; i++)
        {
            if (registros[i].matricula == matri)
            {
                return i;
            }
        }
    }
    return -1;
}
short Editar_reg(Talum registros[], int m, short ordenado)
{
    system("CLS");
    int pos, op = -1;
    pos = Case_4(registros, m, ordenado);
    if (pos != -1 && registros[pos].status != 0)
    {
        do
        {
            printf("Que quiere editar?\n");
            printf("(1)Matricula\n(2)Nombre\n(3)Apellido\n(4)2do Apellido\n");
            printf("(5)Edad\n(6)Sexo\n(7)Eliminar\n(0)Cancelar\n");
            op = valinum(0, 7, "Escoja opcion: ");
            ordenado = Ediciones(registros, m, pos, op, ordenado);
            printf("Registro actualizado:\n");
            Print_reg(registros[pos], pos);
        } while (op != 0);
        system("PAUSE");
    }
    else
    {
        if (registros[pos].status == 0)
        {
            printf("Solo se pueden editar registros activos\n");
            system("PAUSE");
        }
    }
    return ordenado;
}
short Ediciones(Talum registros[], int m, int pos, int op, short ordenado)
{
    char nombre[20];
    switch (op)
    {
    case 1:
        long matri;
        short resul;
        printf("          MATRICULA\n");
        do
        {
            matri = valilong(300000, 399999, "Nueva matricula: ");
            // validar que no se repita la matricula
            resul = Buscar(registros, m, matri, ordenado);
            if (resul != -1)
            {
                printf("Matricula ya usada\n");
            }
        } while (resul != -1);
        registros[pos].matricula = matri;
        ordenado = 2;
        break;
    case 2:
        printf("          NOMBRE\n");
        strscan(nombre, "Ingrese nuevo nombre: ");
        valichar(nombre);
        copystr(registros[pos].nombre, nombre);
        break;
    case 3:
        printf("          APELLIDO\n");
        strscan(nombre, "Ingrese nuevo nombre: ");
        valichar(nombre);
        copystr(registros[pos].appat, nombre);
        break;
    case 4:
        printf("          2do APELLIDO\n");
        strscan(nombre, "Ingrese nuevo nombre: ");
        valichar(nombre);
        copystr(registros[pos].apmat, nombre);
        break;
    case 5:
        int edad;
        printf("          EDAD\n");
        edad = valinum(1, 90, "Ingrese nueva edad: ");
        registros[pos].edad = edad;
        break;
    case 6:
        bool sex;
        printf("          SEXO\n");
        sex = valinum(0, 1, "(1)Hombre\n(0)Mujer\nEscoja sexo: ");
        if (sex)
        {
            copystr(registros[pos].sexo, "HOMBRE");
        }
        else
        {
            copystr(registros[pos].sexo, "MUJER");
        }
        break;
    case 7:
        bool eliminar;
        printf("          ELIMINAR\n");
        eliminar = valinum(0, 1, "(0)Cancelar\n(1)Eliminar\nSeleccione: ");
        if (eliminar)
        {
            registros[pos].status = 0;
            printf("Se elimino el registro\n");
        }
        else
        {
            printf("Cancelando\n");
        }
        break;
    }
    return ordenado;
}
int Case_4(Talum registros[], int m, short ordenado)
{
    system("CLS");
    int num, resul;
    num = valilong(300000, 399999, "Matricula que busca: ");
    resul = Buscar(registros, m, num, ordenado);
    if (resul == -1)
    {
        printf("No se encontro la matricula\n");
    }
    else
    {
        printf("La matricula esta en: %d\n", (resul));
        Print_reg(registros[resul], resul);
    }
    system("PAUSE");
    return resul;
}
void Eliminar(Talum registros[], int m, short ordenado)
{
    long num;
    int resul;
    bool eliminar;

    num = valilong(300000, 399999, "Matricula que busca: ");
    resul = Buscar(registros, m, num, ordenado);
    if (resul == -1)
    {
        printf("No se encontro la matricula\n");
    }
    else
    {
        printf("La matricula esta en: %d\n", (resul));
        Print_reg(registros[resul], resul);
        eliminar = valinum(0, 1, "(0)Cancelar\n(1)Eliminar\nSeleccione: ");
        if (eliminar)
        {
            registros[resul].status = 0;
            printf("Se elimino el registro\n");
        }
        else
        {
            printf("Cancelando\n");
        }
    }
}
int Ordenar(Talum registros[], int m, short ordenado)
{
    int j;
    Talum temp;
    if (ordenado)
    {
        if (ordenado == 2) // mas o menos desordenado
        {
            MergeSort(registros, 0, m - 1);
        }
        else
        {
            for (int i = 0; i < m - 1; i++)
            {
                for (j = i + 1; j < m; j++)
                {
                    if (registros[j].matricula < registros[i].matricula)
                    {
                        temp = registros[i];
                        registros[i] = registros[j];
                        registros[j] = temp;
                    }
                }
            }
        }
    }
    else
    {
        QuickSort(registros, 0, m - 1);
    }
    return 1;
}
void Mostrar_todo(Talum registros[], int m)
{
    for (int i = 0; i < m; i++)
    {
        if (registros[i].status == 1)
        {
            Print_reg(registros[i], i);
        }
    }
}
void Print_reg(Talum registros, int pos)
{
    printf("No.   Matricula  Nombre   Apellidos               Edad    Sexo\n");
    printf("%3d.- %6ld %10s %10s %10s %8d %8s\n", pos, registros.matricula, registros.nombre, registros.appat, registros.apmat, registros.edad, registros.sexo);
}
// funciones de archivos****************************
void Gen_Arch(Talum registros[], int m)
{
    char nombre[20];
    system("CLS");
    strscan(nombre, "Escriba el nombre del archivo: ");
    /* printf("Escriba el nombre del archivo: ");
     fflush(stdin);
     gets(nombre);*/
    valichar(nombre, "Intenta otro nombre: ");
    // concatenar nombre con txt
    strcat(nombre, ".txt");
    FILE *archivo = fopen(nombre, "w");
    if (archivo)
    {
        // Escribir en el archivo
        for (int i = 0; i < m; i++)
        {
            if (registros[i].status == 1)
            {
                fprintf(archivo, "%3d.- %6ld%10s%10s%10s%3d%8s\n", (i), registros[i].matricula, registros[i].nombre, registros[i].appat, registros[i].apmat, registros[i].edad, registros[i].sexo);
            }
        }
        printf("Se ha escrito el archivo\n");
    }
    fclose(archivo);
    printf("Se ha escrito el archivo\n");
    system("PAUSE");
}
void Printtxt(void)
{
    system("CLS");
    int caracter;
    char nombre[20];
    strscan(nombre, "Archivo a leer: ");
    valichar(nombre);
    strcat(nombre, ".txt");
    FILE *arch;
    arch = fopen(nombre, "r");
    if (arch)
    {
        while ((caracter = fgetc(arch)) != EOF)
        {
            putchar(caracter);
        }
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }
    system("PAUSE");
}
void Crear_bin(Talum registros[], int m)
{
    system("CLS");
    Talum reg;
    FILE *fa;
    FILE *arch;
    fa = fopen("datos.dll", "r+b");
    arch = fopen("datos.tmp", "w+b");
    if (fa)
    {
        // leer
        while (fread(&reg, sizeof(Talum), 1, fa))
        {
            fwrite(&reg, sizeof(Talum), 1, arch);
        }
        fclose(fa);
        fclose(arch);
        printf("Se ha respaldado el archivo\n");
    }
    else
    {
        printf("No se puede respaldar el archivo\n");
    }
    // sobreescribir
    fa = fopen("datos.dll", "w+b");
    if (fa)
    {
        for (int i = 0; i < m; i++)
        {
            reg = registros[i];
            fwrite(&reg, sizeof(Talum), 1, fa);
        }
        fclose(fa);
        printf("Se ha escrito el archivo\n");
    }
    system("PAUSE");
}
int Cargar_bin(Talum vect[], int m, int reg_act)
{
    system("CLS");
    Talum reg;
    FILE *fa;
    int i = reg_act;
    if (valinum(0, 1, "1 tmp 0 dll\n"))
    {
        fa = fopen("datos.tmp", "r+b");
    }
    else
    {
        fa = fopen("datos.dll", "r+b");
    }
    if (fa)
    {
        while (fread(&reg, sizeof(Talum), 1, fa) && i < m)
        {
            vect[i++] = reg;
        }
        fclose(fa);
        printf("Se ha cargado el archivo\n");
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }
    system("PAUSE");
    return i;
}
void Eliminados(void)
{
    system("CLS");
    int i = 0;
    bool elim = 1;
    Talum reg;
    FILE *fa;
    fa = fopen("datos.dll", "r+b");
    if (fa)
    {
        while (fread(&reg, sizeof(Talum), 1, fa))
        {
            if (reg.status == 0)
            {
                Print_reg(reg, i);
                elim = 0;
            }
            i++;
        }
        fclose(fa);
        if (elim)
        {
            printf("No hay registros eliminados\n");
        }
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }
    system("PAUSE");
}