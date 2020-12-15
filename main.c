#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "fonctions_2.h"
#include "fonctions_3.h"
#include <time.h>


int main()
{
    clock_t debut, fin;
	  double duree;
    debut = clock();

    char *dictionnaire[256];
    Arbre arbre;


    char *fsource = "input.txt";
    char *ftraduit = "traduction.txt";
    char *fcode = "output.txt";
    char *fdecode = "decodage.txt";
    char *ftest = "test.txt";


    printf("\n\n\n\t_________PROJET HUFFMAN___________\n\n");

    printf("Le nombre de caracteres dans le fichier source (%s) est : %d\n", fsource,nombre_caracteres(fsource));

    traduire_binaire_texte(fsource, ftraduit );
    int nbcartraduit=nombre_caracteres("traduction.txt");
    printf("Le nombre de caracteres dans le fichier traduit (%s) est : %d\n\n", ftraduit,nbcartraduit);

    printf("Calcul des occurrences de caracteres dans le fichier %s\n",fsource);
    Element* L = Liste_occurence_caractere(fsource);

    afficher_liste(L);

    printf("Creation de l'Arbre Huffman\n");
    Arbre A = creer_Arbre_Huffman(L);

    printf("Creation du Dictionnaire\n\n");
    creation_Dictionnaire(A,"Dictionnaire.txt","dico_visuel.txt");

    //Lecture du fichier pour création dictionnaire pour le codage et arbre pour le décodage
    traduire_binaire_dico_Huffman("Dictionnaire.txt",dictionnaire,&arbre);

    printf("Codage du fichier source (%s) dans le fichier (%s)\n",fsource,fcode);
    codage_fichier(fsource,fcode,dictionnaire);

    int aux = nombre_caracteres(fcode);
    printf("Le nombre de caracteres dans le fichier code (%s) est : %d\nGain de codage : %f %%\n", fcode,aux,((float)aux/nbcartraduit)*100);

    printf("Decodage du fichier (%s) dans (%s)\n\n",fcode,fdecode);
    decodage_fichier(fcode,fdecode,arbre);

    Liberer_Arbre(arbre);
    
    Liberer_dictionnaire(dictionnaire);

    fin = clock();
    duree = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf( "L'execution met %f secondes\n", duree );

    return 0;
}
