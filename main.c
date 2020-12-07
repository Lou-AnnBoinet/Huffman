#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "fonctions_2.h"
#include "fonctions_3.h"


int main()
{
    char *dictionnaire[256];
    Arbre arbre;


    char *fsource = "input.txt";
    char *ftraduit = "traduction.txt";
    char *fcode = "output.txt";
    char *fdecode = "decodage.txt";


    printf("\n\n\n\n____________________\n");

    printf("Le nombre de caracteres dans le fichier source (%s) est : %d\n", fsource,nombre_caracteres(fsource));

    traduire_binaire_texte(fsource, ftraduit );
    int nbcartraduit=nombre_caracteres("traduction.txt");
    printf("Le nombre de caracteres dans le fichier traduit (%s) est : %d\n", ftraduit,nbcartraduit);

    printf("Calcule des occurences de caracteres dans le fichier %s\n",fsource);
    Element* L = Liste_occurence_caractere(fsource);

    //DEBUG afficher_liste(L);

    printf("Création de l'Arbre de Huffman\n");
    Arbre A = creer_Arbre_Huffman(L);


    printf("Création du Dictionnaire\n");
    creation_Dictionnaire(A,"Dictionnaire.txt");

    traduire_binaire_dico_Huffman("Dictionnaire.txt",dictionnaire,&arbre);

    printf("Codage du fichier source (%s) dans le fichier (%s)\n",fsource,fcode);
    codage_fichier(fsource,fcode,dictionnaire);

    int aux = nombre_caracteres(fcode);
    printf("Le nombre de caracteres dans le fichier codé (%s) est : %d\nGain de codage : %f %%\n", fcode,aux,((float)aux/nbcartraduit)*100);

    printf("Decodage du fichier (%s) dans (%s)\n",fcode,fdecode);
    decodage_fichier(fcode,fdecode,arbre);

    return 0;
}
