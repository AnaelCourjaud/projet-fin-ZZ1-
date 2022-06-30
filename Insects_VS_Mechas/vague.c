#include "vague.h"

/*
void TotalAttaque(insecte_t tableauAttaque[TAILLEMAX], int *totalphysique, int *totalmagie, int nbrEnnemis)
{
    int i = 0;

    for (; i < nbrEnnemis; i++){
        *totalphysique += tableauAttaque[i].statPhysique;
        *totalmagie += tableauAttaque[i].statMagie;
    }
}*/

void creationVague(spriteBase_t *spritesDeBase[NBRTEXTURES], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], spriteCourant_t *listeCourant[tailleMaxSpritesCourants]) // il faut bien que listeCombattants soit vide à l'execution de cette fonction
{
    float xSpone = 1.0;

    for (int j = 0; j < NBENNEMIVAGUE; j++)
    {
        int r = rand() % NBRTYPEINSECTES;
        if (r == BUGFIRE)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, BUGFIRE, WALK, j, xSpone, 0.5);
        }
        else if (r == FLY)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, FLY, WALK, j, xSpone, 0.5);
        }
        else if (r == MANTIS)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, MANTIS, WALK, j, xSpone, 0.5);
        }
        else
        {
            printf("erreur de création de vagues\n");
        }
        xSpone += 0.1;
    }
}

// utilisation de pointeurs !!!!! on appelle donc la fonction de cette maniere : TotalAttaque(tableauAttaque, &totalphysique, &totalmagie, nbrEnnemis);

/*
int main()
{
    insecte_t bug;
    bug.statPhysique = 2;
    bug.statMagie = 3;
    insecte_t bug2;
    bug2.statPhysique = 2;
    bug2.statMagie = 3;
    int totalphysique = 0; int totalmagie = 0;

    insecte_t tableauAttaque[TAILLEMAX];
    tableauAttaque[0] = bug;
    tableauAttaque[1] = bug2;
    TotalAttaque(tableauAttaque, &totalphysique, &totalmagie, 2);
    printf("physique : %d, magie : %d", totalphysique, totalmagie);

}
*/