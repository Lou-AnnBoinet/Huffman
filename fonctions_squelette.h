
#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#define TAILLE_MAX 150000 // taille maximale tableau
#define TAILLE 50


typedef struct Noeud{
    int info; // occurence pour les feuilles / poids pour les noeuds
    char caractere; // 0 pour les noeud
    struct Noeud* sag; // sous arbre G
    struct Noeud* sad; // sous arbre D
} Noeud;

typedef Noeud* Arbre;

//Element peut être un caractere ou un Arbre
typedef struct Element{
    int occurence;
    char caractere;
    Arbre arbre;
    struct Element* suiv;
}Element;

typedef Element* Liste;


void convertir_binaire(char caractere, char* conteneur);
void traduire_binaire_texte(char* input, char* traduction);

int nombre_caracteres(char *nomfichier);


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


void tableau_noeud_dichotomique();
void trier_tableau();
Arbre Huffman_avec_files();
Arbre organiser_noeud_AVL();
void codage_fichier_opitimise();
void decodage_fichier_optimise();

#endif
