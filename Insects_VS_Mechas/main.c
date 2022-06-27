#include "initialisation.h"
#include "affichage.h"
//#include "affichageAttaque.h"
#include "general.h"

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Rect tailleFenetre;

    SDL_Texture *texture[nbrTextures];
    TTF_Font *tabPolices[nbrPolices];

    // ************** Initialisation de la SDL  + gestion de l'échec possible *********
    // ********************************************************************************

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    // ***************************** Texte ********************************************

    if (TTF_Init() < 0)
        fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());

    // *************************  Gestion des fenetres   *****************************

    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.w = screen.w * coefReducEcran; // réduction fenetre
    tailleFenetre.h = screen.h * coefReducEcran;

    //  ************************* Création de la fenêtre *************************

    window = SDL_CreateWindow("Insects_VS_Mechas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tailleFenetre.w, tailleFenetre.h, SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    //  ************************* Création du renderer *************************

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    // ********************************************************************************
    // ********************************************************************************

init(window, renderer, texture, tabPolices);



    sprite_t fond;
    insecte_t scarabe1;

    
    //fond.source = {0};
    //fond.destination ={0};
    fond.textureSprite = texture[indiceFondAccueil+1];
    SDL_QueryTexture(fond.textureSprite, NULL, NULL,
                     &fond.source.w, &fond.source.h);
    
    fond.destination.x = 20;
    fond.destination.y = 20;
    fond.destination.w = 200;
    fond.destination.h = 200;
 fond.source.x = 20;
    fond.source.y = 20;



/*
SDL_Texture * textureSprite = IMG_LoadTexture(renderer, "./Sprites/fondaccueil.png");
    SDL_Rect source ={0} ,destination = {0};

     SDL_QueryTexture(textureSprite, NULL, NULL,
                     &source.w, &source.h);

                     source.x = 20;
    source.y = 20;
    //source.w = 1000;
    //source.h = 1000;
    destination.x = 20;
    destination.y = 20;
    destination.w = 200;
    destination.h = 200;
*/
    SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);// mode Red, Green, Blue (tous dans 0..255)
    //SDL_RenderClear(renderer);

printf("avant copy\n");
//SDL_RenderCopy(renderer, textureSprite, &source, &destination);
SDL_SetRenderDrawColor(renderer, 255,255, 0, 255);
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     400, 400);
SDL_RenderCopy(renderer, fond.textureSprite, &fond.source, &fond.destination);

    SDL_RenderPresent(renderer);
    printf("avant délai\n");
    SDL_Delay(3000);
    printf("après délai\n");
SDL_DestroyTexture(textureSprite);

/*
SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    SDL_Texture *sprite1;
    SDL_Texture *sprite2;
    SDL_Texture *textureFond;

    int nbrImageSprite1;
    int nbrImageSprite2;
    int animationFinieTerminee = 1;
    int gameOver = 0;

    int ETATJEU = ACCUEIL;
    int i = 0;
    int j=0;

    int PV[2] = {10, 10};
    int etat[2] = {EAU, EAU};

    while (program_on)
    {
        // Voilà la boucle des évènements
        int interessant = 0;
        int choixFait = 0;
        int etatPrec; //sert à l'utilisation de la chaîne de Markov

    // *************************  Gestion des evenements *****************************
    //                                                                             
    // *******************************************************************************

        while ((interessant == 0) && (SDL_PollEvent(&event)))
        {   // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
            // de file dans 'event'
            switch (event.type)
            { // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:
                interessant = 1;        // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYUP: // Le type de event est : une touche lachée

                switch (event.key.keysym.sym)
                { // la touche appuyée est ...
                case SDLK_SPACE:

                    interessant = 1;
                    break;
                case SDLK_q:

                        interessant = 1;
                    
                    break;
                case SDLK_e:
           
                    interessant = 1;
                    break;
                case SDLK_f:
   
                    interessant = 1;
                    break;
                case SDLK_t:
   
                    interessant = 1;
                    break;
                case SDLK_d:

                    interessant = 1;
                    break;
                default:
                    break;
                }

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        interessant = 0;

        switch (ETATJEU)
        {
        case ERREUR:
            break;
        case ACCUEIL:


            break;
        case JEU:

           
            break;
        default:
            ETATJEU = ERREUR;
            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
*/
    end_sdl(1, "FIN NORMALE", window, renderer);
    return 0;
}