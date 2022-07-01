#include "gestionObjets.h"

void creationVague(spriteBase_t *spritesDeBase[NBRTEXTURES], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], spriteCourant_t *listeCourant[tailleMaxSpritesCourants], int modeAffichage) // il faut bien que listeCombattants soit vide à l'execution de cette fonction
{
    float xSpone = 1.0;

    for (int j = 0; j < NBENNEMIVAGUE; j++)
    {
        int r = rand() % NBRTYPEINSECTES;
        if (r == BUGFIRE)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, BUGFIRE, WALK, j, xSpone, 0.7, modeAffichage);
        }
        else if (r == FLY)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, FLY, WALK, j, xSpone, 0.62, modeAffichage);
        }
        else if (r == MANTIS)
        {
            creerAttaquant(spritesDeBase, listeCourant, tableauCombattants, MANTIS, WALK, j, xSpone, 0.75, modeAffichage);
        }
        else
        {
            printf("erreur de création de vagues\n");
        }
        xSpone += 0.1;
    }
}

void creerAttaquant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t typeCombattant, etatCombattant_t etatArrivee, int indiceEmplacement, float proportionPosX, float proportionPosY, int modeAffichage)
{

    // printf("début créer estAttaquant\n");

    int indiceEmplacementDansListeCourants;
    int indicePNG = retourIndicePNG(typeCombattant, etatArrivee);

    if (modeAffichage == 1)
    {
        indiceEmplacementDansListeCourants = creerSpriteCourant(spritesDeBase, listeCourants, indicePNG, proportionPosX, proportionPosY);
    }

    combattant_t *emplacementestAttaquant = malloc(sizeof(combattant_t));

    emplacementestAttaquant->typeCombattant = typeCombattant;
    emplacementestAttaquant->etatCombattant = etatArrivee;

    if (indicePNG == indiceBugfirewalk)
    {
        // emplacementestAttaquant->typeCombattant = BUGFIRE;
        emplacementestAttaquant->physiqueRestant = 3;
        emplacementestAttaquant->magieRestante = 4;
        emplacementestAttaquant->speedX = 0.99;
        emplacementestAttaquant->speedY = 1.0;
    }
    else if (indicePNG == indiceFlyWalk)
    {
        // emplacementestAttaquant->typeCombattant = FLY;
        emplacementestAttaquant->physiqueRestant = 2;
        emplacementestAttaquant->magieRestante = 2;
        emplacementestAttaquant->speedX = 0.99;
        emplacementestAttaquant->speedY = 1.0;
    }
    else if (indicePNG == indiceMantiswalk)
    {
        // emplacementestAttaquant->typeCombattant = MANTIS;
        emplacementestAttaquant->physiqueRestant = 5;
        emplacementestAttaquant->magieRestante = 0;
        emplacementestAttaquant->speedX = 0.99;
        emplacementestAttaquant->speedY = 1.0;
    }
    else if (indicePNG == indiceRobotGrosWalk)
    {
        // emplacementestAttaquant->typeCombattant = ROBOTGROS;
        emplacementestAttaquant->physiqueRestant = 5;
        emplacementestAttaquant->magieRestante = 0;
        emplacementestAttaquant->speedX = 1.015;
        emplacementestAttaquant->speedY = 1.0;
    }
    else if (indicePNG == indiceRobotmetalWalk)
    {
        // emplacementestAttaquant->typeCombattant = ROBOTMETAL;
        emplacementestAttaquant->physiqueRestant = 0;
        emplacementestAttaquant->magieRestante = 5;
        emplacementestAttaquant->speedX = 1.015;
        emplacementestAttaquant->speedY = 1.0;
    }
    else if (indicePNG == indiceRobotpetitwalk)
    {
        // emplacementestAttaquant->typeCombattant = ROBOTPETIT;
        emplacementestAttaquant->physiqueRestant = 3;
        emplacementestAttaquant->magieRestante = 3;
        emplacementestAttaquant->speedX = 1.015;
        emplacementestAttaquant->speedY = 1.0;
    }
    // else
    // {
    //     printf("Erreur dans la création de l'estAttaquant\n");
    // }
    if (modeAffichage == 1)
    {
        emplacementestAttaquant->spriteCourant = listeCourants[indiceEmplacementDansListeCourants];
    }

    tableauCombattants[indiceEmplacement] = emplacementestAttaquant;
}

int creerSpriteCourant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], indicesPNGs indicePNG, float proportionPosX, float proportionPosY)
{

    int emplacementLibreDansListeCourants = 0;
    while (listeCourants[emplacementLibreDansListeCourants] != NULL)
    {
        emplacementLibreDansListeCourants++;

        if (emplacementLibreDansListeCourants >= tailleMaxSpritesCourants)
        {
            printf("Erreur : plus d'emplacement libre dans listeCourants\n");
        }
    }

    spriteCourant_t *maillonSpriteCourant = malloc(sizeof(spriteCourant_t));

    maillonSpriteCourant->spriteDeBase = spritesDeBase[indicePNG];

    maillonSpriteCourant->xProportionPosFenetre = proportionPosX;
    maillonSpriteCourant->yProportionPosFenetre = proportionPosY;

    maillonSpriteCourant->animationTerminee = 0;
    maillonSpriteCourant->numImageEnCours = 0;
    maillonSpriteCourant->retardateurRalenti = maillonSpriteCourant->spriteDeBase->ralenti;

    listeCourants[emplacementLibreDansListeCourants] = maillonSpriteCourant;

    return emplacementLibreDansListeCourants;
}

void cleanListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]) // à utiliser avant de changer radicalement d'affichage (genre en passant de ACCUEIL à JEU par exemple)
{
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        if (listeCourants[i] != NULL)
        {
            free(listeCourants[i]);
            listeCourants[i] = NULL;
        }
    }
}

void cleanCombattantsDeListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]) // à utiliser avant de lancer une nouvelle vague d'estAttaquants
{
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        if (listeCourants[i] != NULL)
        {
            if (listeCourants[i]->spriteDeBase->indicePNG >= indiceBugfirewalk)
            {
                free(listeCourants[i]);
                listeCourants[i] = NULL;
            }
        }
    }
}

void cleanListeCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS]) //
{
    for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
    {
        if (tableauCombattants[i] != NULL)
        {
            free(tableauCombattants[i]);
            tableauCombattants[i] = NULL;
        }
    }
}

int switchEtatCombattants(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants, etatCombattant_t etatArrivee, int modeAffichage)
{
    int nombreDeMorts = 0;
    for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
    {
        int goChanger = 0;
        if (tableauCombattants[i] != NULL)
        {
            if (tableauCombattants[i]->typeCombattant >= familleCombattants && tableauCombattants[i]->typeCombattant <= familleCombattants + 2)
            {
                if (etatArrivee == MORT)
                {
                    if (familleCombattants == BUGFIRE)
                    {
                        if (tableauCombattants[i]->magieRestante <= 0 && tableauCombattants[i]->physiqueRestant <= 0)
                        {
                            goChanger = 1;
                            nombreDeMorts++;
                        }
                    }
                    else
                    {
                        goChanger = 1;
                    }
                }
                else
                {
                    goChanger = 1;
                }
            }
        }
        if (goChanger == 1)
        {
            // tableauCombattants[i]->etatCombattant = etatArrivee;
            float proportionPosX = tableauCombattants[i]->spriteCourant->xProportionPosFenetre;
            float proportionPosY = tableauCombattants[i]->spriteCourant->yProportionPosFenetre;

            typeCombattant_t typeCombattant = tableauCombattants[i]->typeCombattant;
            // etatCombattant_t etatCombattant = tableauCombattants[i]->etatCombattant;
            float speedX = tableauCombattants[i]->speedX;
            float speedY = tableauCombattants[i]->speedY;
            int physiqueRestant = tableauCombattants[i]->physiqueRestant;
            int magieRestante = tableauCombattants[i]->magieRestante;
            // int indiceCreationDeSpriteCourant;
            // indiceCreationDeSpriteCourant = creerSpriteCourant(spritesDeBase, listeCourants, retourIndicePNG(familleCombattants, etatArrivee));
            for (int j = 0; j < tailleMaxSpritesCourants; j++)
            {
                if (listeCourants[j] == tableauCombattants[i]->spriteCourant)
                {
                    free(tableauCombattants[i]->spriteCourant);
                    tableauCombattants[i]->spriteCourant = NULL;
                    listeCourants[j] = NULL;
                    // printf("sprite de combattant supprimé switch etat\n");
                }
            }
            free(tableauCombattants[i]);
            tableauCombattants[i] = NULL;

            creerAttaquant(spritesDeBase, listeCourants, tableauCombattants, typeCombattant, etatArrivee, i, proportionPosX, proportionPosY, modeAffichage);
            tableauCombattants[i]->speedX = speedX;
            tableauCombattants[i]->speedY = speedY;
            tableauCombattants[i]->physiqueRestant = physiqueRestant;
            tableauCombattants[i]->magieRestante = magieRestante;
            // tableauCombattants[i]->spriteCourant = listeCourants[creerSpriteCourant(spritesDeBase, listeCourants, retourIndicePNG(tableauCombattants[i]->typeCombattant, etatArrivee), proportionPosX, proportionPosY)];
            // printf(" idice PNG : %d\n", retourIndicePNG(tableauCombattants[i]->typeCombattant, etatArrivee));
        }
    }
    return nombreDeMorts;
}

int retourIndicePNG(typeCombattant_t typeCombattants, etatCombattant_t etatArrivee)
{

    int bonIndicePNG;
    bonIndicePNG = 3 * typeCombattants + etatArrivee + indiceBugfirewalk;

    return bonIndicePNG;
}

int faireAvancerCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants)
{
    int avanceeFinie = 0;
    int nbrCombattantsArrives = 0;

    for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
    {
        if (tableauCombattants[i] != NULL)
        {
            if (tableauCombattants[i]->typeCombattant >= familleCombattants && tableauCombattants[i]->typeCombattant <= familleCombattants + 2)
            {

                //////////////////////:dégeulasse
                if (tableauCombattants[i]->typeCombattant == BUGFIRE)
                {
                    if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre <= 0.3) // dégueulasse, c'est pas du tout paramètrable mdr
                    {
                        nbrCombattantsArrives++;
                    }
                    else
                    {
                        tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
                        tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;
                    }
                }
                else if (tableauCombattants[i]->typeCombattant == MANTIS)
                {
                    if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre <= 0.55) // dégueulasse, c'est pas du tout paramètrable mdr
                    {
                        nbrCombattantsArrives++;
                    }
                    else
                    {
                        tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
                        tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;
                    }
                }
                else if (tableauCombattants[i]->typeCombattant == FLY)
                {
                    if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre <= 0.55) // dégueulasse, c'est pas du tout paramètrable mdr
                    {
                        nbrCombattantsArrives++;
                    }
                    else
                    {
                        tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
                        tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;
                    }
                }
                else if (tableauCombattants[i]->typeCombattant == ROBOTGROS)
                {
                    if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre >= 0.5) // dégueulasse, c'est pas du tout paramètrable mdr
                    {
                        nbrCombattantsArrives++;
                    }
                    else
                    {
                        tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
                        tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;
                    }
                }
                else if (tableauCombattants[i]->typeCombattant == ROBOTMETAL)
                {
                    if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre >= 0.50) // dégueulasse, c'est pas du tout paramètrable mdr
                    {
                        nbrCombattantsArrives++;
                    }
                    else
                    {
                        tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
                        tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;
                    }
                }
                else if (tableauCombattants[i]->typeCombattant == ROBOTPETIT)
                {
                    if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre >= 0.50) // dégueulasse, c'est pas du tout paramètrable mdr
                    {
                        nbrCombattantsArrives++;
                    }
                    else
                    {
                        tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
                        tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;
                    }
                }
                ////////////////////////
            }
        }
    }

    if (familleCombattants == BUGFIRE)
    {
        if (nbrCombattantsArrives == NBENNEMIVAGUE)
        {
            avanceeFinie = 1;
        }
    }
    else
    {
        if (nbrCombattantsArrives == 1)
        {
            avanceeFinie = 1;
        }
    }

    return avanceeFinie;
}
