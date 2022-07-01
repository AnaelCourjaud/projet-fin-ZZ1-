#include "initialisation.h"

void init(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *tabPolices[nbrPolices], spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *listeCombattants[NBRMAXCOMBATTANTS])
{

    ///////////// Chargement des polices et des textures et stockage des pointeurs dans les tableaux

    char nomFichiers[NBRTEXTURES][tailleMaxFichiers] = {"./Sprites/passerelleanimee.png", "./Sprites/batiment2.png", "./Sprites/batiment2coupe.png", "./Sprites/fond.png", "./Sprites/fondaccueil.png", "./Sprites/lore1.png", "./Sprites/lore2.png", "./Sprites/lore3.png", "./Sprites/bugfirewalk.png", "./Sprites/bugfireattaque.png", "./Sprites/bugfiremort.png", "./Sprites/flyvolant.png", "./Sprites/flyattaquedeb.png", "./Sprites/flymort.png", "./Sprites/mantiswalk.png", "./Sprites/mantiswalk.png", "./Sprites/mantismort.png", "./Sprites/robot.png", "./Sprites/robotattaque.png", "./Sprites/robotmort.png", "./Sprites/robotmetal.png", "./Sprites/robotmetalattaquedeb.png", "./Sprites/robotmetalmort.png", "./Sprites/robotpetitwalk.png", "./Sprites/robotpetitattaque.png", "./Sprites/robotpetitmort.png"};

    // 0 : premier batiment | 1 et 2 : deuxieme batiment avec en 2 celui coupé | 3 : fond du jeu animé | 4 : fond d'accueil | 5 à 7 : fond du Lore |||

    char nomPolices[nbrPolices][tailleMaxFichiers] = {"./fonts/font.ttf", "./fonts/font2.ttf"};
    int taillePolices[nbrPolices] = {100, 50};

    // *******************************Initialisation de la liste de sprites de base**********************
    // **************************************************************************************************

    for (int i = 0; i < NBRTEXTURES; i++)
    {
        spritesDeBase[i] = malloc(sizeof(spriteBase_t));
        spritesDeBase[i]->textureSprite = IMG_LoadTexture(renderer, nomFichiers[i]);
        if (spritesDeBase[i]->textureSprite == NULL)
            end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, spritesDeBase, listeCourants);

        spritesDeBase[i]->indicePNG = i;
        // spritesDeBase[i]->animation = 1;
        spritesDeBase[i]->nbrImagesHorizontales = 7;
        spritesDeBase[i]->nbrImagesVerticales = 4;
        spritesDeBase[i]->ralenti = 1;
        spritesDeBase[i]->animationInfinie = 1;

        if (i == indiceBatiment2coupe)
        {
            spritesDeBase[i]->prioriteAffichage = TOUTDEVANT;
            // spritesDeBase[i]->animation = 0;
            spritesDeBase[i]->nbrImagesHorizontales = 1;
            spritesDeBase[i]->nbrImagesVerticales = 1;
            spritesDeBase[i]->wCoefReductionDestination = 0.35;
            spritesDeBase[i]->hCoefReductionDestination = 0.60;
        }
        else if (i == indiceFond)
        {
            spritesDeBase[i]->prioriteAffichage = TOUTDERRIERE;
            spritesDeBase[i]->nbrImagesHorizontales = 7;
            spritesDeBase[i]->nbrImagesVerticales = 4;
            spritesDeBase[i]->wCoefReductionDestination = 1.0;
            spritesDeBase[i]->hCoefReductionDestination = 1.0;
        }
        else if (i == indicePasserelleAnimee)
        {
            spritesDeBase[i]->prioriteAffichage = DERRIERE;
            // spritesDeBase[i]->animation = 0;
            spritesDeBase[i]->nbrImagesHorizontales = 4;
            spritesDeBase[i]->nbrImagesVerticales = 2;
            spritesDeBase[i]->wCoefReductionDestination = 1.0;
            spritesDeBase[i]->hCoefReductionDestination = 1.0;
            spritesDeBase[i]->ralenti = 4;
        }
        else if (i == indiceBatiment2)
        {
            spritesDeBase[i]->prioriteAffichage = MILIEU;
            // spritesDeBase[i]->animation = 0;
            spritesDeBase[i]->nbrImagesHorizontales = 1;
            spritesDeBase[i]->nbrImagesVerticales = 1;
            spritesDeBase[i]->wCoefReductionDestination = 0.35;
            spritesDeBase[i]->hCoefReductionDestination = 0.60;
        }
        else if (i >= indiceBugfirewalk)
        {
            spritesDeBase[i]->wCoefReductionDestination = 0.10;
            spritesDeBase[i]->hCoefReductionDestination = 0.20;

            if (i == indiceBugfirewalk)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.40;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 3;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
            }
            else if (i == indiceBugfireattaque)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.40;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 10;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
            }
            else if (i == indiceBugfiremort)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.40;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 3;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 5;
                spritesDeBase[i]->animationInfinie = 0;
            }
            else if (i == indiceFlyWalk)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.10;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 4;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
            }
            else if (i == indiceFlyattaque)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.075;
                spritesDeBase[i]->hCoefReductionDestination = 0.15;
                spritesDeBase[i]->nbrImagesHorizontales = 1;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 1;
            }
            else if (i == indiceFlymort)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.10;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 7;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 0;
                spritesDeBase[i]->animationInfinie = 0;
            }
            else if (i == indiceMantiswalk)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.05;
                spritesDeBase[i]->hCoefReductionDestination = 0.10;
                spritesDeBase[i]->nbrImagesHorizontales = 3;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 4;
            }

            else if (i == indiceMantisAttaque)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.05;
                spritesDeBase[i]->hCoefReductionDestination = 0.10;
                spritesDeBase[i]->nbrImagesHorizontales = 3;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 4;
            }
            else if (i == indiceMantismort)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.05;
                spritesDeBase[i]->hCoefReductionDestination = 0.10;
                spritesDeBase[i]->nbrImagesHorizontales = 3;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 1;
                spritesDeBase[i]->animationInfinie = 0;
            }
            else if (i == indiceRobotGrosWalk)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.025;
                spritesDeBase[i]->hCoefReductionDestination = 0.075;
                spritesDeBase[i]->nbrImagesHorizontales = 5;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 4;
            }
            else if (i == indiceRobotGrosattaque)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.0575;
                spritesDeBase[i]->hCoefReductionDestination = 0.115;
                spritesDeBase[i]->nbrImagesHorizontales = 7;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
            }
            else if (i == indiceRobotGrosMort)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.0575;
                spritesDeBase[i]->hCoefReductionDestination = 0.115;
                spritesDeBase[i]->nbrImagesHorizontales = 12;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 0;
                spritesDeBase[i]->animationInfinie = 0;
            }
            else if (i == indiceRobotpetitwalk)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.035;
                spritesDeBase[i]->hCoefReductionDestination = 0.07;
                spritesDeBase[i]->nbrImagesHorizontales = 6;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 4;
            }
            else if (i == indiceRobotpetitattaque)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.035;
                spritesDeBase[i]->hCoefReductionDestination = 0.07;
                spritesDeBase[i]->nbrImagesHorizontales = 6;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
            }
            else if (i == indiceRobotpetitmort)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.035;
                spritesDeBase[i]->hCoefReductionDestination = 0.07;
                spritesDeBase[i]->nbrImagesHorizontales = 3;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
                spritesDeBase[i]->animationInfinie = 0;
            }
            else if (i == indiceRobotmetalWalk)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.10;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 2;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 4;
            }
            else if (i == indiceRobotmetalattaque)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.10;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 2;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 2;
            }
            else if (i == indiceRobotmetalmort)
            {
                spritesDeBase[i]->wCoefReductionDestination = 0.10;
                spritesDeBase[i]->hCoefReductionDestination = 0.20;
                spritesDeBase[i]->nbrImagesHorizontales = 7;
                spritesDeBase[i]->nbrImagesVerticales = 1;
                spritesDeBase[i]->ralenti = 1;
                spritesDeBase[i]->animationInfinie = 0;
            }

            spritesDeBase[i]->prioriteAffichage = DEVANT;
        }
        else
        {
            spritesDeBase[i]->wCoefReductionDestination = 1.0;
            spritesDeBase[i]->hCoefReductionDestination = 1.0;
            spritesDeBase[i]->prioriteAffichage = TOUTDEVANT;
            spritesDeBase[i]->nbrImagesHorizontales = 1;
            spritesDeBase[i]->nbrImagesVerticales = 1;
            // spritesDeBase[i]->animation = 0;
        }

        SDL_Rect source = {0};

        SDL_QueryTexture(spritesDeBase[i]->textureSprite, NULL, NULL, &source.w, &source.h);

        spritesDeBase[i]->wImageSprite = source.w / spritesDeBase[i]->nbrImagesHorizontales;
        spritesDeBase[i]->hImageSprite = source.h / spritesDeBase[i]->nbrImagesVerticales;
    }
    // *******************************Initialisation de la liste de sprites courants ********************
    // **************************************************************************************************

    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        listeCourants[i] = NULL; // malloc(sizeof(spriteCourant_t));
    }

    // *******************************Initialisation de la liste des combattants ************************
    // **************************************************************************************************

    for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
    {
        listeCombattants[i] = NULL; // malloc(sizeof(combattant_t));
    }

    // ******************************* récupération des polices + stockage + test  *********************
    // **************************************************************************************************

    for (int i = 0; i < nbrPolices; i++)
    {
        tabPolices[i] = TTF_OpenFont(nomPolices[i], taillePolices[i]);
        if (tabPolices[i] == NULL)
            end_sdl(0, "Echec du chargement de la police", window, renderer, spritesDeBase, listeCourants);
    }
}

void end_sdl(char ok,            // fin anormale : ok = 0 ; normale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer, spriteBase_t *spritesDebase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants])
{ // renderer à fermer
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    // ******************************* free du tableau sprites courants *********************************
    // **************************************************************************************************

    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        free(listeCourants[i]);
    }

    // ******************************* free du tableau sprites de base  *********************************
    // **************************************************************************************************

    for (int i = 0; i < NBRTEXTURES; i++)
    {
        free(spritesDebase[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}