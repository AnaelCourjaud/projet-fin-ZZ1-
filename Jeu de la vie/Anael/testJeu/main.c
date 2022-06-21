#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HAUTEUR 17
#define LARGEUR 31


int survie[9] = {0, 1, 1, 1, 1, 1, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};


int grille[HAUTEUR][LARGEUR];
int nouvelleGrille[HAUTEUR][LARGEUR];

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
    {                      
int grille[HAUTEUR][LARGEUR];
int nouvelleGrille[HAUTEUR][LARGEUR];            // Destruction si nécessaire du renderer
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

void affichage(int grille[HAUTEUR][LARGEUR], SDL_Renderer *renderer)
{
    int i;
    int j;

    for (i = 0; i < HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            SDL_Rect rect = {40 * j + 1 + 15, 40 * i + 1 + 20, 38, 38};

            if (grille[i][j] == 0)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}



int nb_voisins(int i, int j, int grille[HAUTEUR][LARGEUR], int monde)
{
    int voisins = 0;
    int horz[3] = {-1, 0, 1};
    int vert[3] = {-1, 0, 1};
    int maxvert = 3;
    int minvert = 0;
    int minhorz = 0;
    int maxhorz = 3;
    if (monde == 0) // normal
    {
        if (j == 0)
            minhorz = 1;
        if (j == LARGEUR - 1)
            maxhorz = 2;
        if (i == 0)
            minvert = 1;
        if (i == HAUTEUR - 1)
            maxvert = 2;
    }
    else // torique
    {
        if (j == 0)
            horz[0] = LARGEUR - 1 - j;
        if (j == LARGEUR - 1)
            horz[2] = 0 - j;
        if (i == 0)
            vert[0] = HAUTEUR - 1 - i;
        if (i == HAUTEUR - 1)
            vert[2] = 0 - i;
    }

    for (int b = minvert; b < maxvert; b++)
    {
        for (int a = minhorz; a < maxhorz; a++)
        {

            if (horz[a] != 0 || vert[b] != 0)
            {
                if (grille[vert[b] + i][horz[a] + j] == 1)
                    voisins++;
            }
        }
    }
    return voisins;
}

int nouvgen(int i, int j, int grille[HAUTEUR][LARGEUR], int nouvgrille[HAUTEUR][LARGEUR], int monde)
{
    int voisins = nb_voisins(i, j, grille, monde);
    int modif = 0;
    if (grille[i][j] == 1)
    {
        if (survie[voisins] == 0)
        {
            nouvgrille[i][j] = 0;
            modif++;
        }
        else
        {
            nouvgrille[i][j] = 1;
        }
    }
    else
    {
        if (naissance[voisins] == 1)
        {
            nouvgrille[i][j] = 1;
            modif++;
        }
        else
        {
            nouvgrille[i][j] = 0;
        }
    }
    return modif;
}

int nouvgengrille(int grille[HAUTEUR][LARGEUR], int nouvgrille[HAUTEUR][LARGEUR], int monde)
{
    int nb_modif = 0;
    for (int i = 0; i < HAUTEUR; i++)
    {
        for (int j = 0; j < LARGEUR; j++)
            nb_modif = nb_modif + nouvgen(i, j, grille, nouvgrille, monde);
    }
    return nb_modif;
}


void initGrille()
{
    for (int i = 0; i < HAUTEUR; i++)
    {
        for (int j = 0; j < LARGEUR; j++)
        {
            grille[i][j] = 0;
        }
    }
    grille[6][6] = 1;
    grille[6][5] = 1;
    grille[7][5] = 1;
    grille[8][5] = 1;
    grille[7][4] = 1;
    /*grille[2][0] = 1;
    grille[5][4] = 1;
    grille[5][3] = 1;
    grille[0][3] = 1;*/
}


int main(int argc, char **argv)
{
    srand(time(NULL));

    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Point tailleFenetre;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.x = screen.w * 0.66;
    tailleFenetre.y = screen.h * 0.66;
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

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/
    /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */

    SDL_bool
        program_on = SDL_TRUE,   // Booléen pour dire que le programme doit continuer
        interessant = SDL_FALSE; // Booléen pour dire que le programme est en pause
    SDL_Event event;             // Evènement à traiter

    int ok = 0;

    initGrille();

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
        */

        affichage(grille, renderer);
        SDL_RenderPresent(renderer);

        int N_modifs = nouvgengrille(grille, nouvelleGrille, 0);

        for (int i = 0; i < HAUTEUR; i++)//remplacer grille par nouvelleGrille
        {
            for (int j = 0; j < LARGEUR; j++)
            {
                grille[i][j] = nouvelleGrille[i][j];
            }
        }

        SDL_Delay(200); // Petite pause
    }

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}