#include "resolution.h"

int gagnant(int etat[2])
{
    // 0: perso gagne; 1:ennemi gagne; 2: meme attaque; 3 : au moins une defense
    int duel[4][4] = {{2, 0, 1, 3}, {1, 2, 0, 3}, {0, 1, 2, 3}, {3, 3, 3, 2}};
    return duel[etat[0]][etat[1]];
}

void resolutionPV(int PV[], int resultat, int etat[])
{
    int degat[3] = {2, 3, 1}; // degat des attaques eau, feu et terre
    if (resultat == 0)
    { // si le perso a gagné
        PV[1] = PV[1] - degat[etat[0]];
    }
    if (resultat == 1)
    { // si l'ennemi a gagné
        PV[0] = PV[0] - degat[etat[1]];
    }
    // si meme attaque ou si defense, pas de changemement de PV
}

int defaite(int etat[2])
{
    // renvoie l'etat contre lequel gagne l'ennemi
    int etatperdant;
    printf("etatEnnemi:"
           "%d\n",
           etat[1]);
    switch (etat[1])
    {
    case EAU:
        etatperdant = FEU;
        break;
    case FEU:
        etatperdant = TERRE;
        break;
    case TERRE:
        etatperdant = EAU;
        break;
    case DEFENSE:
        etatperdant = DEFENSE;
        break;
    }
    return etatperdant;
}

void reussitedefense(int etat[2], int etatprec)
{
    srand(time(NULL));
    int pourcentEtat = rand() % 100;
    printf("%d\n", pourcentEtat);
    if (etat[0] == 3)
    { // si le perso tente une defense
        switch (etatprec)
        {
        case TERRE:
            if (pourcentEtat < 50)
                etat[0] = defaite(etat);
            break;
        case EAU:
            if (pourcentEtat < 40)
                etat[0] = defaite(etat);
            break;
        case FEU:
            if (pourcentEtat < 30)
                etat[0] = defaite(etat);
            break;
        case DEFENSE:
            etat[0] = defaite(etat);
        }
    }
}

void changement(int etat[])
{
    srand(time(NULL));
    int changementEtat[4][3] = {{10, 45, 80}, // tableaux des transitions de Markov
                                {50, 60, 90},
                                {40, 60, 70},
                                {33, 66, 100}};
    int pourcentEtat = rand() % 100;
    printf("%d\n", pourcentEtat);
    int i = 0;
    while ((changementEtat[etat[1]][i] < pourcentEtat) && (i < 3))
        i++;
    etat[1] = i;
}

int main()
{
    // int PV[2] = {10, 6};
    int etat[2] = {FEU, EAU};
    int etatprec = DEFENSE;
    int nouvetat = defaite(etat);
    printf("ancienEtat:"
           "%d\n",
           etat[0]);
    printf("nouvEtat:"
           "%d\n",
           nouvetat);
    reussitedefense(etat, etatprec);
    printf("nouvEtateffectif:"
           "%d\n",
           etat[0]);
    return 0;
}