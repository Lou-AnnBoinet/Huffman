#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"


//partie 1

void convertir_binaire(char caractere, char* conteneur)
{
    int var = 128;
    for (int i = 0; i < 8 ; i++)
        {
            if ( caractere >= var )
            {
                conteneur[i] = '1';
                caractere -= var;
            }
            else
            {
                conteneur[i] = '0';
            }
            var /= 2;
        }
    conteneur[8] = '\0';
}

void traduire_binaire_texte(char* input, char* traduction)
{
    FILE* texte = fopen("input.txt", "r");
    FILE* texte2 = fopen("traduction.txt", "w");
    char temp = 0;
    char conteneur[9] ;
    while ( (temp = getc(texte)) != EOF)
    {