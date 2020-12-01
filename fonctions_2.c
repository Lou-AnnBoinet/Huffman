#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions_2.h"

Element* Creer_New_Element(char c){         //fonction pour créer les élements d'une liste
    Element* new_element = malloc(sizeof(Element));
    new_element->caractere  = c;
    new_element->occurrence = 1;
    new_element->suiv = NULL;
    return new_element;
}

void liberer_Liste(Element* Liste){
    if (Liste == NULL){
        return NULL;
    }
    else {
        liberer_Liste(Liste->suiv);
        Liste->occurrence = 0;
        Liste->caractere = 0;
        Liste->suiv = NULL;
        Element* Liste = NULL;
        free(Liste);
    }
}


/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

int Compare_caractere(Element* Liste, char carac){      //On compare les caractères avec la liste 
    if (Liste == NULL){return NULL;}
    if ( Liste->caractere == carac){
        Liste->occurrence ++;
            return 0;               //On retourne 0 si le caractère est déjà dans la liste et on augmente l'occurrence
    }
    else if (Liste->suiv == NULL){
       Liste->suiv = Creer_New_Element(carac);
    }
    else {Compare_caractere(Liste->suiv, carac);}
    return 1;           //On retourne 1 si le caractère n'existe pas ce qui permet de le rajouter dans la liste
}

Element* Liste_occurrence_caractere(char* input, Element* Liste){
    FILE* texte = fopen(input, "r");
    char temp = 0;
    while ( (temp = getc(texte)) != EOF){
          Compare_caractere(Liste, temp);       //On voit si on ajoute ou non un élement dans la liste selon le retour
    }
    fclose(texte);
    return 0;
}

void afficher_liste (Element* Liste)
{    Element* temp;
    temp = Liste;
    if (Liste == NULL){
        printf("La Liste est NULL\n");
    }
    else {
    while(temp!=NULL)
    {   printf("%c present ", temp->caractere);
        printf("%d fois\n", temp->occurrence);
        temp=temp->suiv; }
    }
}

/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

int minimum_Liste(Element* Liste)
{
    return 0;
}

