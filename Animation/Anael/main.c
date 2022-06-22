#include "module.h"

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

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Texture *my_texture;
    my_texture = IMG_LoadTexture(renderer, "./panther.png");
    if (my_texture == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    int xImage1 = 0, xImage2 = 242, xImage3 = 444, xImage4 = 690;
    int wImage1 = 242, wImage2 = 202, wImage3 = 246, wImage4 = 228;

    int xImages[4] = {xImage1, xImage2, xImage3, xImage4};
    int wImages[4] = {wImage1, wImage2, wImage3, wImage4};

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image
                                            /*
                                                int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
                                                float zoom = 2;                      // zoom, car ces images sont un peu petites
                                                int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
                                                    offset_y = source.h;             // La hauteur d'une vignette de l'image, marche car la planche est bien réglée
                                        
                                                state.x = 0;        // La première vignette est en début de ligne
                                                state.y = 0;        // On s'intéresse à la 4ème ligne, le bonhomme qui court
                                                state.w = offset_x; // Largeur de la vignette
                                                state.h = offset_y; // Hauteur de la vignette
                                        
                                                destination.w = offset_x * zoom; // Largeur du sprite à l'écran
                                                destination.h = offset_y * zoom; // Hauteur du sprite à l'écran
                                            */

    destination.y = // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) / 2;
    destination.x = // La course se fait en milieu d'écran (en vertical)
        0;

    int speed = 9;
    int nb_it = 0;
    float zoom = 1.0;
    int attaque =1;

    while(nb_it <=120)

    {int courant;
destination.x += speed;
        
        state.y = 0;
        
        state.h = source.h;

        if(attaque == 0){
            courant = nb_it % 3;
            state.x = xImages[courant];
            state.w = wImages[courant];

        }else if(attaque ==1){
            courant = nb_it % 4;
            state.x = xImages[courant];
            state.w = wImages[courant];

        }
        

        destination.w = state.w * zoom; // Largeur du sprite à l'écran
        destination.h = state.h * zoom; // Hauteur du sprite à l'écran

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
        SDL_RenderPresent(renderer); // Affichage
        if(courant == 3){
            SDL_Delay(500);
        }else{
        SDL_Delay(150);
        }
        printf(" nb_it : %d\n courant : %d\n", nb_it, courant);
        nb_it++;
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
                               /* 00;
                                   for (int x = 0; x < window_dimensions.w - destination.w; x += speed)
                                   {
                                       destination.x = x;   // Position en x pour l'affichage du sprite
                                       state.x += offset_x; // On passe à la vignette suivante dans l'image
                                       state.x %= source.w; // La vignette qui suit celle de fin de ligne est
                                                            // celle de début de ligne
                           
                                       SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
                                       SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                                                      &state,
                                                      &destination);
                                       SDL_RenderPresent(renderer); // Affichage
                                       SDL_Delay(80);               // Pause en ms
                                   }
                                   SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
                                                              /*
                                                     float zoom = 1.0;                       // Facteur de zoom à appliquer
                                                     destination.w = source.w ;        // La destination est un zoom de la source
                                                     destination.h = source.h ;        // La destination est un zoom de la source
                                                     destination.x =
                                                         (window_dimensions.w - destination.w) / 2; // La destination est au milieu de la largeur de la fenêtre
                                                     destination.y =
                                                         (window_dimensions.h - destination.h) / 2;
                           
                                                     SDL_RenderCopy(renderer, my_texture,
                                                                    &source,
                                                                    &destination);
                           
                                                     //...
                                                     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                                     SDL_RenderDrawLine(renderer,
                                                                        (window_dimensions.w - destination.w) / 2, 0, // x,y du point de la première extrémité
                                                                        (window_dimensions.w - destination.w) / 2, window_dimensions.h);
                                                     SDL_RenderDrawLine(renderer,
                                                                        (window_dimensions.w - destination.w) / 2 + source.w, 0, // x,y du point de la première extrémité
                                                                        (window_dimensions.w - destination.w) / 2 + source.w, window_dimensions.h);
                                                     SDL_RenderDrawLine(renderer,
                                                                        0, (window_dimensions.h - destination.h) / 2, // x,y du point de la première extrémité
                                                                        window_dimensions.w, (window_dimensions.h - destination.h) / 2);
                                                     SDL_RenderDrawLine(renderer,
                                                                        0, (window_dimensions.h - destination.h) / 2 + source.h, // x,y du point de la première extrémité
                                                                        window_dimensions.w, (window_dimensions.h - destination.h) / 2 + source.h);
                           
                                                     SDL_RenderDrawLine(renderer,
                                                                      (window_dimensions.w - destination.w) /2 + 242, 0,                                          // x,y du point de la première extrémité
                                                                      (window_dimensions.w - destination.w) /2 + 242, window_dimensions.h);
                                                     SDL_RenderDrawLine(renderer,
                                                                      (window_dimensions.w - destination.w) /2 + 444, 0,                                          // x,y du point de la première extrémité
                                                                      (window_dimensions.w - destination.w) /2 + 444, window_dimensions.h);
                                                     SDL_RenderDrawLine(renderer,
                                                                      (window_dimensions.w - destination.w) /2 + 690, 0,                                          // x,y du point de la première extrémité
                                                                      (window_dimensions.w - destination.w) /2 + 690, window_dimensions.h);
                           
                           
                           
                                                     SDL_RenderPresent(renderer);
                                                     SDL_Delay(5000);
                                                 */
    IMG_Quit();

    SDL_DestroyTexture(my_texture);

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}