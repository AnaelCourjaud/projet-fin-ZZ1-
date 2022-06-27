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

    window = SDL_CreateWindow("Insects_VS_Mechas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tailleFenetre.w, tailleFenetre.h, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    //  ************************* Création du renderer *************************

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    // ********************************************************************************
    // ********************************************************************************

    init(window, renderer, texture, tabPolices);

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    int ETATJEU = ACCUEIL;
    int i = 0;
    int j=0;

    sprite_t fondAccueil;
    sprite_t lore1;
    sprite_t lore2;
    sprite_t lore3;



    while (program_on)
    {
        // Voilà la boucle des évènements
        int interessant = 0;
        int choixFait = 0;

        // *************************  Gestion des evenements *****************************
        //                                                                             
        // *******************************************************************************

        while ((interessant == 0) && (SDL_PollEvent(&event)))
        {   // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
            // de file dans 'event'
            switch (event.type)
            { 
            case SDL_QUIT:
                interessant = 1;        // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYUP: // Le type de event est : une touche lachée

                switch (event.key.keysym.sym)
                { // la touche appuyée est ...
                case SDLK_SPACE:
                    if (ETATJEU == ACCUEIL)
                    {
                        ETATJEU = LORE1;
                    }
                    else if (ETATJEU == LORE1)
                    {
                        ETATJEU = LORE2;
                    }
                    else if (ETATJEU == LORE2)
                    {
                        ETATJEU = LORE3;
                    }
                    else if (ETATJEU == LORE3)
                    {
                        ETATJEU = VAGUE;
                    }
                    interessant = 1;
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

            fondAccueil.textureSprite = texture[indiceFondAccueil];
            creationFond(fondAccueil.textureSprite, window, renderer, 0, 0);
            break;
        case LORE1:
            lore1.textureSprite = texture[indiceLore1];
            creationFond(lore1.textureSprite, window, renderer, 0, 0);

            break;
        case LORE2:
            lore2.textureSprite = texture[indiceLore2];
            creationFond(lore2.textureSprite, window, renderer, 0, 0);

            break;
        case LORE3:
            lore3.textureSprite = texture[indiceLore3];
            creationFond(lore3.textureSprite, window, renderer, 0, 0);


            break;
        case VAGUE:
            printf("Jeu en route");
           
            break;
        case ATTENTERIPOSTE:
            
            break;
        case RIPOSTE:
            
            break;
        case FINDEVAGUE:
           
            break;
        case FINJEU:
           
            break;
        default:
            ETATJEU = ERREUR;
            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }

    end_sdl(1, "FIN NORMALE", window, renderer);
    return 0;
}