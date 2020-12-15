#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions-2.h"

//Partie 2 Le code d'Huffman version naive

Element* Creer_New_Element(char c){
    Element* new_element = malloc(sizeof(Element));
    new_element->caractere  = c;
    new_element->occurence = 1;
    new_element->arbre = NULL;
    new_element->suiv = NULL;
    return new_element;
}

//2.1 Les occurrences

void Compare_caractere(Element* Liste, char carac){
    if (Liste == NULL){
      EXIT_FAILURE ;
    }
    if ( Liste->caractere == carac){
        Liste->occurence ++;
    }
    else if (Liste->suiv == NULL){
       Liste->suiv = Creer_New_Element(carac);
    }
    else {Compare_caractere(Liste->suiv, carac);}
}

Element* Liste_occurence_caractere(char* input){
    Element* Liste = NULL;
    FILE* texte = fopen(input, "r");
    char temp = 0;
    while ( (temp = fgetc(texte)) != EOF){
        if (Liste == NULL)
          Liste = Creer_New_Element(temp);
        else
          Compare_caractere(Liste, temp);
    }
    fclose(texte);
    return Liste;
}

void afficher_liste (Element* Liste)       
{   Element* temp;
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

//2.2 L'Arbre


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

Arbre nouvelArbre(int v,char c)
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
  Arbre a = nouvelArbre(e1->occurence+e2->occurence,(char)0);
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
      a->sad = nouvelArbre(max->occurence,max->caractere);

  if (min->arbre != NULL)
      a->sag = min->arbre;
  else
      a->sag = nouvelArbre(min->occurence,min->caractere);

  return a;

}

Arbre creer_Arbre_Huffman(Element* Liste)
{
  Element *L = Liste;

  while (L!=NULL)
  {
      Element *e1 = isoleetrenvoiepluspetit(&L);
      Element *e2 = isoleetrenvoiepluspetit(&L);
      if (e2==NULL) return e1->arbre; 
      Arbre a = AjouterElementArbre(e1,e2);

      free (e2);

      e1->arbre = a;
      e1->caractere = 0;
      e1->occurence = a->info;

      e1->suiv = L;
      L = e1;
  }
}

//2.3 Le Dictionnaire

void creation_Dictionnaire_rec(Arbre A,char code[],FILE *fileDictionnaire,FILE *filedico)
{
  if (A==NULL) return ;

  if (A->caractere!=0)
  {

    fprintf(fileDictionnaire,"%d:%s\n",A->caractere,code);
    fprintf(filedico,"%c:%s\n",A->caractere,code);
  }
  else
  {

    int len;
    for (len=0;code[len]!=0;len++) ; 
    code[len] = '1'; code[len+1]=0;
    creation_Dictionnaire_rec(A->sad,code,fileDictionnaire,filedico);
    code[len] = '0'; code[len+1]=0;
    creation_Dictionnaire_rec(A->sag,code,fileDictionnaire,filedico);
  }
}

void creation_Dictionnaire(Arbre A,char *fichierDictionnaire,char *fichierdico)
{
    FILE* file = fopen(fichierDictionnaire, "w");
    FILE* file2 = fopen (fichierdico, "w");
    char s[500];
    s[0] = 0;
    creation_Dictionnaire_rec(A,s,file,file2);
    fclose(file);
}

//2.4 L'encodage

void insererBranche(Arbre a,char *s,char c)
{
  for (int i=0;s[i];i++)
    if (s[i]=='0')
    {
      if (a->sag == NULL)
        {
        a->sag = nouvelArbre(0,0); 
        }
      a = a->sag;
    }
    else
    {
      if (a->sad == NULL)
      {
        a->sad = nouvelArbre(0,0); 
      }
      a = a->sad;
    }
  a->caractere = c; 
}

void traduire_binaire_dico_Huffman (char* fichierdico,char *dictionnaire[256],Arbre *arbre)
{
  *arbre = nouvelArbre(0,0);
  char chaine[50];
  FILE* texte = fopen(fichierdico, "r");


    for (int i=0;i<256;i++)
    {
      dictionnaire[i] = NULL;
    }

    while (fgets(chaine,TAILLE,texte))
    {
      int i;
      char res=0;
      char s[50];
      for (i=0;chaine[i]!=':';i++) res = res*10+(chaine[i]-'0');

      i++;
      int j;
      for ( j=i;(chaine[j]!=0) && (chaine[j]!='\n');j++)
      {
        s[j-i] = chaine[j];
      }
        s[j-i] = 0;

      dictionnaire[res] =(char*)malloc((strlen(s)+1)*sizeof(char));
      strcpy(dictionnaire[res],s); 
      insererBranche(*arbre,s,res);
    }

  fclose(texte);
}


void codage_fichier(char* fichierinput,char* fichieroutput,char *dictionnaire[256])
{
  char chaine[500];
  FILE* texte = fopen(fichierinput, "r");
  FILE* texteout = fopen(fichieroutput, "w");
  while (fgets(chaine,500,texte))
  {
    for (int j=0;chaine[j]!='\0';j++) fprintf(texteout,"%s",dictionnaire[chaine[j]]);
  }
  fclose(texte);
  fclose(texteout);
}

//2.5 Le decodage

void decodage_fichier(char* fichierinput,char* fichieroutput,Arbre arbre)
{
  char chaine[500];
  Arbre a = arbre;

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
   }
  }
  fclose(texte);
  fclose(texteout);
}

// Liberation

void Liberer_Arbre (Arbre A)
{
  if (A!=NULL)
  {
    Liberer_Arbre(A->sag);
    Liberer_Arbre(A->sad);
    free(A);
  }
}

void Liberer_dictionnaire(char *dictionnaire[256])
{
  for (int i=0;i<256;i++)
  {
    if (dictionnaire[i]!=NULL)
    {
      free(dictionnaire[i]);
    }
  }
}
