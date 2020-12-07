#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions-2.h"

//Partie 2 Le code de Huffman version naive
//2.1 Les occurences

Element* Creer_New_Element(char c){
    Element* new_element = malloc(sizeof(Element));
    new_element->caractere  = c;
    new_element->occurence = 1;
    new_element->arbre = NULL;
    new_element->suiv = NULL;
    return new_element;
}

int liberer_Liste(Element* Liste){
    if (Liste == NULL){
        return 0;
    }
    else {
        liberer_Liste(Liste->suiv);
        Liste->occurence = 0;
        Liste->caractere = 0;
        Liste->suiv = NULL;
        Element* Liste = NULL;
        free(Liste);
    }
}


int Compare_caractere(Element* Liste, char carac){
    if (Liste == NULL){return -1;}
    if ( Liste->caractere == carac){
        Liste->occurence ++;
            return 0;
    }
    else if (Liste->suiv == NULL){
       Liste->suiv = Creer_New_Element(carac);
    }
    else {Compare_caractere(Liste->suiv, carac);}
    return 1;
}


Element* Liste_occurence_caractere(char* input){
    Element* Liste = NULL;
    FILE* texte = fopen(input, "r");
    char temp = 0;
    while ( (temp = getc(texte)) != EOF){
        if (Liste == NULL)
          Liste = Creer_New_Element(temp);
        else
          Compare_caractere(Liste, temp);
    }
    fclose(texte);
    return Liste;
}

void afficher_liste (Element* Liste)
{    Element* temp;
    temp = Liste;
    if (Liste == NULL){
        printf("La Liste est NULL\n");
    }
    else {
    while(temp!=NULL)
    {   printf("\t%c present ", temp->caractere);
        printf("%d fois\n", temp->occurence);
        temp=temp->suiv; }
    }
}

/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

//2.2 L'arbre


Noeud* creer_noeud(int valeur)
{
    Noeud* nouv_noeud = (Noeud*) malloc(sizeof(Noeud));
    (nouv_noeud->info) = valeur;
    (nouv_noeud->sag) = NULL;
    (nouv_noeud->sad) = NULL;
    return nouv_noeud;
}

Noeud* creer_arbre(int n)
{
    if(n <= 0) return NULL;
    else{
        Noeud* nouv_noeud = creer_noeud(n); // Permet de crÃ©er tous les noeuds de l'arbre
        (nouv_noeud->sag) = creer_arbre((n-1)/2+(n-1)%2);
        (nouv_noeud->sad) = creer_arbre((n-1)/2);
        return nouv_noeud;
    }
}


Element* isoleetrenvoiepluspetit(Element** Liste)
{
    Element* pred=*Liste; 
    Element* temp=*Liste;
    Element* min = temp;
    Element* minp = temp; 

    if (temp==NULL)
    {
        return NULL;
    }
    while (temp!=NULL)
    {
        if ((temp->occurence) < min->occurence)
        {
            min = temp;
            minp = pred;
        }
        pred = temp;
        temp=temp->suiv;
    }

    if (*Liste != min)
      minp->suiv = min->suiv;
    else 
      *Liste = min->suiv;
    return min;
}

Arbre nouvelleArbre(int v,char c)
{
  Arbre a = malloc(sizeof(Arbre));
  a->sad = NULL;
  a->sag = NULL;
  a->info = v;
  a->caractere = c;
  return a;
}

Arbre AjouterElementArbre(Element *e1,Element *e2)
{
  Element *min,*max;
  Arbre a = nouvelleArbre(e1->occurence+e2->occurence,(char)0);
  if (e1->occurence >= e2->occurence)
  {
    min = e2;
    max = e1;
  }
  else
  {
    min = e1;
    max = e2;
  }

  if (max->arbre != NULL)
      a->sad = max->arbre;
  else
      a->sad = nouvelleArbre(max->occurence,max->caractere);

  if (min->arbre != NULL)
      a->sag = min->arbre;
  else
      a->sag = nouvelleArbre(min->occurence,min->caractere);

  return a;

}

Arbre creer_Arbre_Huffman(Element* Liste)
{
  //printf("CrÃ©ation de l'arbre de Huffman\n");

  Element *L = Liste;

  while (L!=NULL)
  {
      Element *e1 = isoleetrenvoiepluspetit(&L);
      Element *e2 = isoleetrenvoiepluspetit(&L);
      if (e2==NULL) return e1->arbre;
      Arbre a = AjouterElementArbre(e1,e2);
      //DEBUG printf("\tCrÃ©ation d'un noeud de poids %d\n",a->info); //char s[100]; scanf("%s",s);
      e1->arbre = a;
      e1->caractere = 0;
      e1->occurence = a->info;
      e1->suiv = L;
      L = e1;

      //DEBUG afficher_liste(L);

  }

}

/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

// 2.3 Le dictionnaire

void creation_Dictionnaire_rec(Arbre A,char code[],FILE *fileDictionnaire)
{
  if (A==NULL) return ;

  if (A->caractere!=0)
  {
    //DEBUG printf("\t%c : %s\n",A->caractere,code);
    fprintf(fileDictionnaire,"%d:%s\n",A->caractere,code);
  }
  else
  {
    int len;
    for (len=0;code[len]!=0;len++) ;
    code[len] = '1'; code[len+1]=0;
    creation_Dictionnaire_rec(A->sad,code,fileDictionnaire);
    code[len] = '0'; code[len+1]=0;
    creation_Dictionnaire_rec(A->sag,code,fileDictionnaire);
  }
}

void creation_Dictionnaire(Arbre A,char *fichierDictionnaire)
{
    FILE* file = fopen(fichierDictionnaire, "w");
    char s[500];
    s[0] = 0;
    creation_Dictionnaire_rec(A,s,file);
    fclose(file);
}

/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

//2.4 L'encodage

void insererBranche(Arbre a,char *s,char c)
{
  for (int i=0;s[i];i++)
    if (s[i]=='0')
    {
      if (a->sag == NULL)
        a->sag = nouvelleArbre(0,0);
      a = a->sag;
    }
    else
    {
      if (a->sad == NULL)
        a->sad = nouvelleArbre(0,0);
      a = a->sad;
    }
  a->caractere = c;
}


void traduire_binaire_dico_Huffman (char* fichierdico,char *dictionnaire[256],Arbre *arbre)
{
  *arbre = nouvelleArbre(0,0);
  char chaine[50];
  FILE* texte = fopen(fichierdico, "r");

    //char c;
    for (int i=0;i<256;i++) dictionnaire[i] = NULL;

    while (fgets(chaine,TAILLE,texte))
    {
      //DEBUG printf("L:%s",chaine);
      int i;
      char res=0;
      char s[50];
      for (i=0;chaine[i]!=':';i++) res = res*10+(chaine[i]-'0');

      i++;
      int j;
      for ( j=i;(chaine[j]!=0) && (chaine[j]!='\n');j++) s[j-i] = chaine[j];
      s[j-i] = 0;
      //DEBUG printf(">%c:%s",res,s);
      dictionnaire[res] =(char*)malloc((strlen(s)+1)*sizeof(char));
      strcpy(dictionnaire[res],s);
      insererBranche(*arbre,s,res);

    }

  fclose(texte);
}


void codage_fichier(char* fichierinput,char* fichieroutput,char *dictionnaire[256])
{
  char chaine[500];
  //Element_d *temp = liste;
  FILE* texte = fopen(fichierinput, "r");
  FILE* texteout = fopen(fichieroutput, "w");
  while (fgets(chaine,500,texte))
  {
    for (int j=0;chaine[j];j++) fprintf(texteout,"%s",dictionnaire[chaine[j]]);
  }
  fclose(texte);
  fclose(texteout);
}

/*______________________________________________*/
/*______________________________________________*/
/*______________________________________________*/

//2.5 Le dÃ©codage

void decodage_fichier(char* fichierinput,char* fichieroutput,Arbre arbre)
{
  char chaine[500];
  Arbre a = arbre;
  //Element_d *temp = liste;
  FILE* texte = fopen(fichierinput, "r");
  FILE* texteout = fopen(fichieroutput, "w");
  while (fgets(chaine,500,texte))
  {
   for (int j=0;chaine[j];j++)
   {
    if (chaine[j]=='0')
      a = a->sag;
    else
      a = a->sad;
    if (a->caractere != 0)
    {
        fprintf(texteout,"%c",a->caractere);
        a = arbre;
    }

//    for (int j=0;chaine[j];j++) fprintf(texteout,"%s",dictionnaire[chaine[j]]);
   }
  }
  fclose(texte);
  fclose(texteout);
}

