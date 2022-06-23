#include "resolution.h"
#include "affichage.h"

int main(int argc, char *argv[])
{

    /************** Initialisation de la SDL  + gestion de l'échec possible *********/
    /*                                                                              */
    /********************************************************************************/

    if(SDL_Init(SDL_INIT_VIDEO) !=0 ){
        SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError());    // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    /***************************** Texte ********************************************/
    /*                                                                              */
    /********************************************************************************/

    /*****Initialisation*****/

    if (TTF_Init() < 0) fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());

    /*************************  Gestion des fenetres   *****************************/
    /*                                                                             */
    /*******************************************************************************/

    SDL_DisplayMode screen;
    SDL_GetCurrentDisplayMode(0, &screen);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    /*tailleFenetre.x = screen.w;
    tailleFenetre.y = screen.h;
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);
    printf("Pour fermer : cliquer sur la croix, ou alors 'q' ou alors 'ESCAPE'. Bon trip !\n");*/

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de l'ambiance",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 
                              screen.w,screen.h,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );


    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


    /*************************  Gestion des evenements *****************************/
    /*                                                                             */
    /*******************************************************************************/

    SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
    SDL_Event event;                              // c'est le type IMPORTANT !!

    int ETATJEU = ACCUEIL;
    int affichage = 0;
    int i = 0;

    int PV[2] = {10, 6};
    int etat[2] = {EAU, EAU};

    while (program_on){
                                     // Voilà la boucle des évènements 
        int interessant = 0;
        int changerEtat = 0;

        while ((interessant == 0 )&&(SDL_PollEvent(&event))){                 // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
                                                    // de file dans 'event'
            switch(event.type){                       // En fonction de la valeur du type de cet évènement
                case SDL_QUIT :
                    interessant = 1;                         // Un évènement simple, on a cliqué sur la x de la fenêtre
                    program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
                    break;
                case SDL_KEYUP: // Le type de event est : une touche lachée

                    switch (event.key.keysym.sym)
                    { // la touche appuyée est ...
                        case SDLK_SPACE:
                            if (ETATJEU == ACCUEIL)
                            {
                                ETATJEU = JEU;
                            }
                            interessant = 1;
                            break;
                        case SDLK_q:
                            if (ETATJEU == JEU)
                            {
                                ETATJEU = ACCUEIL;
                            }
                            interessant =1;
                            break;
                        case SDLK_e:
                            etat[0] = 0;
                            interessant =1;
                            break;
                        case SDLK_f:
                            etat[0] = 1;
                            interessant =1;
                            break;
                        case SDLK_t:
                            etat[0] = 2;
                            interessant =1;
                            break;
                        case SDLK_d:
                            etat[0] = 3;
                            interessant =1;
                            break;
                        default:
                            break;
                    }
                
                default:                                  // L'évènement défilé ne nous intéresse pas
                    break;
            }
        }
        interessant = 0;

        switch (ETATJEU)
        {
            case ERREUR:
                break;
            case ACCUEIL:
                /*SDL_SetRenderDrawColor(renderer, 0, 145, 255, 255);
                SDL_RenderClear(renderer);*/
                SDL_RenderClear(renderer);
                creationImage("./Sprites/fond1.jpg", renderer, 1920, 1080, 0, 0);

                creationTexte("Bienvenue :", "normal", "./fonts/font.ttf", renderer, 100, 600, 100, 255);
                creationTexte("Commandes :", "surligne", "./fonts/font2.ttf", renderer, 90, 400, 300, 255);
                creationTexte("E pour attaque eau", "normal", "./fonts/font2.ttf", renderer, 90, 500, 450, 255);
                creationTexte("F pour attaque feu", "normal", "./fonts/font2.ttf", renderer, 90, 500, 550, 255);
                creationTexte("T pour attaque terre", "normal", "./fonts/font2.ttf", renderer, 90, 500, 650, 255);
                creationTexte("D pour defense", "normal", "./fonts/font2.ttf", renderer, 90, 500, 750, 255);
                creationTexte("Q pour revenir ici", "normal", "./fonts/font2.ttf", renderer, 90, 500, 850, 255);
                
                break;
            case JEU:
                //SDL_RenderClear(renderer);
                //creationImage("./Sprites/fond2.jpg", renderer, 1920, 1080, 0, 0);
                affichage = 1;
                /*SDL_RenderClear(renderer);
                creationImage("fond.jpg", renderer, 1920, 1080, 0, 0);*/
                

                
                break;
            case FINJEU:
                break;
            default:
                ETATJEU = ERREUR;
                break;
        }
        if (affichage == 1){
        Animation("./Sprites/persobase.png", "./Sprites/fond2.jpg", renderer, window, 400, 400, 200, 500, 2, i);
        i++;
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(150);
    }

    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window); 
    SDL_Quit();   
    TTF_Quit(); 
    return 0;
}