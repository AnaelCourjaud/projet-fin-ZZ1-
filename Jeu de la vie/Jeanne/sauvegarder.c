#include "sauvegarder.h"

int grille[HAUTEUR][LARGEUR];
for (i = 0; i < HAUTEUR; i++)
{
    for (j = 0; j < LARGEUR; j++)
    {
        grille[i][j] = 0;
    }
}
grille[2][6] = 1;

void sauvegarder(int grille[HAUTEUR][LARGEUR])
{
    FILE *fichier = NULL;
    time_t now;
    char nomfichier[100];
    strcpy(nomfichier, "sauvegarde");
    strcat(strcat(nomfichier, ctime(&now)), ".txt");
    fichier = fopen(nomfichier, "w");
    int i, j;
    for (i = 0; i < HAUTEUR; i++)
    {
        char ligne[LARGEUR + 1];
        for (j = 0; j < LARGEUR; j++)
        {
            ligne[j] = grille[i][j] + '0';
        }
        ligne[LARGEUR] = 0;
        fprintf(fichier, "%s\n", ligne);
    }
    fclose(fichier);
}

int loadConfig(int grille[HAUTEUR][LARGEUR], char nom_fic[100])
{
    int erreur = 1; // pas d'erreur

    FILE *fichier = NULL;
    fichier = fopen(nom_fic, "r");
    if (fichier == 0)
        erreur = 0;
    char ligne[LARGEUR];
    int k;
    for (k = 0; k < LARGEUR; k++)
        ligne[k] = 4;
    printf(ligne);
    if (fichier)
    {
        int i = 0;
        int j;
        while (fgets(ligne, LARGEUR, fichier))
        {
            for (j = 0; j < LARGEUR; j++)
            {
                if ((atoi(ligne) != 0) || (atoi(ligne) != 1) || (atoi(ligne) != 4))
                    erreur = 0;
                grille[i][j] = atoi(ligne[j]);
                printf(ligne[j]);
            }
            i++;
        }
        fclose(fichier);
    }
    return erreur;
}

int main()
{
    int grille[HAUTEUR][LARGEUR];
    int i,j;
    /*for (i = 0; i < HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            grille[i][j] = 0;
        }
    }
    grille[2][6] = 1;*/

    int erreur = loadConfig(grille, "config.txt");
    return 0;
}
// pour effacer un fichier : remove("nomFichier.xxx");