#include "apprentissage.h"

void gestionTable(float tableQ[NBPERCEPTION][NBDEFENSES], int tablesauv[2][NBPERCEPTION], float gamma, float epsilon)
{
    int taille = tailleTableau(tablesauv);
    int i;
    float p = 0.0;

    for(i = taille-1; i > -1; i--)
    {
        int perception = tablesauv[0][i];
        int action = tablesauv[1][i];
        tableQ[perception][action] = epsilon*pow(gamma,p);                    

        p ++;
    }
}

int preferencelearning(int perception, float tableQ[NBPERCEPTION][NBDEFENSES], float epsilon)
{
    float E[NBDEFENSES];
    float z = 0;
    float cumul = 0;
    int i;

    for(i=0;i<NBDEFENSES;i++){
        float Q = tableQ[perception][i];
        E[i] = expf(Q/epsilon);
        z += E[i];
    }   

    float alpha = reelAleatoireUniforme();

    int defense = rand() % 3;
    //printf("defense : %d\n", defense);

    for(i=0;i<NBDEFENSES;i++){
        cumul += E[i]/z;
        if(alpha <= cumul){
            defense = i;
            break;
        }
    }   

    return defense;
}

/*
Entrées :
  - s la situation
  - Q la méthode permettant de connaitre la qualité d'une action dans une situation donnée
  - T la 'température', c'est un réel strictement positif
Sortie :
  - une action tirée selon la distribution de Gibbs
Processus :
  - Définir L : la liste des actions possibles depuis l'état s
  - Définir N le nombre d'éléments de L
  - Pour chaque action a de L:
      - Définir E(a) : l'énergie de a est E(a) = exp(Q(s,a)/T)
  - Définir Z : la somme des énergies des éléments de L
  - Définir action = L[N-1], c'est l'indice de l'action par défaut 
  - Définir alpha : un réel tiré en aléatoire uniforme dans [0 ; 1[
  - Définir cumul = 0
  - pour a dans L :
    - cumul +=  E(a)/Z
    - si alpha <= cumul :
      - action = a
      - break
  - renvoyer action */

float reelAleatoireUniforme()
{
    int digit = 1000000;
    int r = rand() % digit;
    printf("r : %d\n", r);
    float reel = r/(float)digit;

    return reel;
}        

int tailleTableau(int tablesauv[2][NBPERCEPTION]){

    int taille = 0;

    while(tablesauv[0][taille] != 1000)
    {
        taille += 1;
    }
    return taille;
}

void initTableQ(float tableQ[NBPERCEPTION][NBDEFENSES])
{
    int i; int j;
    int r;

    for(i=0; i<NBPERCEPTION ; i++){
        for(j=0; j<NBDEFENSES; j++)
        {
            r = rand() % 4;
            if (r == 0){ 
                tableQ[i][j] = 0.01;}
            else if (r == 1){ 
                tableQ[i][j] = -0.01;}
            else if (r == 2){ 
                tableQ[i][j] = 0.001;}
            else if (r == 3){ 
                tableQ[i][j] = -0.001;}
        }
    }
}

void affichageTable(float tableQ[NBPERCEPTION ][NBDEFENSES]){

    char nomperception[PERCEPTIONMAX][TAILLECHAR];
    strcpy(nomperception[0], "B   ");strcpy(nomperception[1], "M   ");strcpy(nomperception[2], "F   ");strcpy(nomperception[3], "BB  ");strcpy(nomperception[4], "FF  ");strcpy(nomperception[5], "MM  ");strcpy(nomperception[6], "BF  ");strcpy(nomperception[7], "BM  ");strcpy(nomperception[8], "FM  ");strcpy(nomperception[9], "BBB ");strcpy(nomperception[10], "FFF ");strcpy(nomperception[11], "MMM ");strcpy(nomperception[12], "BBF ");strcpy(nomperception[13], "BBM ");strcpy(nomperception[14], "FFB ");strcpy(nomperception[15], "FFM ");strcpy(nomperception[16], "MMB ");strcpy(nomperception[17], "MMF ");strcpy(nomperception[18], "MFB ");strcpy(nomperception[19], "BBBB");strcpy(nomperception[20], "FFFF");strcpy(nomperception[21], "MMMM");strcpy(nomperception[22], "BBBF");strcpy(nomperception[23], "BBBM");strcpy(nomperception[24], "FFFM");strcpy(nomperception[25], "FFFB");strcpy(nomperception[26], "MMMF");strcpy(nomperception[27], "MMMB");strcpy(nomperception[28], "BBMM");strcpy(nomperception[29], "BBFF");strcpy(nomperception[30], "BBFM");strcpy(nomperception[31], "FFMM");strcpy(nomperception[32], "FFBB");strcpy(nomperception[33], "FFBM");strcpy(nomperception[34], "MMFB");

    int i; 

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("    |         Defense Robot        |      Defense Robot Metal     |      Defense Robot Petit     |\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    for(i=0; i<NBPERCEPTION;i++){
        printf("%s|           %f                       %f                       %f            \n", nomperception[i], tableQ[i][0], tableQ[i][1], tableQ[i][2]);
    }
    printf("\n");
}

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

    int perception = 0;
    int defense = preferencelearning(perception, tableQ, epsilon);
    printf("defense a effectuer%d\n", defense);

    return 0;
}