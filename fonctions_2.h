#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#define TAILLE 50

typedef struct Noeud{
    int info;
    char caractere; 
    struct Noeud* sag; 
    struct Noeud* sad; 
} Noeud;

typedef Noeud* Arbre;


typedef struct Element{
    int occurence;
    char caractere;
    Arbre arbre;
    struct Element* suiv;
}Element;

typedef Element* Liste;

Element* Creer_New_Element(char c);
Element* Liste_occurence_caractere(char* input);
void afficher_liste (Element* Liste);
int liberer_Liste(Element* Liste);
int Compare_caractere(Element* Liste, char carac);


Noeud* creer_noeud(int valeur);
Noeud* creer_arbre(int n);


void creation_Dictionnaire(Arbre A,char *fichierDictionnaire);

Arbre creer_Arbre_Huffman(Element* Liste);
void traduire_binaire_dico_Huffman (char* fichierdico,char *dictionnaire[256],Arbre *arbre);
void codage_fichier(char* fichierinput,char* fichieroutput,char *dictionnaire[256]);
void decodage_fichier(char* fichierinput,char* fichieroutput,Arbre arbre);


#endif