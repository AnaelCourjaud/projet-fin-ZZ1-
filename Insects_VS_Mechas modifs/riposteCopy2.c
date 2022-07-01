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

int appartient(int valeur, int tableau[NBENNEMIVAGUE])
{
    int indice = 1000;
    int i = 0;
    for (i = 0; i < NBENNEMIVAGUE; i++)
    {
        if (tableau[i] == valeur)
            indice = i;
    }
    return indice;
}

void initValNull(int listeIndice[NBENNEMIVAGUE], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    // initalise sur 0 les insectes de la vague qui sont NULL dans une liste d'indice dont les valeurs sont initialisées à 999
    int cour = 0;
    for (int i = 0; i < NBENNEMIVAGUE; i++)
    {
        if (tableauCombattants[i] == NULL)
        {
            listeIndice[cour] = i;
            creerAttaquantSansSprite(tableauCombattants, i);
            tableauCombattants[i]->physiqueRestant = 0;
            tableauCombattants[i]->magieRestante = 0;
            cour++;
        }
    }
}

void supprValNull(int listIndice[NBENNEMIVAGUE], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    // met sur NULL les insectes de la vague qui étaient NULL au départ à l'aide de la liste d'indice dont les valeurs sont initialisées à 999
    for (int i = 0; i < NBENNEMIVAGUE; i++)
    {
        if (listIndice[i] != 999)
        {
            int cour = 0;
            int indiceCombattantVide = listIndice[i];
            free(tableauCombattants[indiceCombattantVide]);
            tableauCombattants[indiceCombattantVide] = NULL;
        }
    }
}

void tristat(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], int statMagie[NBRMAXCOMBATTANTS], int statPhys[NBRMAXCOMBATTANTS])
// tri les indices des combattants par valeur decroissante de leur stat magie et physique.
{
    // printf("AAAAAAAAAAAA llleme valeur Phys: %d\n", tableauCombattants[0]->physiqueRestant);
    int indmax = 0;
    int cour = 0;

    while (statPhys[NBENNEMIVAGUE - 1] == 999)
    // on trie la liste des indices par valeur des stats
    {
        indmax = 0;
        // printf("debut while tristat\n");
        // printf("indmaxP0 : %d\n", (appartient(indmax, statPhys)));
        while (appartient(indmax, statPhys) != 1000)
        {
            // printf("indmaxP0 : %d\n", (appartient(indmax, statPhys)));
            indmax++;
            // printf("indmax : %d\n", indmax);
        }
        // printf("indmaxP1 : %d\n", indmax);
        // printf("indmax1:%d\n", indmax);
        if (indmax == NBENNEMIVAGUE)
            indmax = indmax - 1;
        for (int i = 0; i < NBENNEMIVAGUE; i++)
        {
            // printf("%deme valeur Phys: %d\n", i, tableauCombattants[i]->physiqueRestant);
            // while((appartient(indmax, statPhys) != 1000)) indmax ++;
            // printf("debut for tristat\n");
            if ((tableauCombattants[i]->physiqueRestant >= tableauCombattants[indmax]->physiqueRestant) && (appartient(i, statPhys) == 1000))
            {
                // si la valeur est plus grande que le max, et n'est pas déjà dans le tableau
                indmax = i;
                // printf("debut if2 tristat\n");
            }
            while ((indmax < NBENNEMIVAGUE) && (appartient(tableauCombattants[indmax]->physiqueRestant, statPhys) != 1000))
            {
                indmax++;
                // printf("debut if2 tristat\n");
            }
            // printf("indmaxP2 : %d\n", indmax);
            // printf("i : %d\n", i);
        }
        if (indmax == NBENNEMIVAGUE)
            indmax = indmax - 1;
        statPhys[cour] = indmax;
        // printf("%d\n", statPhys[cour]);
        cour++;
        // printf("indmax2:%d\n", indmax);
    }

    indmax = 0;
    cour = 0;
    while (statMagie[NBENNEMIVAGUE - 1] == 999)
    // de même avec la magie
    {
        indmax = 0;
        while ((appartient(indmax, statMagie) != 1000))
            indmax++;
        // printf("%d\n", indmax);
        if (indmax == NBENNEMIVAGUE)
            indmax = indmax - 1;
        for (int i = 0; i < NBENNEMIVAGUE; i++)
        {
            // printf("%deme valeur Magie: %d\n", i, tableauCombattants[i]->magieRestante);
            // while((appartient(indmax, statPhys) != 1000)) indmax ++;
            if ((tableauCombattants[i]->magieRestante >= tableauCombattants[indmax]->magieRestante) && (appartient(i, statMagie) == 1000))
                // si la valeur est plus grande que le max, et n'est pas déjà dans le tableau
                indmax = i;
            while ((indmax < NBENNEMIVAGUE) && (appartient(indmax, statMagie) != 1000))
                indmax++;
            // printf("indmaxM : %d\n", indmax);
        }
        if (indmax == NBENNEMIVAGUE)
            indmax = indmax - 1;
        statMagie[cour] = indmax;
        // printf("%d\n", statMagie[cour]);
        cour++;
    }
}

int rechercheIndPhysInf(int tableau[NBRMAXCOMBATTANTS], int valeur, combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
// on cherche le dernier indice de l'indice du tableau de stat physique dont la stat physique est strictement inferieur à valeur, sinon on renvoie celui de la plus petite
{
    int i = 0;
    // printf("tableau%d:%d\n",i, tableauCombattants[tableau[i]]->physiqueRestant);
    while ((i < NBENNEMIVAGUE) && (valeur < tableauCombattants[tableau[i]]->physiqueRestant))
    { // tant que superieure et pas au bout de tous les attaquants
        // printf("%d\n", tableau[i]);
        // printf("tableau%d:%d\n",i, tableauCombattants[tableau[i]]->physiqueRestant);
        i++;
    }
    // printf("%dfin", i);
    if (i == NBENNEMIVAGUE)
        i = i - 1;
    return i;
}

int rechercheIndMagieInf(int tableau[NBRMAXCOMBATTANTS], int valeur, combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
// idem pour la magie
{
    int i = 0;
    while ((i < NBENNEMIVAGUE) && (valeur < tableauCombattants[tableau[i]]->magieRestante)) // tant que superieure et pas au bout de tous les attaquants
        i++;
    if (i == NBENNEMIVAGUE)
        i = i - 1;
    return i;
}

int rechercheMagieNulle(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    int nbStatMagieNul = 0;
    for (int i = 0; i < NBENNEMIVAGUE; i++)
    {
        if (tableauCombattants[i]->magieRestante == 0)
            nbStatMagieNul++;
    }
    return nbStatMagieNul;
}

int recherchePhysNulle(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    int nbStatPhysNul = 0;
    for (int i = 0; i < NBENNEMIVAGUE; i++)
    {
        if (tableauCombattants[i]->physiqueRestant == 0)
            nbStatPhysNul++;
    }
    return nbStatPhysNul;
}

void degatInflige(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    // inflige les degats de sorte à tuer entierEment des ennemis si possible
    // int nbInsecte = nbEnnemis(combattant_t tableauCombattants[NBENNEMIVAGUE]);
    // calculStat(tableauCombattants[NBENNEMIVAGUE], valStat[2]);
    // valStat[0] -= defenseur.physiqueRestant;
    // valStat[1] -= defenseur.magieRestante;
    // printf("DEBUT\n");
    //--------init variable
    int listeIndice[NBENNEMIVAGUE];
    for (int i = 0; i < NBENNEMIVAGUE; i++)
        listeIndice[i] = 999;
    initValNull(listeIndice, tableauCombattants);
    int magieDef = tableauCombattants[NBENNEMIVAGUE]->magieRestante;
    // printf("magieDefFonc: %d\n", magieDef);
    int physDef = tableauCombattants[NBENNEMIVAGUE]->physiqueRestant;
    // printf("physDefFonc: %d\n", physDef);
    int nbStatMagieNul = rechercheMagieNulle(tableauCombattants);
    // printf("0\n");
    int nbStatPhysiqueNul = recherchePhysNulle(tableauCombattants);
    // printf("1\n");
    int statMagie[NBRMAXCOMBATTANTS];
    int statPhys[NBRMAXCOMBATTANTS];
    for (int i = 0; i < NBENNEMIVAGUE; i++)
    {
        statMagie[i] = 999;
        statPhys[i] = 999;
    }
    statMagie[NBENNEMIVAGUE] = 1000; // marque la fin du tableau
    statPhys[NBENNEMIVAGUE] = 1000;  // marque la fin du tableau
    int indchoisi;
    // printf("2\n");
    tristat(tableauCombattants, statMagie, statPhys);
    // printf("avant debut while\n");
    // printf("Stat ennemi0 avec degat: %d %d \n", tableauCombattants[0]->physiqueRestant, tableauCombattants[0]->magieRestante);
    // printf("Stat ennemi1 avec degat: %d %d \n", tableauCombattants[1]->physiqueRestant, tableauCombattants[1]->magieRestante);
    // printf("Stat ennemi2 avec degat: %d %d \n", tableauCombattants[2]->physiqueRestant, tableauCombattants[2]->magieRestante);

    while ((
               (tableauCombattants[NBENNEMIVAGUE]->magieRestante != 0) && (nbStatMagieNul != NBENNEMIVAGUE)) ||
           ((tableauCombattants[NBENNEMIVAGUE]->physiqueRestant != 0) && (nbStatPhysiqueNul != NBENNEMIVAGUE)))
    // tant qu'il reste de la magie au defenseur et que toutes les stats de magie ne sont pas nul ou pareil pour le physique
    {
        // printf("DEBUT while\n");
        //----------Choix de l'insecte a buté
        if (((magieDef > physDef) && (nbStatMagieNul != NBENNEMIVAGUE)) || ((magieDef <= physDef) && (nbStatPhysiqueNul == NBENNEMIVAGUE)))
        // si la stat de magie du defenseur est + grande que sa stat de physique
        {
            // printf("debut if magie\n");
            // printf("indmagiemin: %d\n", rechercheIndMagieInf(statMagie, magieDef, tableauCombattants));
            if ((tableauCombattants[statMagie[rechercheIndMagieInf(statMagie, magieDef, tableauCombattants)]]->magieRestante > magieDef) || (tableauCombattants[statMagie[rechercheIndMagieInf(statMagie, magieDef, tableauCombattants)]]->magieRestante == 0))
            // si il n'y a pas d'indice de magie plus petit que celui du defenseur ou que la stat magie + petite est nulle
            {
                // printf("debut if magie grand\n");
                // printf("stat phys:%d\n", rechercheIndPhysInf(statPhys, physDef, tableauCombattants));
                if ((physDef == 0) || (nbStatPhysiqueNul == NBENNEMIVAGUE) || ((tableauCombattants[statPhys[rechercheIndPhysInf(statPhys, physDef, tableauCombattants)]]->physiqueRestant > physDef) && (statMagie[0] != 0)))
                // si il n'y a pas d'indice de physique plus petit que celui du defenseur && que le max de magie est non nul
                {
                    // printf("debut if magie max\n");
                    indchoisi = statMagie[0];
                }
                else if ((tableauCombattants[statPhys[rechercheIndPhysInf(statPhys, physDef, tableauCombattants)]]->physiqueRestant != 0))
                {
                    // printf("debut if phys petit\n");
                    indchoisi = statPhys[rechercheIndPhysInf(statPhys, physDef, tableauCombattants)];
                }
                else // si le plus haute stat phys attaquant completement killable est nulle
                {
                    // printf("debut if ĥys max\n");
                    indchoisi = statPhys[0];
                }
                // printf("indchoisi0:%d\n", indchoisi);
            }
            else
            {
                // printf("debut if magie petit\n");
                int iMagieChoisie = rechercheIndMagieInf(statMagie, magieDef, tableauCombattants); // indice de stat magie du combattant choisi dans statMagie
                int iPhysChoisie = appartient(statMagie[iMagieChoisie], statPhys);                 // indice de stat phys du combattant choisi dans statPhys
                // int iPhysCour = rechercheIndPhysInf(statPhys, physDef, tableauCombattants);        // indice du combattant ayant la + grande stat phys <= a physDef
                // int iMagieCour = appartient(statPhys[iMagieChoisie], statMagie);                   // indice de stat magie du combattant courant dans statMagie
                // printf("indchoisi1b:%d\n", iMagieChoisie);
                int iMagieCour = iMagieChoisie + 1;
                // printf("statMagie[iMagieCour]:%d\n", statMagie[iMagieCour]);
                while ((statMagie[iMagieCour] != 1000) && (tableauCombattants[statPhys[iPhysChoisie]]->physiqueRestant > physDef))
                {
                    int iPhysCour = appartient(statMagie[iMagieCour], statPhys);
                    // tant que le phys du combattant choisi n'est pas <= a celui du defenseur et qu'on est pas au bout du tableau
                    if ((((iPhysCour > iPhysChoisie) && (tableauCombattants[statPhys[iPhysCour]]->physiqueRestant < physDef)) && (tableauCombattants[statPhys[iPhysCour]]->physiqueRestant > physDef)) && ((tableauCombattants[statPhys[iPhysChoisie]]->physiqueRestant > physDef) && (tableauCombattants[statPhys[iPhysCour]]->physiqueRestant < physDef)))
                    // si le magie plus petit suivant a une  meilleur stat de physique realisable ou que le magie choisi n'avait pas de stat realisable
                    {
                        // printf("indchoisi1:%d\n", statMagie[iMagieChoisie]);
                        iMagieChoisie++;
                        iPhysChoisie = appartient(statMagie[iMagieChoisie], statPhys);
                    }
                    iMagieCour++;
                    iPhysCour = appartient(statMagie[iMagieCour], statPhys);
                }
                indchoisi = statMagie[iMagieChoisie];
                // while ((iPhysChoisie < iPhysCour) && (statPhys[iPhysChoisie + 1] != 1000))
                // // tant que le phys du combattant choisi est plus petit que celui du plus grand phys realisable (ie plus grand phys plus petit que celui du defenseur)
                // {
                //     if (appartient(statPhys[iMagieChoisie], statMagie) > magieDef)
                // }
                // printf("indchoisi2:%d\n", indchoisi);
            }
        }
        else
        // si la stat de physique du defenseur est + grande que sa stat de magie
        {
            // printf("debut if physique\n");
            if ((tableauCombattants[statPhys[rechercheIndPhysInf(statPhys, physDef, tableauCombattants)]]->physiqueRestant > physDef) || (tableauCombattants[statPhys[rechercheIndPhysInf(statPhys, physDef, tableauCombattants)]]->physiqueRestant == 0))
            // si il n'y a pas d'indice de magie plus petit que celui du defenseur
            {
                // printf("debut if phys grand\n");
                if ((magieDef == 0) || (nbStatMagieNul == NBENNEMIVAGUE) || ((tableauCombattants[statMagie[rechercheIndMagieInf(statMagie, magieDef, tableauCombattants)]]->magieRestante > magieDef) && (statPhys[0] != 0)))
                // si il n'y a pas d'indice de physique plus petit que celui du defenseur
                {
                    // printf("debut if phys max\n");
                    indchoisi = statPhys[0];
                }
                else if (tableauCombattants[statMagie[rechercheIndMagieInf(statMagie, magieDef, tableauCombattants)]]->magieRestante != 0)
                {
                    // printf("debut if magie petit\n");
                    indchoisi = statMagie[rechercheIndMagieInf(statMagie, magieDef, tableauCombattants)];
                }
                else // si le plus haute stat magie attaquant completement killable est nulle
                {
                    // printf("debut if magie max\n");
                    indchoisi = statPhys[0];
                }
                // printf("indchoisi0:%d\n", indchoisi);
            }
            else
            {
                // int iMagieChoisie = rechercheIndMagieInf(statMagie, magieDef, tableauCombattants); // indice de stat magie du combattant choisi dans statMagie
                // int iPhysChoisie = appartient(statMagie[iMagieChoisie], statPhys);                 // indice de stat phys du combattant choisi dans statPhys
                int iPhysChoisie = rechercheIndPhysInf(statPhys, physDef, tableauCombattants); // indice de stat phys du combattant choisi dans statPhys
                int iMagieChoisie = appartient(statPhys[iPhysChoisie], statMagie);             // indice de stat magie du combattant choisi dans statMagie
                int iPhysCour = iPhysChoisie + 1;                                              // indice de stat phys du combattant courant dans statMagie
                while ((statPhys[iPhysCour] != 1000) && (tableauCombattants[statMagie[iMagieChoisie]]->magieRestante > magieDef))
                {
                    int iMagieCour = appartient(statPhys[iPhysCour], statMagie);
                    // tant que la magie du combattant choisi n'est pas <= a celle du defenseur et qu'on est pas au bout du tableau
                    if ((((iMagieCour > iMagieChoisie) && (tableauCombattants[statMagie[iMagieCour]]->magieRestante < magieDef)) && (tableauCombattants[statMagie[iMagieCour]]->magieRestante > magieDef)) && ((tableauCombattants[statMagie[iMagieChoisie]]->magieRestante > magieDef) && (tableauCombattants[statMagie[iMagieCour]]->magieRestante < magieDef)))
                    // si le magie plus petit suivant a une  meilleur stat de physique realisable ou que le magie choisi n'avait pas de stat realisable
                    {
                        iPhysChoisie++;
                        iMagieChoisie = appartient(statPhys[iPhysChoisie], statMagie);
                    }
                    iPhysCour++;
                    iMagieCour = appartient(statPhys[iPhysCour], statMagie);
                }
                indchoisi = statPhys[iPhysChoisie];
                // while ((iPhysChoisie < iPhysCour) && (statPhys[iPhysChoisie + 1] != 1000))
                // // tant que le phys du combattant choisi est plus petit que celui du plus grand phys realisable (ie plus grand phys plus petit que celui du defenseur)
                // {
                //     if (appartient(statPhys[iMagieChoisie], statMagie) > magieDef)
                // }
            }
        }
        //-----------------Butage de l'insecte en question
        // on a récupéré l'indice du combattants a buté --> il est temps d'agir en consequence
        // printf("debut degat\n");
        // printf("indchoisi:%d\n", indchoisi);
        int magieAttak = tableauCombattants[indchoisi]->magieRestante;
        int physAttak = tableauCombattants[indchoisi]->physiqueRestant;
        // printf("magieAttak:%d\n", magieAttak);
        // printf("physAttak:%d\n", physAttak);
        if (magieAttak > magieDef)
        {
            // printf("debut if1\n");
            tableauCombattants[indchoisi]->magieRestante = magieAttak - magieDef;
            tableauCombattants[NBENNEMIVAGUE]->magieRestante = 0;
        }
        else
        {
            // printf("debut if2\n");
            tableauCombattants[indchoisi]->magieRestante = 0;
            // printf("suppr20\n");
            tableauCombattants[NBENNEMIVAGUE]->magieRestante = magieDef - magieAttak;
            // printf("suppr21\n");
        }
        if (physAttak > physDef)
        {
            // printf("debut if3\n");
            tableauCombattants[indchoisi]->physiqueRestant = physAttak - physDef;
            // printf("physDef: %d physAttak : %d\n", physDef, physAttak);
            // printf("physDef - physAttak: %d\n", physAttak - physDef);
            tableauCombattants[NBENNEMIVAGUE]->physiqueRestant = 0;
        }
        else
        {
            // printf("debut if4\n");
            tableauCombattants[indchoisi]->physiqueRestant = 0;
            // printf("physDef: %d physAttak : %d\n", physDef, physAttak);
            // printf("physDef - physAttak: %d\n", physDef - physAttak);
            tableauCombattants[NBENNEMIVAGUE]->physiqueRestant = physDef - physAttak;
        }
        nbStatMagieNul = rechercheMagieNulle(tableauCombattants);
        nbStatPhysiqueNul = recherchePhysNulle(tableauCombattants);
        //--------Re-init valeur
        for (int i = 0; i < NBENNEMIVAGUE; i++)
        {
            statMagie[i] = 999;
            statPhys[i] = 999;
        }
        tristat(tableauCombattants, statMagie, statPhys);
        magieDef = tableauCombattants[NBENNEMIVAGUE]->magieRestante;
        physDef = tableauCombattants[NBENNEMIVAGUE]->physiqueRestant;
        // printf("Stat ennemi0 avec degat: %d %d \n", tableauCombattants[0]->physiqueRestant, tableauCombattants[0]->magieRestante);
        // printf("Stat ennemi1 avec degat: %d %d \n", tableauCombattants[1]->physiqueRestant, tableauCombattants[1]->magieRestante);
        // printf("Stat ennemi2 avec degat: %d %d \n", tableauCombattants[2]->physiqueRestant, tableauCombattants[2]->magieRestante);
        // printf("Valeur de magie %d %d %d\n", statMagie[0], statMagie[1], statMagie[2]);
        // printf("Valeur de physique %d %d %d\n", statPhys[0], statPhys[1], statPhys[2]);
        // printf("nbStatMagieNul:%d\n", nbStatMagieNul);
        // printf("nbStatPhysiqueNul:%d\n", nbStatPhysiqueNul);
        // printf("magieDefFinBoucle: %d\n", magieDef);
        // printf("physDefFinBoucle: %d\n", physDef);
    }
    supprValNull(listeIndice, tableauCombattants);
}

void creerAttaquantSansSprite(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], int indiceEmplacement)
{

    combattant_t *emplacementestAttaquant = malloc(sizeof(combattant_t));

    emplacementestAttaquant->magieRestante = 0;
    emplacementestAttaquant->physiqueRestant = 0;

    tableauCombattants[indiceEmplacement] = emplacementestAttaquant;
}

// int main()
// {
//     int tableau[NBENNEMIVAGUE] = {4, 5, 2};

//     combattant_t *tableauCombattants[NBRMAXCOMBATTANTS];
//     creerAttaquant(tableauCombattants, indiceMantiswalk, 0);
//     creerAttaquant(tableauCombattants, indiceFlyWalk, 1);
//     creerAttaquant(tableauCombattants, indiceBugfirewalk, 2);
//     creerAttaquant(tableauCombattants, indiceBugfirewalk, 3);
//     tableauCombattants[0]->physiqueRestant = 5;
//     tableauCombattants[0]->magieRestante = 0;
//     tableauCombattants[1]->physiqueRestant = 2;
//     tableauCombattants[1]->magieRestante = 2;
//     tableauCombattants[2]->physiqueRestant = 3;
//     tableauCombattants[2]->magieRestante = 4;
//     // tableauCombattants[2]->physiqueRestant = 2;
//     // tableauCombattants[2]->magieRestante = 2;
//     tableauCombattants[3]->physiqueRestant = 3;
//     tableauCombattants[3]->magieRestante = 3;
//     int magieDef = tableauCombattants[NBENNEMIVAGUE]->magieRestante;
//     int physDef = tableauCombattants[NBENNEMIVAGUE]->physiqueRestant;
//     int statMagie[NBRMAXCOMBATTANTS];
//     int statPhys[NBRMAXCOMBATTANTS];
//     for (int i = 0; i < NBENNEMIVAGUE; i++)
//     {
//         statMagie[i] = 999;
//         statPhys[i] = 999;
//     }
//     statMagie[NBENNEMIVAGUE] = 1000; // marque la fin du tableau
//     statPhys[NBENNEMIVAGUE] = 1000;  // marque la fin du tableau
//     // printf("Stat mantis : %d %d \n", tableauCombattants[0]->physiqueRestant, tableauCombattants[0]->magieRestante);
//     // printf("Stat Bugfire : %d %d \n", tableauCombattants[1]->physiqueRestant, tableauCombattants[1]->magieRestante);
//     // printf("Stat Fly : %d %d \n", tableauCombattants[2]->physiqueRestant, tableauCombattants[2]->magieRestante);
//     // tristat(tableauCombattants, statMagie, statPhys);
//     // printf("Valeur de magie %d %d %d\n", statMagie[0], statMagie[1], statMagie[2]);
//     // printf("Valeur de physique %d %d %d\n", statPhys[0], statPhys[1], statPhys[2]);
//     printf("physDef: %d\n", physDef);
//     printf("magieDef: %d\n", magieDef);
//     // int indiceM = rechercheIndMagieInf(statMagie, magieDef, tableauCombattants);
//     // printf("indiceM:%d\n", indiceM);
//     degatInflige(tableauCombattants);
//     // printf("Stat mantis avec degat: %d %d \n", tableauCombattants[0]->physiqueRestant, tableauCombattants[0]->magieRestante);
//     //printf("Stat Bugfire avec degat: %d %d \n", tableauCombattants[1]->physiqueRestant, tableauCombattants[1]->magieRestante);
//     // printf("Stat Fly avec degat: %d %d \n", tableauCombattants[2]->physiqueRestant, tableauCombattants[2]->magieRestante);
//     magieDef = tableauCombattants[NBENNEMIVAGUE]->magieRestante;
//     physDef = tableauCombattants[NBENNEMIVAGUE]->physiqueRestant;
//     printf("physDef avec degat: %d\n", physDef);
//     printf("magieDef avec degat: %d\n", magieDef);
//     return 0;
// }