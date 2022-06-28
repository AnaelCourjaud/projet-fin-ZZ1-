#include "riposte.h"

void calculStat(combattant_t tableauCombattants[NBENNEMIVAGUE], int valStat[2])
{
    // calcul les stats total d'attaque de la vague
    int physique = 0;
    int magie = 0;
    for (int i = 0; i++; i < NBENNEMIVAGUE)
    {
        physique += tableauCombattants[i].physiqueRestant;
        magie += tableauCombattants[i].magieRestante;
    }
    valStat[0] = physique;
    valStat[1] = magie;
}

void degatInfligé(combattant_t defenseur, combattant_t tableauCombattants[NBENNEMIVAGUE])
{
    // inflige les degats de sorte à tuer entiermeent des ennemis si possible
    int valStat[2];
    calculStat(tableauCombattants[NBENNEMIVAGUE], valStat[2]);
    valStat[0] -= defenseur.physiqueRestant;
    valStat[1] -= defenseur.magieRestante;
    int nbStatMagieNul = 0;
    while (nbStatMagieNul != NBENNEMIVAGUE)
    {
        for (int i = 0; i++; i < NBENNEMIVAGUE)
        {
        }
    }
}