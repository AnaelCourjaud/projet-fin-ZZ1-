# include "vague.h"

void TotalAttaque(insecte_t tableauAttaque[TAILLEMAX], int *totalphysique, int *totalmagie, int nbrEnnemis) 
{
    int i = 0;

    for (; i < nbrEnnemis; i++){
        *totalphysique += tableauAttaque[i].statPhysique;
        *totalmagie += tableauAttaque[i].statMagie;
    }
}

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