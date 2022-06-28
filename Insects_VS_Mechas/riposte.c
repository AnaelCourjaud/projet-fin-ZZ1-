#include "riposte.h"

void calculStat(combattant_t tableauCombattants[NBENNEMIVAGUE+1], int valStat[2])
{
    // calcul les stats total d'attaque de la vague
    int physique = 0;
    int magie = 0;
    for (int i = 0; i++; i < NBENNEMIVAGUE+1)
    {
        if (type)
        physique += tableauCombattants[i].physiqueRestant;
        magie += tableauCombattants[i].magieRestante;
    }
    valStat[0] = physique;
    valStat[1] = magie;
}


int nbEnnemis(combattant_t tableauCombattants[NBENNEMIVAGUE]){
    int compteur = 0;
    int i =0;
    while(tableauCombattants[i] != NULL) compteur ++;
    return (compteur - 1);
}


void degatInfligé(combattant_t tableauCombattants[NBENNEMIVAGUE])
{
    // inflige les degats de sorte à tuer entiermeent des ennemis si possible
    int nbInsecte = nbEnnemis(combattant_t tableauCombattants[NBENNEMIVAGUE]);
    //calculStat(tableauCombattants[NBENNEMIVAGUE], valStat[2]);
    //valStat[0] -= defenseur.physiqueRestant;
    //valStat[1] -= defenseur.magieRestante;
    int nbStatMagieNul = 0;
    while ((tableauCombattants[nbInsecte].magieRestante != 0) && (nbStatMagieNul != nbInsecte))
    //
    {
        indmax = 0
        for (int i = 0; i++; i < NBENNEMIVAGUE)
        {
            if (tableauCombattants[i].magieRestante == 0) nbStatMagieNul ++;
            if (tableauCombattants[i].magieRestante > tableauCombattants[indmax].magieRestante) indmax = i;        
        }
        if (nbStatMagieNul != NBENNEMIVAGUE){
            int degat = tableauCombattants[i].magieRestante - defenseur.magieRestante;
            if (degat<0){
                tableauCombattants[i].magieRestante -= defenseur.magieRestante;
                defenseur.magieRestante = 0;
            }
            else {
                tableauCombattants[i].magieRestante = 0;
                defenseur.magieRestante -= tableauCombattants[i].magieRestante;
            }
        }
    }
}