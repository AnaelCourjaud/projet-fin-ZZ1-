#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define TAILLEMAX 500
/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
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

void draw(SDL_Renderer *renderer, int x, int y, int rad, int R, int G, int B)
{
    /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
    {
        SDL_SetRenderDrawColor(renderer,
                               R, G, B, //          de bleu
                               255);    // opacité = opaque
        SDL_RenderDrawPoint(renderer,
                            x + rad * cos(angle),  // coordonnée en x
                            y + rad * sin(angle)); //            en y
    }
}

int main(int argc, char **argv)

{
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL,
                 *renderer2 = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                              screen.h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/
    /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */
 
    

    SDL_bool
        program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;           // Evènement à traiter

    while (program_on)
    { // La boucle des évènements
        if (SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
          // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                              // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                              // l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                { // la touche appuyée est ...

                case SDLK_ESCAPE:   // 'ESCAPE'
                case SDLK_q:        // ou 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        draw(renderer, rand() % 1920, rand() % 1080, 1, 255, 255, 255); // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);
        SDL_Delay(50); // Petite pause
    }
    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer2);
    return EXIT_SUCCESS;
}
