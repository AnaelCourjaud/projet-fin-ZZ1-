#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ligneTexture 2
#define colonneTexture 7
#define nombreFichier 14
#define tailleMaxFichiers 50

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

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Point tailleFenetre;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + TTF + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.x = screen.w * 0.66;
    tailleFenetre.y = screen.h * 0.66;
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);
    //printf("Pour fermer : cliquer sur la croix, ou alors 'q' ou alors 'ESCAPE'. Bon trip !\n");

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, tailleFenetre.x,
                              tailleFenetre.y,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /* Création du moyen d'écrire du texte*/
    if (TTF_Init() < 0)
        fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());
    /**********************************************************************************************************************/

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderClear(renderer);

    SDL_Texture *texture[ligneTexture][colonneTexture];
    char nomFichiers[ligneTexture][colonneTexture][tailleMaxFichiers] = {{"./panther.png", "./background_jungle.png", "./panther.png", "./panther.png", "./panther.png", "./panther.png", "./panther.png"},{ "./panther.png", "./panther.png", "./panther.png", "./panther.png", "./panther.png", "./panther.png", "./panther.png"}};

    for (int i = 0; i < ligneTexture; i++)
    {
        for (int j = 0; j < colonneTexture; j++)
        {
            texture[i][j] = IMG_LoadTexture(renderer, nomFichiers[i][j]);
            if (texture[i][j] == NULL)
                end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
        }
    }
    /*
        // SDL_Texture *my_texture;
        texture[0][0] = IMG_LoadTexture(renderer, "./panther.png");
        if (texture[0][0] == NULL)
            end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

        // SDL_Texture *my_texture2;
        texture[1][1] = IMG_LoadTexture(renderer, "./background_jungle.png");
        if (texture[1][1] == NULL)
            end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    */
    SDL_Rect
        source = {0},
        source2 = {0},           // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0},
        destination2 = {0}, // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state3 = {0},
        destination3 = {0}; // Rectangle de la vignette en cours dans la planche

    int xImage1 = 0, xImage2 = 242, xImage3 = 444, xImage4 = 690;
    int wImage1 = 242, wImage2 = 202, wImage3 = 246, wImage4 = 228;

    int xImages[5] = {xImage1, xImage2, xImage3, xImage4, xImage4};
    int wImages[5] = {wImage1, wImage2, wImage3, wImage4, wImage4};

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(texture[0][0], NULL, NULL,
                     &source.w, &source.h);
    SDL_QueryTexture(texture[0][1], NULL, NULL,
                     &source2.w, &source2.h);
    destination2 = window_dimensions;
    destination.y = // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h) / 2;
    destination.x = // La course se fait en milieu d'écran (en vertical)
        0;

    destination3.x = (window_dimensions.w) / 2;
    destination3.y = 0;

    int speed = 9;
    int nb_it = 0;
    float zoom = 1.0;
    int attaque = 1;

    while (nb_it <= 60)

    {
        int courant;
        destination.x += speed;

        state.y = 0;
        if (nb_it == 30)
        {
            attaque = 0;
        }
        state.h = source.h;

        if (attaque == 0)
        {
            courant = nb_it % 3;
            state.x = xImages[courant];
            state.w = wImages[courant];
        }
        else if (attaque == 1)
        {
            courant = nb_it % 5;
            state.x = xImages[courant];
            state.w = wImages[courant];
        }

        destination.w = state.w * zoom; // Largeur du sprite à l'écran
        destination.h = state.h * zoom; // Hauteur du sprite à l'écran

        ///////////////////////////////////////
        int courant3;
        destination3.y += speed;

        state3.y = 0;
        if (nb_it == 30)
        {
            attaque = 0;
        }
        state3.h = source.h;

        if (attaque == 0)
        {
            courant3 = (nb_it + 1) % 3;
            state3.x = xImages[courant3];
            state3.w = wImages[courant3];
        }
        else if (attaque == 1)
        {
            courant3 = (nb_it + 1) % 5;
            state3.x = xImages[courant3];
            state3.w = wImages[courant3];
        }

        destination3.w = state3.w * zoom; // Largeur du sprite à l'écran
        destination3.h = state3.h * zoom; // Hauteur du sprite à l'écran

        //////////////////////////////////////////

        SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, texture[0][1], &source2, &destination2);
        SDL_RenderCopy(renderer, texture[0][0], // Préparation de l'affichage
                       &state,
                       &destination);
        SDL_RenderCopy(renderer, texture[0][0], // Préparation de l'affichage
                       &state3,
                       &destination3);
        SDL_RenderPresent(renderer); // Affichage
        if (courant == 10000)
        {
            SDL_Delay(500);
        }
        else
        {
            SDL_Delay(150);
        }
        printf(" nb_it : %d\n courant : %d\n", nb_it, courant);
        nb_it++;
    }
    SDL_RenderClear(renderer);
    IMG_Quit();

    for (int i = 0; i < ligneTexture; i++)
    {
        for (int j = 0; j < colonneTexture; j++)
        {
            SDL_DestroyTexture(texture[i][j]);
        }
    }

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}