#include "affichage.h"

//j'ai une folle envie de tester le commit !!

void creationTexte(char texte[], char style[], char police[], SDL_Renderer *renderer, int taille, int x, int y, int opacite)
{

    TTF_Font *font = NULL;               // la variable 'police de caractère'
    font = TTF_OpenFont(police, taille); // La police à charger, la taille désirée
    if (font == NULL)
        fprintf(stderr, "Can't load font  %s\n", SDL_GetError());

    if (strcmp(style, "normal") == 0)
    { // si on veut le texte en style normal
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    }

    if (strcmp(style, "surligne") == 0)
    { // si on veut le texte surligné
        TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);
    }

    if (strcmp(style, "italique") == 0)
    { // si on veut le texte en italique
        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
    }

    if (strcmp(style, "gras") == 0)
    { // si on veut le texte en gras
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    }

    SDL_Color color = {0, 0, 0, opacite};
    SDL_Surface *text_surface = NULL;                          // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, texte, color); // création du texte dans la surface
    if (text_surface == NULL)
        fprintf(stderr, "Can't create text surface %s\n", SDL_GetError());

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        fprintf(stderr, "Can't create texture from surface %s\n", SDL_GetError());
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {x, y, 1000, 1000};                          // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_DestroyTexture(text_texture);
}

void animation(SDL_Window *window, SDL_Renderer *renderer, spriteCourant_t *listeCourants[tailleMaxSpritesCourants])
{
    SDL_Rect window_dimensions = {0}, source = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); // Récupération des dimensions de la fenêtre

    // printf("debut animation\n");
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        if (listeCourants[i] != NULL)
        {
            source.x = (listeCourants[i]->numImageEnCours % listeCourants[i]->spriteDeBase->nbrImagesHorizontales) * listeCourants[i]->spriteDeBase->wImageSprite;
            source.y = (listeCourants[i]->numImageEnCours / listeCourants[i]->spriteDeBase->nbrImagesHorizontales) * listeCourants[i]->spriteDeBase->hImageSprite;
            source.w = listeCourants[i]->spriteDeBase->wImageSprite;
            source.h = listeCourants[i]->spriteDeBase->hImageSprite;

            destination.x = window_dimensions.w * listeCourants[i]->xProportionPosFenetre;
            destination.y = window_dimensions.h * listeCourants[i]->yProportionPosFenetre;
            destination.w = window_dimensions.w * listeCourants[i]->spriteDeBase->wCoefReductionDestination;
            destination.h = window_dimensions.h * listeCourants[i]->spriteDeBase->hCoefReductionDestination;

            // printf("animation\n");
            if (listeCourants[i]->retardateurRalenti <= 0)
            {
                listeCourants[i]->numImageEnCours++;
                if (listeCourants[i]->numImageEnCours >= listeCourants[i]->spriteDeBase->nbrImagesHorizontales * listeCourants[i]->spriteDeBase->nbrImagesVerticales)
                {   
                    if(listeCourants[i]->spriteDeBase->animationInfinie == 0){
                        listeCourants[i]->animationTerminee = 1;
                    }
                    listeCourants[i]->numImageEnCours = 0;
                }
                listeCourants[i]->retardateurRalenti = listeCourants[i]->spriteDeBase->ralenti;
            }
            else
            {
                listeCourants[i]->retardateurRalenti--;
            }

            SDL_RenderCopy(renderer, listeCourants[i]->spriteDeBase->textureSprite, &source, &destination);
            // printf("apres copy\n");
            
        }
    }
}

// void creerAttaquant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t typeCombattant, etatCombattant_t etatArrivee, int indiceEmplacement, float proportionPosX, float proportionPosY)
// {

//     // printf("début créer estAttaquant\n");

//     int indiceEmplacementDansListeCourants;
//     int indicePNG = retourIndicePNG(typeCombattant, etatArrivee);

//     indiceEmplacementDansListeCourants = creerSpriteCourant(spritesDeBase, listeCourants, indicePNG, proportionPosX, proportionPosY);

//     combattant_t *emplacementestAttaquant = malloc(sizeof(combattant_t));

// emplacementestAttaquant->typeCombattant = typeCombattant;
//     emplacementestAttaquant->etatCombattant = etatArrivee;


//     if (indicePNG == indiceBugfirewalk)
//     {
//         // emplacementestAttaquant->typeCombattant = BUGFIRE;
//         emplacementestAttaquant->physiqueRestant = 3;
//         emplacementestAttaquant->magieRestante = 4;
//         emplacementestAttaquant->speedX = 0.99;
//         emplacementestAttaquant->speedY = 1.0;
//     }
//     else if (indicePNG == indiceFlyWalk)
//     {
//         // emplacementestAttaquant->typeCombattant = FLY;
//         emplacementestAttaquant->physiqueRestant = 2;
//         emplacementestAttaquant->magieRestante = 2;
//         emplacementestAttaquant->speedX = 0.99;
//         emplacementestAttaquant->speedY = 1.0;
//     }
//     else if (indicePNG == indiceMantiswalk)
//     {
//         // emplacementestAttaquant->typeCombattant = MANTIS;
//         emplacementestAttaquant->physiqueRestant = 5;
//         emplacementestAttaquant->magieRestante = 0;
//         emplacementestAttaquant->speedX = 0.99;
//         emplacementestAttaquant->speedY = 1.0;
//     }
//     else if (indicePNG == indiceRobotGrosWalk)
//     {
//         // emplacementestAttaquant->typeCombattant = ROBOTGROS;
//         emplacementestAttaquant->physiqueRestant = 5;
//         emplacementestAttaquant->magieRestante = 0;
//         emplacementestAttaquant->speedX = 1.01;
//         emplacementestAttaquant->speedY = 1.0;
//     }
//     else if (indicePNG == indiceRobotmetalWalk)
//     {
//         // emplacementestAttaquant->typeCombattant = ROBOTMETAL;
//         emplacementestAttaquant->physiqueRestant = 0;
//         emplacementestAttaquant->magieRestante = 5;
//         emplacementestAttaquant->speedX = 1.01;
//         emplacementestAttaquant->speedY = 1.0;
//     }
//     else if (indicePNG == indiceRobotpetitwalk)
//     {
//         // emplacementestAttaquant->typeCombattant = ROBOTPETIT;
//         emplacementestAttaquant->physiqueRestant = 3;
//         emplacementestAttaquant->magieRestante = 3;
//         emplacementestAttaquant->speedX = 1.01;
//         emplacementestAttaquant->speedY = 1.0;
//     }
//     // else
//     // {
//     //     printf("Erreur dans la création de l'estAttaquant\n");
//     // }

//     emplacementestAttaquant->spriteCourant = listeCourants[indiceEmplacementDansListeCourants];

//     tableauCombattants[indiceEmplacement] = emplacementestAttaquant;
// }



// int creerSpriteCourant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], indicesPNGs indicePNG, float proportionPosX, float proportionPosY)
// {

//     int emplacementLibreDansListeCourants = 0;
//     while (listeCourants[emplacementLibreDansListeCourants] != NULL)
//     {
//         emplacementLibreDansListeCourants++;

//         if (emplacementLibreDansListeCourants >= tailleMaxSpritesCourants)
//         {
//             printf("Erreur : plus d'emplacement libre dans listeCourants\n");
//         }
//     }

//     spriteCourant_t *maillonSpriteCourant = malloc(sizeof(spriteCourant_t));

//     maillonSpriteCourant->spriteDeBase = spritesDeBase[indicePNG];

//     maillonSpriteCourant->xProportionPosFenetre = proportionPosX;
//     maillonSpriteCourant->yProportionPosFenetre = proportionPosY;

//     maillonSpriteCourant->animationTerminee = 0;
//     maillonSpriteCourant->numImageEnCours = 0;
//     maillonSpriteCourant->retardateurRalenti = maillonSpriteCourant->spriteDeBase->ralenti;

//     listeCourants[emplacementLibreDansListeCourants] = maillonSpriteCourant;

//     return emplacementLibreDansListeCourants;
// }

// void cleanListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]) // à utiliser avant de changer radicalement d'affichage (genre en passant de ACCUEIL à JEU par exemple)
// {
//     for (int i = 0; i < tailleMaxSpritesCourants; i++)
//     {
//         if (listeCourants[i] != NULL)
//         {
//             free(listeCourants[i]);
//             listeCourants[i] = NULL;
//         }
//     }
// }

// void cleanCombattantsDeListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]) // à utiliser avant de lancer une nouvelle vague d'estAttaquants
// {
//     for (int i = 0; i < tailleMaxSpritesCourants; i++)
//     {
//         if (listeCourants[i] != NULL)
//         {
//             if (listeCourants[i]->spriteDeBase->indicePNG >= indiceBugfirewalk)
//             {
//                 free(listeCourants[i]);
//                 listeCourants[i] = NULL;
//             }
//         }
//     }
// }

// void cleanListeCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS]) //
// {
//     for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
//     {
//         if (tableauCombattants[i] != NULL)
//         {
//             free(tableauCombattants[i]);
//             tableauCombattants[i] = NULL;
//         }
//     }
// }

// int switchEtatCombattants(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants, etatCombattant_t etatArrivee)
// {
//     int nombreDeMorts = 0;
//     for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
//     {
//         int goChanger = 0;
//         if (tableauCombattants[i] != NULL)
//         {
//             if (tableauCombattants[i]->typeCombattant >= familleCombattants && tableauCombattants[i]->typeCombattant <= familleCombattants + 2)
//             {
//                 if (etatArrivee == MORT)
//                 {
//                     if (familleCombattants == BUGFIRE)
//                     {
//                         if(tableauCombattants[i]->magieRestante <= 0 && tableauCombattants[i]->physiqueRestant <= 0){
//                             goChanger = 1;
//                             nombreDeMorts++;
//                         }
//                     }
//                     else
//                     {
//                         goChanger = 1;
//                     }
//                 }
//                 else
//                 {
//                     goChanger = 1;
//                 }
//             }
//         }
//         if (goChanger == 1)
//         {
//             // tableauCombattants[i]->etatCombattant = etatArrivee;
//             float proportionPosX = tableauCombattants[i]->spriteCourant->xProportionPosFenetre;
//             float proportionPosY = tableauCombattants[i]->spriteCourant->yProportionPosFenetre;

//             typeCombattant_t typeCombattant = tableauCombattants[i]->typeCombattant;
//             // etatCombattant_t etatCombattant = tableauCombattants[i]->etatCombattant;
//             float speedX = tableauCombattants[i]->speedX;
//             float speedY = tableauCombattants[i]->speedY;
//             int physiqueRestant = tableauCombattants[i]->physiqueRestant;
//             int magieRestante = tableauCombattants[i]->magieRestante;
//             // int indiceCreationDeSpriteCourant;
//             // indiceCreationDeSpriteCourant = creerSpriteCourant(spritesDeBase, listeCourants, retourIndicePNG(familleCombattants, etatArrivee));
//             for (int j = 0; j < tailleMaxSpritesCourants; j++)
//             {
//                 if (listeCourants[j] == tableauCombattants[i]->spriteCourant)
//                 {
//                     free(tableauCombattants[i]->spriteCourant);
//                     tableauCombattants[i]->spriteCourant = NULL;
//                     listeCourants[j] = NULL;
//                     // printf("sprite de combattant supprimé switch etat\n");
//                 }
//             }
//             free(tableauCombattants[i]);
//             tableauCombattants[i]=NULL;

//             creerAttaquant(spritesDeBase, listeCourants, tableauCombattants, typeCombattant, etatArrivee, i, proportionPosX, proportionPosY);
//             tableauCombattants[i]->speedX =speedX;
//             tableauCombattants[i]->speedY = speedY;
//             tableauCombattants[i]->physiqueRestant = physiqueRestant;
//             tableauCombattants[i]->magieRestante = magieRestante;
//             // tableauCombattants[i]->spriteCourant = listeCourants[creerSpriteCourant(spritesDeBase, listeCourants, retourIndicePNG(tableauCombattants[i]->typeCombattant, etatArrivee), proportionPosX, proportionPosY)];
//             //printf(" idice PNG : %d\n", retourIndicePNG(tableauCombattants[i]->typeCombattant, etatArrivee));
//         }
//     }
//     return nombreDeMorts;
// }



// int retourIndicePNG(typeCombattant_t typeCombattants, etatCombattant_t etatArrivee)
// {

//     int bonIndicePNG;
//     bonIndicePNG = 3 * typeCombattants + etatArrivee + indiceBugfirewalk;

//     return bonIndicePNG;
// }

// int faireAvancerCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants)
// {
//     int avanceeFinie = 0;

//     for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
//     {
//         if (tableauCombattants[i] != NULL)
//         {
//             if (tableauCombattants[i]->typeCombattant >= familleCombattants && tableauCombattants[i]->typeCombattant <= familleCombattants + 2)
//             {
//                 tableauCombattants[i]->spriteCourant->xProportionPosFenetre *= tableauCombattants[i]->speedX;
//                 tableauCombattants[i]->spriteCourant->yProportionPosFenetre *= tableauCombattants[i]->speedY;

//                 //////////////////////:dégeulasse
//                 if (familleCombattants == BUGFIRE)
//                 {
//                     if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre <= 0.5) // dégueulasse, c'est pas du tout paramètrable mdr
//                     {
//                         avanceeFinie = 1;
//                     }
//                 }
//                 if (familleCombattants == ROBOTGROS)
//                 {
//                     if (tableauCombattants[i]->spriteCourant->xProportionPosFenetre >= 0.4) // dégueulasse, c'est pas du tout paramètrable mdr
//                     {
//                         avanceeFinie = 1;
//                     }
//                 }
//                 ////////////////////////
//             }
//         }
//     }

//     return avanceeFinie;
// }

// void supprCombattant(spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *listeCombattants[NBRMAXCOMBATTANTS], )
