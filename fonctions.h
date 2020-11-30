#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void convertir_binaire(char caractere, char* conteneur);
void traduire_binaire_texte(char* input, char* traduction);
int nombre_caracteres();
int nombre_en_binaire();

#endif
#define TAILLE_MAX 150000 // On définit une taille maximale à notre tableau
