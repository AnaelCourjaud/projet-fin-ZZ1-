#include "apprentissage.h"

void gestionTable(float tableQ[NBETATS][NBDEFENSES], int tablesauv[2][NBETATS], float gamma, float epsilon)
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
                       
int tailleTableau(int tablesauv[2][NBETATS]){

    int taille = 0;

    while(tablesauv[0][taille] != 1000)
    {
        taille += 1;
    }
    return taille;
}

void initTableQ(float tableQ[NBETATS][NBDEFENSES])
{
    int i; int j;

    for(i=0; i<NBETATS; i++){
        for(j=0; j<NBDEFENSES; j++)
        {
            tableQ[i][j] = 0;
        }
    }
}

void affichageTable(float tableQ[NBETATS][NBDEFENSES]){

    char nomperception[ETATMAX][TAILLECHAR];
    strcpy(nomperception[0], "B   ");strcpy(nomperception[1], "M   ");strcpy(nomperception[2], "F   ");strcpy(nomperception[3], "BB  ");strcpy(nomperception[4], "FF  ");strcpy(nomperception[5], "MM  ");strcpy(nomperception[6], "BF  ");strcpy(nomperception[7], "BM  ");strcpy(nomperception[8], "FM  ");strcpy(nomperception[9], "BBB ");strcpy(nomperception[10], "FFF ");strcpy(nomperception[11], "MMM ");strcpy(nomperception[12], "BBF ");strcpy(nomperception[13], "BBM ");strcpy(nomperception[14], "FFB ");strcpy(nomperception[15], "FFM ");strcpy(nomperception[16], "MMB ");strcpy(nomperception[17], "MMF ");strcpy(nomperception[18], "MFB ");strcpy(nomperception[19], "BBBB");strcpy(nomperception[20], "FFFF");strcpy(nomperception[21], "MMMM");strcpy(nomperception[22], "BBBF");strcpy(nomperception[23], "BBBM");strcpy(nomperception[24], "FFFM");strcpy(nomperception[25], "FFFB");strcpy(nomperception[26], "MMMF");strcpy(nomperception[27], "MMMB");strcpy(nomperception[28], "BBMM");strcpy(nomperception[29], "BBFF");strcpy(nomperception[30], "BBFM");strcpy(nomperception[31], "FFMM");strcpy(nomperception[32], "FFBB");strcpy(nomperception[33], "FFBM");strcpy(nomperception[34], "MMFB");

    int i; 
    printf("    |     Defense Robot     |  Defense Robot Metal  |  Defense Robot Petit  |\n");
    printf("-----------------------------------------------------------------------------\n");
    for(i=0; i<NBETATS;i++){
        printf("%s|           %f           |           %f           |           %f           |\n", nomperception[i], tableQ[i][0], tableQ[i][1], tableQ[i][2]);
    }
}

int main()
{
    float tableQ[NBETATS][NBDEFENSES];
    float epsilon = 1.0;
    float gamma = 0.5;

    int tablesauv[2][NBETATS];
    tablesauv[0][0] = 0; tablesauv[1][0] = 0;
    tablesauv[0][1] = 4; tablesauv[1][1] = 2;
    tablesauv[0][2] = 9; tablesauv[1][2] = 1;
    tablesauv[0][3] = 12; tablesauv[1][3] = 0;
    tablesauv[0][4] = 1000;

    initTableQ(tableQ);

    gestionTable(tableQ, tablesauv, gamma, epsilon);
    affichageTable(tableQ);

}