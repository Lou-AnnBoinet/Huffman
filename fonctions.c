#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 150000 // On définit une taille maximale à notre tableau
#include "fonction.h"

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
        convertir_binaire(temp, conteneur);
        fprintf(texte2, "%s" , conteneur);
    }
    fclose(texte2);
    fclose(texte);
}
/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

int nombre_caracteres()
{
    FILE *fichier = NULL; // Pointeur initialisé à NULL
    int cmpt = 0; // Un compteur initialisé à 0
    char *tab = (char*)malloc(sizeof(char)*TAILLE_MAX); // On alloue de la mémoire à un tableau
    // On met deux \\ pour le fichier afin d'utiliser la méthode du chemin absolu
    fichier = fopen("input.txt", "r"); // Le pointeur fichier devient un pointeur sur input
    if (fichier == NULL)
    {
        return -1; // Fichier vide
    }
    else{
        while (fgets(tab, TAILLE_MAX, fichier) != NULL) // La fonction fgets lit les caracteres du fichier, les range dans notre tableau
        {
            cmpt = cmpt + strlen(tab); // strlen --> permet de calculer la longueur d'une chaîne de caracteres
        }
    }
    fclose(fichier); // Fermer le fichier une fois qu'on l'a utilisé
    return cmpt;
}

int nombre_en_binaire()
{
    FILE *fichier = NULL;
    int cmpt = 0;
    char *tab = (char*)malloc(sizeof(char)*TAILLE_MAX);
    fichier = fopen("traduction.txt", "r");
    if (fichier == NULL) return -1;
    else{
        while (fgets(tab, TAILLE_MAX, fichier) != NULL){
            cmpt = cmpt + strlen(tab);
        }
    }
    fclose(fichier);
    return cmpt;
}