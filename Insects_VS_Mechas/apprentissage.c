#include "apprentissage.h"

void gestionTable(float tableQ[NBPERCEPTION][NBDEFENSES], int tablesauv[2][NBRCOUPSMAXENREGISTRABLES], int nombreDeCoupsIA, float gamma, float epsilon)
{
    // int taille = tailleTableau(tablesauv);
    // int i;
    float p = 0.0;

    for (int i = nombreDeCoupsIA - 1; i >= 0; i--)
    {
        int perception = tablesauv[0][i];
        int action = tablesauv[1][i];
        tableQ[perception][action] += epsilon * powf(gamma, p);

        p++;
    }
}

int preferencelearning(int perception, float tableQ[NBPERCEPTION][NBDEFENSES], float temperature)
{
    float E[NBDEFENSES];
    float z = 0;
    float cumul = 0;
    int i;

    for (i = 0; i < NBDEFENSES; i++)
    {
        float Q = tableQ[perception][i];
        E[i] = expf(Q / temperature);
        z += E[i];
    }

    // float alpha = reelAleatoireUniforme();
    float alpha = rand()/(RAND_MAX+1.0);

    int defense = NBDEFENSES-1;
    // printf("defense : %d\n", defense);

    for (i = 0; i < NBDEFENSES; i++)
    {
        cumul += E[i] / z;
        if (alpha <= cumul)
        {
            defense = i;
            break;
        }
    }
    
    return defense;
}

int noaleatoire(int perception, float tableQ[NBPERCEPTION][NBDEFENSES])
{
    int i;
    int defense = rand() % 3;

    for (i = 0; i < NBDEFENSES; i++)
    {
        if (tableQ[perception][i] >= tableQ[perception][defense])
        {
            defense = i;
        }
    }

    return defense;
}

/*
Entrées :
  - s la situation
  - la tableQ
  - epsilon
Sortie :
  - une action tirée selon la distribution de Gibbs
Processus :
  - Pour chaque action a de L:
      - Définir E(a) : l'énergie de a est E(a) = exp(Q(s,a)/T)
  - Définir Z : la somme des énergies des éléments de L
  - Définir defense = L[r], avec r un nombre aléatoire entre 0 et 2
  - Définir alpha : un réel tiré en aléatoire uniforme dans [0 ; 1[
  - Définir cumul = 0
  - pour a dans L :
    - cumul +=  E(a)/Z
    - si alpha <= cumul :
      - defense = a
      - break
  - renvoyer defense */

float reelAleatoireUniforme()
{
    int digit = 1000000;
    int r = rand() % digit;
    // printf("r : %d\n", r);
    float reel = r / (float)digit;

    return reel;
}
/*
int tailleTableau(int tablesauv[2][NBPERCEPTION], int compteur){

    int taille = 0;

    while(tablesauv[0][taille] != 1000)
    {
        taille += 1;
    }
    return taille;
}*/

void initTableQ(float tableQ[NBPERCEPTION][NBDEFENSES])
{
    int i;
    int j;
    int r;

    for (i = 0; i < NBPERCEPTION; i++)
    {
        for (j = 0; j < NBDEFENSES; j++)
        {
            tableQ[i][j] = 0;
            // r = rand() % 4;
            // if (r == 0)
            // {
            //     tableQ[i][j] = 0.01;
            // }
            // else if (r == 1)
            // {
            //     tableQ[i][j] = -0.01;
            // }
            // else if (r == 2)
            // {
            //     tableQ[i][j] = 0.001;
            // }
            // else if (r == 3)
            // {
            //     tableQ[i][j] = -0.001;
            // }
        }
    }
}

void affichageTable(float tableQ[NBPERCEPTION][NBDEFENSES])
{

    char nomperception[PERCEPTIONMAX][TAILLECHAR];
    strcpy(nomperception[0], "B   ");
    strcpy(nomperception[1], "F   ");
    strcpy(nomperception[2], "M   ");
    strcpy(nomperception[3], "BB  ");
    strcpy(nomperception[4], "FF  ");
    strcpy(nomperception[5], "MM  ");
    strcpy(nomperception[6], "BF  ");
    strcpy(nomperception[7], "BM  ");
    strcpy(nomperception[8], "FM  ");
    strcpy(nomperception[9], "BBB ");
    strcpy(nomperception[10], "FFF ");
    strcpy(nomperception[11], "MMM ");
    strcpy(nomperception[12], "BBF ");
    strcpy(nomperception[13], "BBM ");
    strcpy(nomperception[14], "FFB ");
    strcpy(nomperception[15], "FFM ");
    strcpy(nomperception[16], "MMB ");
    strcpy(nomperception[17], "MMF ");
    strcpy(nomperception[18], "MFB ");
    strcpy(nomperception[19], "BBBB");
    strcpy(nomperception[20], "FFFF");
    strcpy(nomperception[21], "MMMM");
    strcpy(nomperception[22], "BBBF");
    strcpy(nomperception[23], "BBBM");
    strcpy(nomperception[24], "FFFM");
    strcpy(nomperception[25], "FFFB");
    strcpy(nomperception[26], "MMMF");
    strcpy(nomperception[27], "MMMB");
    strcpy(nomperception[28], "BBMM");
    strcpy(nomperception[29], "BBFF");
    strcpy(nomperception[30], "BBFM");
    strcpy(nomperception[31], "FFMM");
    strcpy(nomperception[32], "FFBM");
    strcpy(nomperception[33], "MMFB");

    int i;

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("    |         Defense Robot        |      Defense Robot Metal     |      Defense Robot Petit     |\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < NBPERCEPTION; i++)
    {
        printf("%s|           %f                       %f                       %f            \n", nomperception[i], tableQ[i][0], tableQ[i][1], tableQ[i][2]);
    }
    printf("\n");
}

void affichageSauv(int tablesauv[2][NBRCOUPSMAXENREGISTRABLES], int taille)
{

    int i;

    printf("Perception| Defense -----------------------------------------------------------------------------------\n");
    for (i = 0; i <= taille; i++)
    {
        printf(" %d    |   %d \n", tablesauv[0][i], tablesauv[1][i]);
    }

    printf("\n");
}

void sauvegarder(float tableQ[NBPERCEPTION][NBDEFENSES])
{
    FILE *fichier = NULL;
    time_t now;
    time(&now);
    char nomfichier[100];
    strcpy(nomfichier, "sauvegarde");
    strcat(strcat(nomfichier, ctime(&now)), ".txt");
    fichier = fopen(nomfichier, "w");
    int i, j;
    for (i = 0; i < NBPERCEPTION; i++)
    {
        for (j = 0; j < NBDEFENSES; j++)
        {
            fprintf(fichier, "%f ", tableQ[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

int loadConfig(float tableQ[NBPERCEPTION][NBDEFENSES], char nom_fic[100])
{
    int erreur = 1; // pas d'erreur

    FILE *fichier = NULL;
    fichier = fopen(nom_fic, "r");
    if (fichier == NULL)
        erreur = 0;

    if (fichier)
    {
        int i = 0;
        int j;

        while (!feof(fichier))
        {
            for (j = 0; j < NBDEFENSES; j++)
            {
                fscanf(fichier, "%f", &tableQ[i][j]);
                printf("%f ", tableQ[i][j]);
            }
            printf("\n");
            i++;
        }
        fclose(fichier);
    }
    return erreur;
}
/*
int main()
{
    float tableQ[NBPERCEPTION][NBDEFENSES];
    float epsilon = 1.0;
    float gamma = 0.5;

    int tablesauv[2][NBPERCEPTION] ;
    tablesauv[0][0] = 0; tablesauv[1][0] = 0;
    tablesauv[0][1] = 4; tablesauv[1][1] = 2;
    tablesauv[0][2] = 9; tablesauv[1][2] = 1;
    tablesauv[0][3] = 12; tablesauv[1][3] = 0;
    tablesauv[0][4] = 1000;

    srand( time( NULL ) );

    initTableQ(tableQ);
    affichageTable(tableQ);

    gestionTable(tableQ, tablesauv, gamma, epsilon);
    affichageTable(tableQ);

    int perception = 1;
    int defense = preferencelearning(perception, tableQ, epsilon);
    printf("defense a effectuer%d\n", defense);

    sauvegarder(tableQ);

    int defense2 = noaleatoire(perception, tableQ);
    printf("defense a effectuer sans alea %d\n", defense2);

    return 0;
}
*/