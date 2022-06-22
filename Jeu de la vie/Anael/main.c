#include "module.h"

int main(int argc, char *argv[])
{

    /*
    initialisation SDL, tableau etc...
    */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Point tailleFenetre;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + TTF + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.x = screen.w;
    tailleFenetre.y = screen.h;
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);
    printf("Pour fermer : cliquer sur la croix, ou alors 'q' ou alors 'ESCAPE'. Bon trip !\n");

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

    int CONTROLE = MONDE;
    int chrono = 0;

    int grille[HAUTEUR][LARGEUR];
    int nouvelleGrille[HAUTEUR][LARGEUR];

    //clock_t begin = clock();

    initGrille(grille);

    SDL_Event event; // Evènement à traiter
                     /*
                         int parametre = 0; // si parametre == 0, alors on considère que l'utilisateur n'a pas rentré de parametre, si ==1 si.
                         if (argc == 2)
                             if (strlen(argv[1]) < TAILLE_MAX)
                                 parametre = chargerConfigInit(grille, argc, argv[1]); // si il y a parametre, ça ouvre le fichier en question, si y a une erreur quelquepart, ça fait comme si il n'y avait pas de paramètre. retourne 0 si pas de parametre et 1 si il y a un parametre
                     */

    while (CONTROLE != FIN)
    {
        int interessant = 0;
        int changerEtat = 0;
        while (interessant == 0 && SDL_PollEvent(&event))
        {
            // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {              // En fonction de la valeur du type de cet évènement
            case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la // fenêtre
                // program_on = SDL_FALSE;
                CONTROLE = FIN;
                interessant = 1; // Il est temps d'arrêter le programme
                break;
                /*
              case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                                // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                                // l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                {                // la touche appuyée est ...
                case SDLK_p:     // 'p'
                case SDLK_SPACE: // ou 'SPC'
                  // paused = !paused; // basculement pause/unpause
                  break;
                case SDLK_ESCAPE:         // 'ESCAPE'
                case SDLK_q:              // ou 'q'
                 // program_on = SDL_FALSE; // 'escape' ou 'q', d'autres façons de quitter le programme
                  interessant = 1;
                  break;
                default: // Une touche appuyée qu'on ne traite pas
                  break;
                }
                break;
                */
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    changerEtat = 1;
                    interessant = 1;
                }

                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        interessant = 0;

        switch (CONTROLE)
        {
        default:
            CONTROLE = ERREUR;
            break;
        case FIN:
            break;
        case ERREUR:
            break;
        case MONDE:
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            SDL_RenderClear(renderer);
            //"Bienvenue dans le jeu de la vie, choisissez votre Monde :"
            // bouton "monde torique " et bouton "monde normal"
            /*
                        if (parametre == 1)
                        {
                            if (parametre == 1)
                                CONTROLE = ITER;
                            else if (parametre == 0)
                                CONTROLE = CONFIG;
                            else
                                CONTROLE = ERREUR;
                        }
                        */
            if (changerEtat == 1)
            {
                CONTROLE = CONFIG;
                changerEtat = 0;
            }

            break;
        case CONFIG:
            SDL_SetRenderDrawColor(renderer, 128, 255, 255, 255);
            SDL_RenderClear(renderer);

            if (changerEtat == 1)
            {
                CONTROLE = ITER;
                changerEtat = 0;
                //begin = clock();
                chrono=0;
            }
            break;
        case ITER:

            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            SDL_RenderClear(renderer);

            /*
                    if (ok == 0)
                    {
                        for (int i = 0; i < HAUTEUR; i++)
                        {
                            for (int j = 0; j < LARGEUR; j++)
                            {
                                printf("nbre voisins de (%d,%d): %d\n", i, j, nb_voisins(i, j, grille, 1));
                                printf("il y a modification : %d\n", nouvgen(i, j, grille, nouvelleGrille, 1));
                            }
                        }
                        ok = 1;
                    }
*/

            affichage(grille, renderer);
            //SDL_RenderPresent(renderer);

            if(chrono >= 100){
            int N_modifs = nouvgengrille(grille, nouvelleGrille, 0);

            for (int i = 0; i < HAUTEUR; i++) // remplacer grille par nouvelleGrille
            {
                for (int j = 0; j < LARGEUR; j++)
                {
                    grille[i][j] = nouvelleGrille[i][j];
                }
            }
            //begin = clock();
            chrono =0;
            }

            if (changerEtat == 1)
            {
                CONTROLE = PAUSE;
                changerEtat = 0;
            }
            break;
        case PAUSE:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderClear(renderer);
            if (changerEtat == 1)
            {
                CONTROLE = STABLE;
                changerEtat = 0;
            }
            // ça affiche l'écran de jeu avec, le nombre d'itérations, une bulle "Pause" et un bouton "au Boulot !"
            // si tu fais 's' ou 'S' ça "sauvegarde"
            // si t'appuies sur le bouton "au Boulot !" le jeu reprend.

            break;
        case STABLE:
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderClear(renderer);
            if (changerEtat == 1)
            {
                CONTROLE = FIN;
                changerEtat = 0;
            }
            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(20); // Petite pause
        chrono++;
        printf(" chrono : %d\n",chrono );
    }
    /*
        SDL_bool
            program_on = SDL_TRUE,   // Booléen pour dire que le programme doit continuer
            interessant = SDL_FALSE; // Booléen pour dire que le programme est en pause
        SDL_Event event;             // Evènement à traiter

        int ok = 0;

        initGrille(grille);

        while (program_on)
        { // La boucle des évènements
            while (!interessant && SDL_PollEvent(&event))
            { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                // terminé le programme Défiler l'élément en tête de file dans 'event'
                switch (event.type)
                {              // En fonction de la valeur du type de cet évènement
                case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la // fenêtre
                    program_on = SDL_FALSE;
                    interessant = SDL_TRUE; // Il est temps d'arrêter le programme
                    break;

                default: // Les évènements qu'on n'a pas envisagé
                    break;
                }
            }
            interessant = SDL_FALSE;

            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            SDL_RenderClear(renderer);

            /*
                    if (ok == 0)
                    {
                        for (int i = 0; i < HAUTEUR; i++)
                        {
                            for (int j = 0; j < LARGEUR; j++)
                            {
                                printf("nbre voisins de (%d,%d): %d\n", i, j, nb_voisins(i, j, grille, 1));
                                printf("il y a modification : %d\n", nouvgen(i, j, grille, nouvelleGrille, 1));
                            }
                        }
                        ok = 1;
                    }


            affichage(grille, renderer);
            SDL_RenderPresent(renderer);

            int N_modifs = nouvgengrille(grille, nouvelleGrille, 0);

            for (int i = 0; i < HAUTEUR; i++) // remplacer grille par nouvelleGrille
            {
                for (int j = 0; j < LARGEUR; j++)
                {
                    grille[i][j] = nouvelleGrille[i][j];
                }
            }

            SDL_Delay(200); // Petite pause
        }*/

    // SDL_Delay(10000);
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}