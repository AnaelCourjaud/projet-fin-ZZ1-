#include "sauvegarder.h"

int grille[HAUTEUR][LARGEUR];
/*for (i = 0; i < HAUTEUR; i++)
{
    for (j = 0; j < LARGEUR; j++)
    {
        grille[i][j] = 0;
    }
}
grille[2][6] = 1;*/

void sauvegarder(int grille[HAUTEUR][LARGEUR])
{
    FILE *fichier = NULL;
    time_t now;
    time(&now);
    char nomfichier[100];
    strcpy(nomfichier, "sauvegarde");
    strcat(strcat(nomfichier, ctime(&now)), ".txt");
    fichier = fopen(nomfichier, "w");
    int i, j;
    for (i = 0; i < HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            fprintf(fichier, "%d ", grille[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

int loadConfig(int grille[HAUTEUR][LARGEUR], char nom_fic[100])
{
    int erreur = 1; // pas d'erreur

    FILE *fichier = NULL;
    fichier = fopen(nom_fic, "r");
    if (fichier == NULL)
        erreur = 0;
    char ligne[LARGEUR+1];
    // int k;
    // for (k = 0; k < LARGEUR; k++)
    //     ligne[k] = '4';
    ligne[0] = '\0';
    // printf(ligne);

    if (fichier)
    {
        int i = 0;
        int j;
        printf("On commence ici\n");
        // while (!feof(fichier))
        // {
        //     fgets(ligne, LARGEUR+1, fichier);

        //     if(i<HAUTEUR)
        //     {
        //         for (j = 0; j < LARGEUR; j++)
        //         {
        //             if ((ligne[j] != '0') && (ligne[j] != '1'))
        //                 erreur = 0;
        //             grille[i][j] = ligne[j] - '0' ;
        //             printf("%c", ligne[j]);
        //         }
        //         printf("\n");
        //         i++;
        //     }
        // }
        
        while( !feof(fichier) )
        {
             for (j = 0; j < LARGEUR; j++)
            {
                fscanf(fichier, "%d", &grille[i][j]);
                printf("%d ", grille[i][j]);
            }
            printf("\n");
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
    for (i = 0; i < HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            grille[i][j] = 0;
        }
    }
    grille[2][6] = 1;

    int erreur = loadConfig(grille, "config1.txt");
    sauvegarder(grille);
    return 0;
}
// pour effacer un fichier : remove("nomFichier.xxx");