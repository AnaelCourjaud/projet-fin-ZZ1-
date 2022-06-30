#include "analyseVague.h"


// int listeCompo[20][3] = {{BUGFIRE, -1, -1}, {FLY, -1, -1}, {MANTIS, -1, -1}, {BUGFIRE, BUGFIRE, -1}, {FLY, FLY, -1}, {MANTIS, MANTIS, -1}, {BUGFIRE, FLY, -1}, {BUGFIRE, MANTIS, -1}, {FLY, MANTIS, -1}, {BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, MANTIS}, {BUGFIRE, FLY, FLY}, {FLY, FLY, MANTIS}, {BUGFIRE, MANTIS, MANTIS}, {FLY, MANTIS, MANTIS}, {BUGFIRE, FLY, MANTIS}};

// int listeCompo[34][4] = {{BUGFIRE, -1, -1, -1}, {FLY, -1, -1, -1}, {MANTIS, -1, -1, -1}, {BUGFIRE, BUGFIRE, -1, -1}, {FLY, FLY, -1, -1}, {MANTIS, MANTIS, -1, -1}, {BUGFIRE, FLY, -1, -1}, {BUGFIRE, MANTIS, -1, -1}, {FLY, MANTIS, -1, -1}, {BUGFIRE, BUGFIRE, BUGFIRE, -1}, {FLY, FLY, FLY, -1}, {MANTIS, MANTIS, MANTIS, -1}, {BUGFIRE, BUGFIRE, FLY, -1}, {BUGFIRE, BUGFIRE, MANTIS, -1}, {BUGFIRE, FLY, FLY, -1}, {FLY, FLY, MANTIS, -1}, {BUGFIRE, MANTIS, MANTIS, -1}, {FLY, MANTIS, MANTIS, -1}, {BUGFIRE, FLY, MANTIS, -1}, {BUGFIRE, BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, BUGFIRE, MANTIS}, {BUGFIRE, FLY, FLY, FLY}, {FLY, FLY, FLY, MANTIS}, {BUGFIRE, MANTIS, MANTIS, MANTIS}, {FLY, MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY, FLY}, {BUGFIRE, BUGFIRE, FLY, MANTIS}, {FLY, FLY, MANTIS, MANTIS}, {BUGFIRE, FLY, FLY, MANTIS}, {BUGFIRE, FLY, MANTIS, MANTIS}};



int reconnaitreCompo( int listeCompo[NBCOMPO][NBENNEMIVAGUE], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    //---------Reformuler compo liste attaquant
    int compo[NBENNEMIVAGUE];
    int courdeb = 0;
    int courfin = NBENNEMIVAGUE - 1;
    for (int i = 0; i < NBENNEMIVAGUE; i++)
    {
        int valeur;
        if (tableauCombattants[i] == NULL)
            valeur = -1;
        else
        {

            switch (tableauCombattants[i]->typeCombattant)
            {
            case BUGFIRE:
                valeur = BUGFIRE;
                break;
            case FLY:
                valeur = FLY;
                break;
            case MANTIS:
                valeur = MANTIS;
                break;
            default:
                valeur = -1;
            }
        }
        if (valeur == -1)
        {
            compo[courfin] = valeur;
            courfin--;
        }
        else
        {
            compo[courdeb] = valeur;
            int cour = courdeb;
            while ((cour != 0) && (compo[cour] < compo[cour - 1]))
            {
                int temp = compo[cour];
                compo[cour] = compo[cour - 1];
                compo[cour - 1] = temp;
                cour--;
            }
            courdeb++;
        }
    }
    //-------Reconnaitre num compo
    int indice = -1;
    int combReconnu = 0;
    while (combReconnu != 3)
    {
        indice++;
        int j = 0;
        while ((j < NBENNEMIVAGUE) && (listeCompo[indice][j] == compo[j]))
            j++;
        combReconnu = j;
    }
    return indice;
}

// int main()
// {

//     combattant_t *tableauCombattants[NBRMAXCOMBATTANTS];
//     creerAttaquant(tableauCombattants, indiceBugfirewalk, 2);
//     creerAttaquant(tableauCombattants, indiceBugfirewalk, 1);
//     creerAttaquant(tableauCombattants, indiceMantiswalk, 0);
//     // tableauCombattants[0] = NULL;
//     int listeCompo[20][3] = {{BUGFIRE, -1, -1}, {FLY, -1, -1}, {MANTIS, -1, -1}, {BUGFIRE, BUGFIRE, -1}, {FLY, FLY, -1}, {MANTIS, MANTIS, -1},
//      {BUGFIRE, FLY, -1}, {BUGFIRE, MANTIS, -1}, {FLY, MANTIS, -1}, {BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY},
//       {MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, MANTIS}, {FLY, FLY, BUGFIRE},{FLY, FLY, MANTIS},
//        {MANTIS, MANTIS, BUGFIRE}, {MANTIS, MANTIS, FLY}, {BUGFIRE, FLY, MANTIS}};
//     int compo[3];
//     int retour = reconnaitreCompo(compo, listeCompo, tableauCombattants);
//     // for (int i = 0; i < 3; i++)
//     // {
//     //     printf("ennemi%d: %d\n", i, compo[i]);
//     // }
//     printf("compo n°%d", retour);
//     return retour;
// }