#include "luis.h"
#include <cstring>
#include <stdlib.h>
#include <time.h>
void Curp(char curp[], char nombre[], char appat[], char apmat[], int sex, int estado, int anio, int mes, int dia);
void Compuestos(char nombre[]);
void Vocales(char palabra[]);
void Consonantes(char palabra[]);
void Nombres(char nombre[], char appat[], char apmat[]);
void Vali_Nombres(char curp[], char nombre[], char appat[], char apmat[]);
void Nacimiento(char curp[], int anio, int mes, int dia);
void Sexo(char curp[], int sex);
void Estado(char curp[], int estado);
void Antison(char curp[]);

void Curp(char curp[], char nombre[], char appat[], char apmat[], int sex, int estado, int anio, int mes, int dia)
{
    // digitos 1-4 y 14-16
    Vali_Nombres(curp, nombre, appat, apmat);
    // digitos 5-10 y 17
    Nacimiento(curp, anio, mes, dia);
    // digito 11
    Sexo(curp, sex);
    // digitos 12 y 13
    Estado(curp, estado);
    // Homoclave digito 18
    curp[17] = '0' + (rand() % 5) + 1;
    curp[18] = '\0';
    Antison(curp);
}

// funcion para nombres compuestos
void Compuestos(char nombre[])
{
    char invalido[19][5] = {"DA ", "DAS ", "DE ", "DEL ", "DER ", "DI ", "DIE ", "DD ", "Y ", "EL ", "LA ", "LOS ", "LAS ", "LE ", "LES ", "MAC ", "MC ", "VAN ", "VON "};
    int i, j, tam;
    bool comp = 0;
    char copia[30];
    for (i = 0; i <= 18; i++)
    {
        tam = tamstr(invalido[i]);
        comp = 0;
        if (tam >= 3)
        {
            if (tam == 4)
            {
                if (nombre[0] == invalido[i][0] && nombre[1] == invalido[i][1] && nombre[2] == invalido[i][2] && nombre[3] == invalido[i][3])
                {
                    comp = 1;
                }
            }
            else
            {
                if (nombre[0] == invalido[i][0] && nombre[1] == invalido[i][1] && nombre[2] == invalido[i][2])
                {
                    comp = 1;
                }
            }
        }
        else
        {
            if (nombre[0] == invalido[i][0] && nombre[1] == invalido[i][1])
            {
                comp = 1;
            }
        }
        if (comp)
        {
            copystr(copia, nombre);
            for (j = tam; copia[j] != '\0'; j++)
            {
                nombre[j - tam] = copia[j];
            }
            nombre[j - tam] = '\0';
            i = 0;
        }
    }
}
void Vocales(char palabra[])
{
    int acum = 0;
    upcstr(palabra);
    for (int i = 0; palabra[i] != '\0'; i++)
    {

        if (palabra[i] == 'A' or palabra[i] == 'E' or palabra[i] == 'I' or palabra[i] == 'O' or palabra[i] == 'U')
        {
            palabra[acum] = palabra[i];
            acum++;
        }
        else
        {
            if (palabra[i] == '/' or palabra[i] == '.' or palabra[i] == '-' or palabra[i] == '´')
            {
                if (palabra[i + 1] == 'A' or palabra[i + 1] == 'E' or palabra[i + 1] == 'I' or palabra[i + 1] == 'O' or palabra[i + 1] == 'U')
                {
                    palabra[acum] = 'X';
                    acum++;
                }
            }
        }
    }
    palabra[acum] = '\0';
}
void Consonantes(char palabra[])
{
    int acum = 0;
    upcstr(palabra);
    for (int i = 0; palabra[i] != '\0'; i++)
    {
        if (palabra[i] != 'A' && palabra[i] != 'E' && palabra[i] != 'I' && palabra[i] != 'O' && palabra[i] != 'U')
        {
            if (palabra[i] == 47 or palabra[i] == 45 or palabra[i] == 46 or palabra[i] == 39)
            {
                palabra[acum] = 'X';
            }
            else
            {
                palabra[acum] = palabra[i];
            }
            acum++;
        }
    }
    palabra[acum] = '\0';
}
// funcion para tomar nombres y pasar a mayusculas
void Nombres(char nombre[], char appat[], char apmat[])
{
    int i;
    char copia[30];

    if (nombre[0] == 'M' && nombre[1] == 'A' && nombre[2] == 'R' && nombre[3] == 'I' && nombre[4] == 'A' && nombre[5] == ' ')
    {
        copystr(copia, nombre);
        for (i = 6; copia[i] != '\0'; i++)
        {
            nombre[i - 6] = copia[i];
        }
        nombre[i - 6] = '\0';
    }
    else
    {
        if (nombre[0] == 'J' && nombre[1] == 'O' && nombre[2] == 'S' && nombre[3] == 'E' && nombre[4] == ' ')
        {
            copystr(copia, nombre);
            for (i = 5; copia[i] != '\0'; i++)
            {
                nombre[i - 5] = copia[i];
            }
            nombre[i - 5] = '\0';
        }
    }
    Compuestos(nombre);
    Compuestos(appat);
    Compuestos(apmat);
}
void Vali_Nombres(char curp[], char nombre[], char appat[], char apmat[])
{
    char copia[20];
    Nombres(nombre, appat, apmat);
    // primera letra del apellido
    if (appat[0] == 47 or appat[0] == 45 or appat[0] == 46 or appat[0] == 39)
    {
        curp[0] = 'X';
    }
    else
    {
        curp[0] = appat[0];
    }
    // primera vocal del apellido
    copystr(copia, appat);
    Vocales(copia);
    if (copia[0] != curp[0] && copia[0] != '\0')
    {

        curp[1] = copia[0];
    }
    else
    {
        if (copia[1] == '\0' or copia[0] == '\0')
        {
            curp[1] = 'X';
        }
        else
        {
            curp[1] = copia[1];
        }
    }
    // primera letra del segundo apellido
    if (apmat[0] == 47 or apmat[0] == 45 or apmat[0] == 46 or apmat[0] == 39)
    {
        curp[2] = 'X';
    }
    else
    {
        curp[2] = apmat[0];
    }
    // primera letra del nombre excepto maria y jose si son compuestos
    if (nombre[0] == 47 or nombre[0] == 45 or nombre[0] == 46 or nombre[0] == 39)
    {
        curp[3] = 'X';
    }
    else
    {
        curp[3] = nombre[0];
    }
    // siguientes consonantes de apellido pat, ap materno y nombre
    Consonantes(appat);
    Consonantes(apmat);
    if (nombre[0] == 'M' && nombre[1] == 'A' && nombre[2] == 'R' && nombre[3] == 'I' && nombre[4] == 'A')
    {
        curp[15] = nombre[0];
    }
    else
    {
        if (nombre[0] == 'J' && nombre[1] == 'O' && nombre[2] == 'S' && nombre[3] == 'E')
        {
            curp[15] = nombre[0];
        }
        else
        {
            Consonantes(nombre);
            if (nombre[0] != curp[3] && nombre[0] != '\0')
            {
                curp[15] = nombre[0];
            }
            else
            {
                if (nombre[1] == '\0' or nombre[0] == '\0')
                {
                    curp[15] = 'X';
                }
                else
                {
                    curp[15] = nombre[1];
                }
            }
        }
    }

    if (appat[0] != curp[0] && appat[0] != '\0')
    {
        curp[13] = appat[0];
    }
    else
    {
        if (appat[1] == '\0' or appat[0] == '\0')
        {
            curp[13] = 'X';
        }
        else
        {
            curp[13] = appat[1];
        }
    }

    if (apmat[0] != curp[2] && apmat[0] != '\0')
    {
        curp[14] = apmat[0];
    }
    else
    {
        if (apmat[1] == '\0' or apmat[0] == '\0')
        {
            curp[14] = 'X';
        }
        else
        {
            curp[14] = apmat[1];
        }
    }
}
void Nacimiento(char curp[], int anio, int mes, int dia)
{
    // primer digito de la homoclave
    if (anio < 2000)
    {
        curp[16] = '0';
    }
    else
    {
        if (anio >= 2010)
        {
            if (anio >= 2020)
            {
                curp[16] = 'C';
            }
            else
            {
                curp[16] = 'B';
            }
        }
        else
        {
            curp[16] = 'A';
        }
    }

    // paso numeros a cadena
    curp[5] = '0' + anio % 10;
    curp[4] = '0' + (anio / 10) % 10;
    if (mes > 9)
    {
        curp[6] = '0' + 1;
        curp[7] = '0' + mes % 10;
    }
    else
    {
        curp[6] = '0';
        curp[7] = '0' + mes;
    }

    if (dia > 9)
    {
        curp[9] = '0' + dia % 10;
        curp[8] = '0' + (dia / 10) % 10;
    }
    else
    {
        curp[8] = '0';
        curp[9] = '0' + dia;
    }
}
void Sexo(char curp[], int sex)
{

    if (sex <= 2)
    {
        if (sex == 2)
        {
            curp[10] = 'H';
        }
        else
        {
            curp[10] = 'M';
        }
    }
    else
    {
        curp[10] = 'X';
    }
}
void Estado(char curp[], int estado)
{
    curp[11] = estado;
    if (curp[11] >= 16)
    {
        if (curp[11] >= 24)
        {
            if (curp[11] >= 28)
            {
                if (curp[11] >= 30)
                {
                    if (curp[11] >= 31)
                    {
                        if (curp[11] >= 32)
                        {
                            if (curp[11] == 32)
                            {
                                curp[11] = 'Z';
                                curp[12] = 'S';
                            }
                            else
                            {
                                curp[11] = 'N';
                                curp[12] = 'E';
                            }
                        }
                        else
                        {
                            curp[11] = 'Y';
                            curp[12] = 'N';
                        }
                    }
                    else
                    {
                        curp[11] = 'V';
                        curp[12] = 'Z';
                    }
                }
                else
                {
                    if (curp[11] == 28)
                    {
                        curp[11] = 'T';
                        curp[12] = 'S';
                    }
                    else
                    {
                        curp[11] = 'T';
                        curp[12] = 'L';
                    }
                }
            }
            else
            {
                if (curp[11] >= 25)
                {
                    if (curp[11] >= 26)
                    {
                        if (curp[11] == 27)
                        {
                            curp[11] = 'T';
                            curp[12] = 'C';
                        }
                        else
                        {
                            curp[11] = 'S';
                            curp[12] = 'R';
                        }
                    }
                    else
                    {
                        curp[11] = 'S';
                        curp[12] = 'L';
                    }
                }
                else
                {
                    curp[11] = 'S';
                    curp[12] = 'P';
                }
            }
        }
        else
        {
            if (curp[11] >= 20)
            {
                if (curp[11] >= 22)
                {
                    if (curp[11] == 23)
                    {
                        curp[11] = 'Q';
                        curp[12] = 'R';
                    }
                    else
                    {
                        curp[11] = 'Q';
                        curp[12] = 'T';
                    }
                }
                else
                {
                    if (curp[11] == 21)
                    {
                        curp[11] = 'P';
                        curp[12] = 'L';
                    }
                    else
                    {
                        curp[11] = 'O';
                        curp[12] = 'C';
                    }
                }
            }
            else
            {
                if (curp[11] >= 18)
                {
                    if (curp[11] == 19)
                    {
                        curp[11] = 'N';
                        curp[12] = 'L';
                    }
                    else
                    {
                        curp[11] = 'N';
                        curp[12] = 'T';
                    }
                }
                else
                {
                    if (curp[11] == 17)
                    {
                        curp[11] = 'M';
                        curp[12] = 'S';
                    }
                    else
                    {
                        curp[11] = 'M';
                        curp[12] = 'N';
                    }
                }
            }
        }
    }
    else
    {
        if (curp[11] >= 8)
        {
            if (curp[11] >= 12)
            {
                if (curp[11] >= 14)
                {
                    if (curp[11] == 15)
                    {
                        curp[11] = 'J';
                        curp[12] = 'C';
                    }
                    else
                    {
                        curp[11] = 'H';
                        curp[12] = 'G';
                    }
                }
                else
                {
                    if (curp[11] == 12)
                    {
                        curp[11] = 'G';
                        curp[12] = 'T';
                    }
                    else
                    {
                        curp[11] = 'G';
                        curp[12] = 'R';
                    }
                }
            }
            else
            {
                if (curp[11] >= 10)
                {
                    if (curp[11] == 11)
                    {
                        curp[11] = 'M';
                        curp[12] = 'C';
                    }
                    else
                    {
                        curp[11] = 'D';
                        curp[12] = 'G';
                    }
                }
                else
                {
                    if (curp[11] == 8)
                    {
                        curp[11] = 'C';
                        curp[12] = 'L';
                    }
                    else
                    {
                        curp[11] = 'C';
                        curp[12] = 'M';
                    }
                }
            }
        }
        else
        {
            if (curp[11] >= 4)
            {
                if (curp[11] >= 6)
                {
                    if (curp[11] == 7)
                    {
                        curp[11] = 'D';
                        curp[12] = 'F';
                    }
                    else
                    {
                        curp[11] = 'C';
                        curp[12] = 'H';
                    }
                }
                else
                {
                    if (curp[11] == 5)
                    {
                        curp[11] = 'C';
                        curp[12] = 'S';
                    }
                    else
                    {
                        curp[11] = 'C';
                        curp[12] = 'C';
                    }
                }
            }
            else
            {
                if (curp[11] >= 2)
                {
                    if (curp[11] == 3)
                    {
                        curp[11] = 'B';
                        curp[12] = 'S';
                    }
                    else
                    {
                        curp[11] = 'B';
                        curp[12] = 'C';
                    }
                }
                else
                {
                    curp[11] = 'A';
                    curp[12] = 'S';
                }
            }
        }
    }
}
// palabras antisonantes
void Antison(char curp[])
{
    int tam, i = 0, x;
    char compr[5];
    char malas[82][5] = {"BACA", "BAKA", "BUEI", "BUEY", "CACA", "CACO", "CAGA", "CAGO", "CAKA", "CAKO", "COGE", "COGI", "COJA", "COJE", "COJI", "COJO", "COLA", "CULO", "FALO", "FETO", "GETA", "GUEI", "GUEY", "JETA", "JOTO", "KACA", "KACO", "KAGA", "KAGO", "KAKA", "KAKO", "KOGE", "KOGI", "KOJA", "KOJE", "KOJI", "KOJO", "KOLA", "KULO", "LILO", "LOCA", "LOCO", "LOKA", "LOKO", "MAME", "MAMO", "MEAR", "MEAS", "MEON", "MIAR", "MION", "MOCO", "MOKO", "MULA", "MULO", "NACA", "NACO", "PEDA", "PEDO", "PENE", "PIPI", "POPO", "PUTA", "PUTO", "QULO", "RATA", "ROBA", "ROBE", "ROBO", "RUIN", "SENO", "TETA", "VACA", "VAGO", "VAKA", "VUEI", "VUEY", "WUEI", "WUEY"};
    strncpy(compr, curp, 4);
    while (i < 82)
    {
        x = strcmp(compr, malas[i]);
        if (x == 0)
        {
            curp[1] = 'X';
            break;
        }
        i++;
    }
}