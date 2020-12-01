#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Noeud{
    int info; // L'information d'un noeud ou d'une feuille = sa valeur
    struct Noeud* sag; // Pour aller au prochain élément côté gauche
    struct Noeud* sad; // Pour aller au prochain élément côté droit
} Noeud;

typedef struct Element{
    int occurrence;
    char caractere;
    struct Element* suiv;
}Element;

typedef Element* Liste;

Element* Creer_New_Element(char c);
Element* Liste_occurrence_caractere(char* input, Element* Liste);
void afficher_liste (Element* Liste);
void liberer_Liste(Element* Liste);
int Compare_caractere(Element* Liste, char carac);
int minimum_Liste(Element* Liste);

#endif