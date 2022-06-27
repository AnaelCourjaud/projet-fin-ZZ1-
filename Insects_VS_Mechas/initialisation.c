#include "initialisation.h"

void init(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture[nbrTextures], TTF_Font *tabPolices[nbrPolices])
{

    ///////////// Chargement des polices et des textures et stockage des pointeurs dans les tableaux

    char nomFichiers[nbrTextures][tailleMaxFichiers] = {"./Sprites/batiment1.png", "./Sprites/batiment2.png", "./Sprites/batiment2coupe.png", "./Sprites/fond.png", "./Sprites/fondaccueil.png", "./Sprites/lore1.png", "./Sprites/lore2.png", "./Sprites/lore3.png", "./Sprites/bugfirewalk.png", "./Sprites/bugfireattaque.png", "./Sprites/bugfiremort.png", "./Sprites/flyvollant.png", "./Sprites/flyattaque.png", "./Sprites/flymort.png", "./Sprites/mantiswalk.png", "./Sprites/mantismort.png", "./Sprites/robot.png", "./Sprites/robotattaque.png", "./Sprites/robotmort.png", "./Sprites/robotmetal.png", "./Sprites/robotmetalattaquedeb.png", "./Sprites/robotmetalattaque.png", "./Sprites/robotmetalmort.png", "./Sprites/robotpetit.png", "./Sprites/robotpetitattaque.png", "./Sprites/robotpetitmort.png",};

    // 0 : premier batiment | 1 et 2 : deuxieme batiment avec en 2 celui coupé | 3 : fond du jeu animé | 4 : fond d'accueil | 5 à 7 : fond du Lore |||

    char nomPolices[nbrPolices][tailleMaxFichiers] = {"./fonts/font.ttf", "./fonts/font2.ttf"};
    int taillePolices[nbrPolices] = {100, 50};

    /////////////// récupération des textures et stockage dans tableau texture et test de réussite de chargement
    for (int i = 0; i < nbrTextures; i++)
    {
        texture[i] = IMG_LoadTexture(renderer, nomFichiers[i]);
        if (texture[i] == NULL)
            end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }
    //////////////////////////

    /////////////// récupération des textures et stockage dans tableau texture et test de réussite de chargement
    for (int i = 0; i < nbrPolices; i++)
    {
        tabPolices[i] = TTF_OpenFont(nomPolices[i], taillePolices[i]);
        if (tabPolices[i] == NULL)
            end_sdl(0, "Echec du chargement de la police", window, renderer);
    }
    //////////////////////////
}

void end_sdl(char ok,            // fin anormale : ok = 0 ; normale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
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