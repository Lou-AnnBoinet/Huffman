
void convertir_binaire(char caractere, char* conteneur)
{
    int var = 128; //2 exposant 7
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
    while ( (temp = fgetc(texte)) != EOF)
    {
        convertir_binaire(temp, conteneur);
        fprintf(texte2, "%s" , conteneur);
    }
    fclose(texte2);
    fclose(texte);
}


int nombre_caracteres(char* fichier)
{
    FILE* texte = fopen(fichier, "r");
    int comp = 0;
    char temp = 0;
    while ( (temp = getc(texte)) != EOF ){
        comp++;
    }
    fclose(texte);
    return comp;
}