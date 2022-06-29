#include "affichage.h"

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

// void creationFond(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int x, int y)
// {

//     SDL_Rect
//         source = {0},            // Rectangle définissant la zone de la texture à récupérer
//         window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
//         destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

//     SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); // Récupération des dimensions de la fenêtre
//     SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

//     destination.x = x;
//     destination.y = y;
//     destination.w = window_dimensions.w;
//     destination.h = window_dimensions.h;

//     SDL_RenderCopy(renderer, my_texture, &source, &destination);
// }

void animation(SDL_Window *window, SDL_Renderer *renderer, spriteCourant_t *listeCourants[tailleMaxSpritesCourants])
{
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); // Récupération des dimensions de la fenêtre

    // printf("debut animation\n");
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        // printf("%d\n", i);
        if (listeCourants[i] != NULL)
        {
            // printf("pas nul\n");
            // printf(" indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", listeCourants[i]->spriteDeBase->indicePNG, listeCourants[i]->spriteDeBase->animation, listeCourants[i]->spriteDeBase->nbrImagesHorizontales, listeCourants[i]->spriteDeBase->nbrImagesVerticales, listeCourants[i]->spriteDeBase->prioriteAffichage);
            if (listeCourants[i]->spriteDeBase->animation == 1)
            {
                // printf("animation\n");
                if (listeCourants[i]->retardateurRalenti <= 0)
                {
                    listeCourants[i]->source.x = (listeCourants[i]->numImageEnCours % listeCourants[i]->spriteDeBase->nbrImagesHorizontales) * listeCourants[i]->source.w;
                    listeCourants[i]->source.y = (listeCourants[i]->numImageEnCours / listeCourants[i]->spriteDeBase->nbrImagesHorizontales) * listeCourants[i]->source.h;

                    listeCourants[i]->numImageEnCours++;
                    if (listeCourants[i]->numImageEnCours >= listeCourants[i]->spriteDeBase->nbrImagesHorizontales * listeCourants[i]->spriteDeBase->nbrImagesVerticales)
                    {
                        listeCourants[i]->numImageEnCours = 0;
                    }
                    listeCourants[i]->retardateurRalenti = listeCourants[i]->spriteDeBase->ralenti;
                }
                else
                {
                    listeCourants[i]->retardateurRalenti--;
                }
            }

            listeCourants[i]->destination.w = window_dimensions.w * listeCourants[i]->spriteDeBase->wCoefReductionDestination;
            listeCourants[i]->destination.h = window_dimensions.h * listeCourants[i]->spriteDeBase->hCoefReductionDestination;
            // maillonSpriteCourant->destination.w = window_dimensions.w * maillonSpriteCourant->spriteDeBase->wCoefReductionDestination;
            // maillonSpriteCourant->destination.h = window_dimensions.h * maillonSpriteCourant->spriteDeBase->hCoefReductionDestination;
            SDL_RenderCopy(renderer, listeCourants[i]->spriteDeBase->textureSprite, &listeCourants[i]->source, &listeCourants[i]->destination);
            // printf("apres copy\n");
        }
    }
}

void creerAttaquant(SDL_Window *window, spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], indicesPNGs indicePNG, int indiceEmplacement)
{

    // printf("début créer attaquant\n");

    int indiceEmplacementDansListeCourants;
    // while (listeCourants[indiceEmplacementDansListeCourants] != NULL)
    // {
    //     indiceEmplacementDansListeCourants++;
    // }
    // indiceEmplacementDansListeCourants = 0;
    // printf(" indicePNG : %d\n", indicePNG);
    indiceEmplacementDansListeCourants = creerSpriteCourant(window, spritesDeBase, listeCourants, indicePNG);
    // printf(" creerAttaquant : indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", listeCourants[indiceEmplacementDansListeCourants]->spriteDeBase->indicePNG, listeCourants[indiceEmplacementDansListeCourants]->spriteDeBase->animation, listeCourants[indiceEmplacementDansListeCourants]->spriteDeBase->nbrImagesHorizontales, listeCourants[indiceEmplacementDansListeCourants]->spriteDeBase->nbrImagesVerticales, listeCourants[indiceEmplacementDansListeCourants]->spriteDeBase->prioriteAffichage);

    combattant_t *emplacementAttaquant = malloc(sizeof(combattant_t));
    // emplacementAttaquant->spriteCourant = malloc(sizeof(spriteCourant_t));
    // emplacementAttaquant->spriteCourant->spriteDeBase = spritesDeBase[indicePNG];

    // emplacementAttaquant->spriteCourant->source.x = 0;
    // emplacementAttaquant->spriteCourant->source.y = 0;
    // emplacementAttaquant->spriteCourant->source.w = 200;
    // emplacementAttaquant->spriteCourant->source.h = 200;

    // emplacementAttaquant->spriteCourant->destination.x = 0;
    // emplacementAttaquant->spriteCourant->destination.y = 0;
    // emplacementAttaquant->spriteCourant->destination.w = 200;
    // emplacementAttaquant->spriteCourant->destination.h = 200;

    // emplacementAttaquant->spriteCourant->numImageEnCours = 0;
    // emplacementAttaquant->spriteCourant->retardateurRalenti = emplacementAttaquant->spriteCourant->spriteDeBase->ralenti;
    if (indicePNG == indiceBugfirewalk)
    {
        emplacementAttaquant->typeCombattant = BUGFIRE;
        emplacementAttaquant->physiqueRestant = 3;
        emplacementAttaquant->magieRestante = 4;
    }
    else if (indicePNG == indiceFlyvolant)
    {
        emplacementAttaquant->typeCombattant = FLY;
        emplacementAttaquant->physiqueRestant = 2;
        emplacementAttaquant->magieRestante = 2;
    }
    else if (indicePNG == indiceMantiswalk)
    {
        emplacementAttaquant->typeCombattant = MANTIS;
        emplacementAttaquant->physiqueRestant = 5;
        emplacementAttaquant->magieRestante = 0;
    }
    else
    {
        printf("Erreur dans la création de l'attaquant\n");
    }

    emplacementAttaquant->spriteCourant = listeCourants[indiceEmplacementDansListeCourants];

    // listeCourants[i] = emplacementAttaquant->spriteCourant;
    // printf("listeCourants[%d] == NULL : %d\n", i, listeCourants[i] == NULL);

    tableauCombattants[indiceEmplacement] = emplacementAttaquant;
    // printf(" creerAttaquant bis : indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", tableauCombattants[indiceEmplacement]->spriteCourant->spriteDeBase->indicePNG, tableauCombattants[indiceEmplacement]->spriteCourant->spriteDeBase->animation, tableauCombattants[indiceEmplacement]->spriteCourant->spriteDeBase->nbrImagesHorizontales, tableauCombattants[indiceEmplacement]->spriteCourant->spriteDeBase->nbrImagesVerticales, tableauCombattants[indiceEmplacement]->spriteCourant->spriteDeBase->prioriteAffichage);

    // printf("attaquant créé ! indiceEmplacement = %d et indicePNG = %d et emplacement dans listeCourants : %d\n", indiceEmplacement, indicePNG, indiceEmplacementDansListeCourants);
    /*
        int j=0;
        while(listeCourants[j] != NULL){
            j++
        }
        listeCourants[i] = emplacementAttaquant->spriteCourant;
    */
}

int creerSpriteCourant(SDL_Window *window, spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], indicesPNGs indicePNG)
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
    // spriteBase_t *maillonCopieBase = malloc(sizeof(spriteBase_t));
    // // maillonSpriteCourant->spriteDeBase
    // maillonCopieBase->textureSprite = spritesDeBase[indicePNG]->textureSprite;
    // maillonCopieBase->indicePNG = spritesDeBase[indicePNG]->indicePNG;
    // maillonCopieBase->prioriteAffichage = spritesDeBase[indicePNG]->prioriteAffichage;
    // maillonCopieBase->animation = spritesDeBase[indicePNG]->animation;
    // maillonCopieBase->nbrImagesHorizontales = spritesDeBase[indicePNG]->nbrImagesHorizontales;
    // maillonCopieBase->nbrImagesVerticales = spritesDeBase[indicePNG]->nbrImagesVerticales;
    // maillonCopieBase->ralenti = spritesDeBase[indicePNG]->ralenti;

    maillonSpriteCourant->spriteDeBase = spritesDeBase[indicePNG];

    // printf(" creerSpriteCourant : indicePNG : %d, animation = %d, nbr imageshorizon : %d, nbr images vertic : %d, priorite affichage : %d\n", maillonSpriteCourant->spriteDeBase->indicePNG, maillonSpriteCourant->spriteDeBase->animation, maillonSpriteCourant->spriteDeBase->nbrImagesHorizontales, maillonSpriteCourant->spriteDeBase->nbrImagesVerticales, maillonSpriteCourant->spriteDeBase->prioriteAffichage);
    // SDL_Rect window_dimensions = {0};
    // SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); // Récupération des dimensions de la fenêtre

    maillonSpriteCourant->source.x = 0;
    maillonSpriteCourant->source.y = 0;
    maillonSpriteCourant->source.w = 0;
    maillonSpriteCourant->source.h = 0;

    SDL_QueryTexture(maillonSpriteCourant->spriteDeBase->textureSprite, NULL, NULL, &maillonSpriteCourant->source.w, &maillonSpriteCourant->source.h);

    if (maillonSpriteCourant->spriteDeBase->animation == 1)
    {
        maillonSpriteCourant->source.w = maillonSpriteCourant->source.w / maillonSpriteCourant->spriteDeBase->nbrImagesHorizontales;
        maillonSpriteCourant->source.h = maillonSpriteCourant->source.h / maillonSpriteCourant->spriteDeBase->nbrImagesVerticales;
    }

    maillonSpriteCourant->destination.x = 0;
    maillonSpriteCourant->destination.y = 0;
    maillonSpriteCourant->destination.w = 0; // window_dimensions.w * maillonSpriteCourant->spriteDeBase->wCoefReductionDestination;
    maillonSpriteCourant->destination.h = 0; // window_dimensions.h * maillonSpriteCourant->spriteDeBase->hCoefReductionDestination;

    maillonSpriteCourant->numImageEnCours = 0;
    maillonSpriteCourant->retardateurRalenti = maillonSpriteCourant->spriteDeBase->ralenti;

    listeCourants[emplacementLibreDansListeCourants] = maillonSpriteCourant;

    return emplacementLibreDansListeCourants;
}

void cleanListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants])
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

void cleanListeCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
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

// void supprCombattant(spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *listeCombattants[NBRMAXCOMBATTANTS], )

/*

void Animation(SDL_Texture * texture1, SDL_Texture *texture2, SDL_Texture *fond, SDL_Renderer *renderer, SDL_Window *window, int longueur, int largeur, int x1,  int x2, int y,int nbimage1,int nbimage2, int nbimageFond, int ite, int iteFond)
{
    SDL_Rect
        source1 = {0},                             // Rectangle définissant la zone de la texture à récupérer
       // window_dimensions1 = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
        destination1 = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

//    SDL_Texture  *texture2;
  //  SDL_Surface *image2 = NULL;

    SDL_Rect
        source2 = {0},                             // Rectangle définissant la zone de la texture à récupérer
       // window_dimensions2 = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
        destination2 = {0};

SDL_Rect
        sourceFond = {0},                             // Rectangle définissant la zone de la texture à récupérer
       // window_dimensions1 = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
        destinationFond = {0};


    SDL_Rect state1[nbimage1];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation
    SDL_Rect state2[nbimage2];
    SDL_Rect stateFond[nbimageFond];

    SDL_QueryTexture(texture1, NULL, NULL, &source1.w, &source1.h);
    int offset_x1 = source1.w / nbimage1,                // La largeur d'une vignette de l'image
        offset_y1 = source1.h;

    // construction des différents rectangles autour de chacune des vignettes de la planche
    int i1 = 0;
    for (int y1 = 0; y1 < source1.h ; y1 += offset_y1) {
    for (int x1 = 0; x1 < source1.w; x1 += offset_x1) {
      state1[i1].x = x1;
      state1[i1].y = y1;
      state1[i1].w = offset_x1;
      state1[i1].h = offset_y1;
      ++i1;
    }
    }

    SDL_QueryTexture(texture2, NULL, NULL, &source2.w, &source2.h);
    int offset_x2 = source2.w / nbimage2,                // La largeur d'une vignette de l'image
        offset_y2 = source2.h;

    // construction des différents rectangles autour de chacune des vignettes de la planche
    int i2 = 0;
    for (int y2 = 0; y2 < source2.h ; y2 += offset_y2) {
    for (int x2 = 0; x2 < source2.w; x2 += offset_x2) {
      state2[i2].x = x2;
      state2[i2].y = y2;
      state2[i2].w = offset_x2;
      state2[i2].h = offset_y2;
      ++i2;
    }
    }

     SDL_QueryTexture(fond, NULL, NULL, &sourceFond.w, &sourceFond.h);
    int offset_xFond = sourceFond.w / nbimageFond,                // La largeur d'une vignette de l'image
        offset_yFond = sourceFond.h;

    // construction des différents rectangles autour de chacune des vignettes de la planche
    int iFond = 0;
    for (int yFond = 0; yFond < sourceFond.h ; yFond += offset_yFond) {
    for (int xFond = 0; xFond < sourceFond.w; xFond += offset_xFond) {
      stateFond[iFond].x = xFond;
      stateFond[iFond].y = yFond;
      stateFond[iFond].w = offset_xFond;
      stateFond[iFond].h = offset_yFond;
      ++iFond;
    }
    }


    destination1.w = largeur;           // Largeur du sprite à l'écran
    destination1.h = longueur;            // Hauteur du sprite à l'écran
    destination1.x = x1; // Position en x pour l'affichage du sprite
    destination1.y = y;  // Position en y pour l'affichage du sprite

    if(offset_x1 >= 150){
        destination1.w = 750;
        destination1.h += 50;
        destination1.x += 50;
        destination1.y -= 50;
    }

    destination2.w = largeur;           // Largeur du sprite à l'écran
    destination2.h = longueur;            // Hauteur du sprite à l'écran
    destination2.x = x2; // Position en x pour l'affichage du sprite
    destination2.y = y;  // Position en y pour l'affichage du sprite

    if(offset_x2 >= 150){
        destination2.w = 750;
        destination2.h += 50;
        destination2.x -= 400;
        destination2.y -= 50;
    }

    destinationFond.w = 1920;           // Largeur du sprite à l'écran
    destinationFond.h = 1080;            // Hauteur du sprite à l'écran
    destinationFond.x = 0; // Position en x pour l'affichage du sprite
    destinationFond.y = 0;  // Position en y pour l'affichage du sprite



    int courant1 = ite % nbimage1;
    int courant2 = ite % nbimage2;
    int courantFond = iteFond % nbimageFond;

    SDL_RenderCopy(renderer, fond, &stateFond[courantFond], &destinationFond);
    SDL_RenderCopy(renderer, texture1, &state1[courant1], &destination1);
    SDL_RenderCopy(renderer, texture2, &state2[courant2], &destination2);

}
*/