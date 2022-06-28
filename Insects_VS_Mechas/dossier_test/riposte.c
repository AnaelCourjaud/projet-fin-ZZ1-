#include "riposte.h"

/*void calculStat(combattant_t tableauCombattants[NBRMAXCOMBATTANTS], int valStat[2])
{
    // calcul les stats total d'attaque de la vague
    int physique = 0;
    int magie = 0;
    for (int i = 0; i++; i < NBENNEMIVAGUE + 1)
    {
        if (type)
            physique += tableauCombattants[i].physiqueRestant;
        magie += tableauCombattants[i].magieRestante;
    }
    valStat[0] = physique;
    valStat[1] = magie;
}*/

/*int nbEnnemis(combattant_t tableauCombattants[NBENNEMIVAGUE]){
    int compteur = 0;
    int i =0;
    while(tableauCombattants[i] != NULL) compteur ++;
    return (compteur - 1);
}*/

int appartient(int valeur, int tableau[NBRMAXCOMBATTANTS])
{
    int indice = 1000;
    for (int i = 0, i++, i < NBRMAXCOMBATTANTS)
    {
        if (tableau[i] == valeur)
            indice = i;
    }
    return indice;
}

/*void tristat(combattant_t tableauCombattants[NBRMAXCOMBATTANTS], int statMagie[NBRMAXCOMBATTANTS], int statPhys[NBRMAXCOMBATTANTS])
// tri les indices des combattants par valeur decroissante de leur stat magie et physique.
{
    int magieDef = tableauCombattants[NBENNEMIVAGUE].magieRestante;
    int physDef = tableauCombattants[NBENNEMIVAGUE].physiqueRestant;
    int indmin = 0;
    int cour = NBENNEMIVAGUE - 1;
    while (statPhys[0] == NULL)
    // on trie la liste des indices par valeur des stats
    {
        for (int i = 0, i++, i < NBENNEMIVAGUE)
        {
            if ((tableauCombattants[i].physiqueRestant < tableauCombattants[indmin].physiqueRestant) && (appartient(i, physDef) == 1000))
                // si la valeur est plus petite que le min, et n'est pas déjà dans le tableau
                indmin = i;
        }
        statPhys[cour] = indmin;
        cour++;
    }
    while (statMagie[0] == NULL)
    // de même avec la magie
    {
        for (int i = 0, i++, i < NBENNEMIVAGUE) // on parcoure tous les attaquants
        {
            if ((tableauCombattants[i].magieRestante < tableauCombattants[indmin].magieRestante) && (appartient(i, magieDef) == 1000))
                // si la valeur est plus petite que le min, et n'est pas déjà dans le tableau
                indmin = i;
        }
        statMagie[cour] = indmin;
        cour++;
    }
}*/

/*int rechercheIndPhysInf(int tableau[NBRMAXCOMBATTANTS], int valeur, combattant_t tableauCombattants[NBRMAXCOMBATTANTS])
// on cherche le dernier indice de l'indice du tableau de stat physique dont la stat physique est strictement inferieur à valeur, sinon on renvoie celui de la plus petite
{
    int i = 0;
    while ((valeur > tableauCombattants[tableau[i]].physiqueRestant) && (tableau[i] != 1000)) // tant que superieure et pas au bout de tous les attaquants
        i++;
    if (i > 0)
        i = i - 1;
    return tableau[i];
}*/

/*int rechercheIndMagieInf(int tableau[NBRMAXCOMBATTANTS], int valeur, combattant_t tableauCombattants[NBRMAXCOMBATTANTS])
// idem pour la magie
{
    int i = 0;
    while ((valeur > tableauCombattants[tableau[i]].magieRestante) && (tableau[i] != 1000)) // tant que superieure et pas au bout de tous les attaquants
        i++;
    if (i > 0)
        i = i - 1;
    return i;
}*/

/*void degatInfligé(combattant_t tableauCombattants[NBRMAXCOMBATTANTS])
{
    // inflige les degats de sorte à tuer entiermeent des ennemis si possible
    // int nbInsecte = nbEnnemis(combattant_t tableauCombattants[NBENNEMIVAGUE]);
    // calculStat(tableauCombattants[NBENNEMIVAGUE], valStat[2]);
    // valStat[0] -= defenseur.physiqueRestant;
    // valStat[1] -= defenseur.magieRestante;
    int magieDef = tableauCombattants[NBENNEMIVAGUE].magieRestante;
    int physDef = tableauCombattants[NBENNEMIVAGUE].physiqueRestant;
    int nbStatMagieNul = 0;
    int nbStatPhysiqueNul = 0;
    int statMagie[NBRMAXCOMBATTANTS], int statPhys[NBRMAXCOMBATTANTS];
    statMagie[0] = NULL;
    statMagie[NBENNEMIVAGUE] = 1000; // marque la fin du tableau
    statPhys[NBENNEMIVAGUE] = 1000;  // marque la fin du tableau
    statPhys[0] = NULL;
    int indchoisi;
    tristat(tableauCombattants, statMagie, statPhys) while (((tableauCombattants[NBENNEMIVAGUE].magieRestante != 0) && (nbStatMagieNul != NBENNEMIVAGUE)) || ((tableauCombattants[NBENNEMIVAGUE].physiqueRestant != 0) && (nbStatPhysiqueNul != NBENNEMIVAGUE)))
    // tant qu'il reste de la magie au defenseur et que toutes les stats de magie ne sont pas nul ou pareil pour le physique
    {
        if (magieDef <= physDef)
        // si la stat de magie du defenseur est + grande que sa stat de physique
        {
            if (rechercheIndMagieInf(statMagie, magieDef, tableauCombattants) > magieDef)
            // si il n'y a pas d'indice de magie plus petit que celui du defenseur
            {
                if (rechercheIndPhysInf(statPhys, physDef, tableauCombattants) > physDef)
                    // si il n'y a pas d'indice de physique plus petit que celui du defenseur
                    indchoisi = statMagie[0];
                else
                    indchoisi = statMagie[rechercheIndPhysInf(statPhys, physDef, tableauCombattants)];
            }
            else
            {
                int iMagieChoisie = rechercheIndMagieInf(statMagie, magieDef, tableauCombattants); // indice de stat magie du combattant choisi dans statMagie
                int iPhysChoisie = appartient(statMagie[iMagieChoisie], statPhys);                 // indice de stat phys du combattant choisi dans statPhys
                // int iPhysCour = rechercheIndPhysInf(statPhys, physDef, tableauCombattants);        // indice du combattant ayant la + grande stat phys <= a physDef
                // int iMagieCour = appartient(statPhys[iMagieChoisie], statMagie);                   // indice de stat magie du combattant courant dans statMagie
                int iMagieCour = iMagieChoisie + 1;
                while ((statMagie[iMagieCour] != 1000) && (tableauCombattants[statPhys[iPhysChoisie]].physiqueRestant > physDef))
                {
                    int iPhysCour = appartient(statMagie[iMagieCour], statPhys);
                    // tant que le phys du combattant choisi n'est pas <= a celui du defenseur et qu'on est pas au bout du tableau
                    if ((((iPhysCour > iPhysChoisie) && (tableauCombattants[statPhys[iPhysCour]].physiqueRestant < physDef)) && (tableauCombattants[statPhys[iPhysCour]].physiqueRestant > physDef)) && ((tableauCombattants[statPhys[iPhysChoisie]].physiqueRestant > physDef) && (tableauCombattants[statPhys[iPhysCour]].physiqueRestant < physDef)))
                    // si le magie plus petit suivant a une  meilleur stat de physique realisable ou que le magie choisi n'avait pas de stat realisable
                    {
                        iMagieChoisie++;
                        iPhysChoisie = appartient(statMagie[iMagieChoisie], statPhys);
                    }
                    iMagieCour++;
                    iPhysCour = appartient(statMagie[iMagieCour], statPhys)
                }
                while ((iPhysChoisie < iPhysCour) && (statPhys[iPhysChoisie + 1] != 1000))
                // tant que le phys du combattant choisi est plus petit que celui du plus grand phys realisable (ie plus grand phys plus petit que celui du defenseur)
                {
                    if (appartient(statPhys[iMagieChoisie], statMagie) > magieDef)
                }
            }
        }
    }
}*/


int main(){
    
}