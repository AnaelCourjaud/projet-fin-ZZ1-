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
    

    for (int j = 0; j < NBENNEMIVAGUE; j++)
    {
        int r = rand() % NBRTYPEINSECTES;
        if (r == BUGFIRE)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, indiceBugfirewalk, j);
            // printf(" creation vague juste après creer attaquant dans liste courants: indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", listeCourant[j]->spriteDeBase->indicePNG, listeCourant[j]->spriteDeBase->animation, listeCourant[j]->spriteDeBase->nbrImagesHorizontales, listeCourant[j]->spriteDeBase->nbrImagesVerticales, listeCourant[j]->spriteDeBase->prioriteAffichage);
            // printf(" creation vague juste après creer attaquant dans liste combattants : indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", tableauCombattants[j]->spriteCourant->spriteDeBase->indicePNG, tableauCombattants[j]->spriteCourant->spriteDeBase->animation, tableauCombattants[j]->spriteCourant->spriteDeBase->nbrImagesHorizontales, tableauCombattants[j]->spriteCourant->spriteDeBase->nbrImagesVerticales, tableauCombattants[j]->spriteCourant->spriteDeBase->prioriteAffichage);

            // for (int i = 0; i < tailleMaxSpritesCourants; i++)
            // {
            //     printf("listeCourrants[%d] == NULL : %d\n", i, listeCourant[i] == NULL);
            //     //  printf(" creation vague juste après creer attaquant dans liste courants: indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", listeCourant[i]->spriteDeBase->indicePNG, listeCourant[i]->spriteDeBase->animation, listeCourant[i]->spriteDeBase->nbrImagesHorizontales, listeCourant[i]->spriteDeBase->nbrImagesVerticales, listeCourant[i]->spriteDeBase->prioriteAffichage);
            // }
        }
        else if (r == FLY)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, indiceFlyWalk, j);
            // printf(" creation vague juste après creer attaquant dans liste courants: indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", listeCourant[j]->spriteDeBase->indicePNG, listeCourant[j]->spriteDeBase->animation, listeCourant[j]->spriteDeBase->nbrImagesHorizontales, listeCourant[j]->spriteDeBase->nbrImagesVerticales, listeCourant[j]->spriteDeBase->prioriteAffichage);
            // printf(" creation vague juste après creer attaquant dans liste combattants : indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", tableauCombattants[j]->spriteCourant->spriteDeBase->indicePNG, tableauCombattants[j]->spriteCourant->spriteDeBase->animation, tableauCombattants[j]->spriteCourant->spriteDeBase->nbrImagesHorizontales, tableauCombattants[j]->spriteCourant->spriteDeBase->nbrImagesVerticales, tableauCombattants[j]->spriteCourant->spriteDeBase->prioriteAffichage);

            // for (int i = 0; i < tailleMaxSpritesCourants; i++)
            // {
            //     printf("listeCourrants[%d] == NULL : %d\n", i, listeCourant[i] == NULL);
            // }
        }
        else if (r == MANTIS)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, indiceMantiswalk, j);
            // printf(" creation vague juste après creer attaquant dans liste courants: indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", listeCourant[j]->spriteDeBase->indicePNG, listeCourant[j]->spriteDeBase->animation, listeCourant[j]->spriteDeBase->nbrImagesHorizontales, listeCourant[j]->spriteDeBase->nbrImagesVerticales, listeCourant[j]->spriteDeBase->prioriteAffichage);
            // printf(" creation vague juste après creer attaquant dans liste combattants : indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", tableauCombattants[j]->spriteCourant->spriteDeBase->indicePNG, tableauCombattants[j]->spriteCourant->spriteDeBase->animation, tableauCombattants[j]->spriteCourant->spriteDeBase->nbrImagesHorizontales, tableauCombattants[j]->spriteCourant->spriteDeBase->nbrImagesVerticales, tableauCombattants[j]->spriteCourant->spriteDeBase->prioriteAffichage);

            // for (int i = 0; i < tailleMaxSpritesCourants; i++)
            // {
            //     printf("listeCourrants[%d] == NULL : %d\n", i, listeCourant[i] == NULL);
            // }
        }
        else
        {
            printf("erreur de création de vagues\n");
        }
    }
}

/*
void extractionEnnemisVivants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants], int nombreEnnemiParType[3][3])
{
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        if (listeCourants[i]->spriteDeBase->typeSprite == BUGFIRE)
        {
            nombreEnnemiParType[0][0]++;
        }
        else if (listeCourants[i]->spriteDeBase->typeSprite == FLY)
        {
            nombreEnnemiParType[1]++;
        }
        else if (listeCourants[i]->spriteDeBase->typeSprite == MANTIS)
        {
            nombreEnnemiParType[2]++;
        }
    }
}*/

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