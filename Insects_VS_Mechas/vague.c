# include "vague.h"
/*
void TotalAttaque(insecte_t tableauAttaque[TAILLEMAX], int *totalphysique, int *totalmagie, int nbrEnnemis) 
{
    int i = 0;

    for (; i < nbrEnnemis; i++){
        *totalphysique += tableauAttaque[i].statPhysique;
        *totalmagie += tableauAttaque[i].statMagie;
    }
}*/

void creationVague(combattant_t *tableauCombattants[NBENNEMIVAGUE], spriteCourant_t *listeCourant[tailleMaxSpritesCourants])
{
    srand(time(NULL));

    int r ;
    for (i=0; i < NBENNEMIVAGUE ;i++){
        rand() % NBENNEMIVAGUE;
        if(r == 0){
            creerCombattant(tableauCombattants[NBENNEMIVAGUE],listeCourant[tailleMaxSpritesCourants], indiceBugfirewalk);
        }
        if(r == 1){
            creerCombattant(tableauCombattants[NBENNEMIVAGUE],listeCourant[tailleMaxSpritesCourants],indiceFlyvolant);
        }
        if(r == 2){
            creerCombattant(tableauCombattants[NBENNEMIVAGUE],listeCourant[tailleMaxSpritesCourants],indiceMantiswalk);
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

//utilisation de pointeurs !!!!! on appelle donc la fonction de cette maniere : TotalAttaque(tableauAttaque, &totalphysique, &totalmagie, nbrEnnemis);

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