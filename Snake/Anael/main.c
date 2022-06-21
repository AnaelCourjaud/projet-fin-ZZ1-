#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>


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
  {                                // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)
  {                            // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
    window = NULL;
  }

  SDL_Quit();

  if (!ok)
  { // On quitte si cela ne va pas
    exit(EXIT_FAILURE);
  }
}

void draw(SDL_Renderer *renderer, int posX, int posY)
{ // Je pense que vous allez faire moins laid :)

  int rayonCercle = 100;

  // SDL_Rect HitBoxRectCercle;

  /*
    HitBoxRectCercle.x = posX-100;
    HitBoxRectCercle.y = posY-100;
    HitBoxRectCercle.w = 200;
    HitBoxRectCercle.h = 200;
  */

  /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
  for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
  {
    SDL_SetRenderDrawColor(renderer,
                           (cos(angle * 2) + 1) * 255 / 2, // quantité de Rouge
                           (cos(angle * 5) + 1) * 255 / 2, //          de vert
                           (cos(angle) + 1) * 255 / 2,     //          de bleu
                           255);                           // opacité = opaque
    SDL_RenderDrawPoint(renderer,
                        posX + rayonCercle * cos(angle),  // coordonnée en x
                        posY + rayonCercle * sin(angle)); //            en y
  }
}

int main(int argc, char **argv)
{
  srand( time( NULL ) );

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

  SDL_Point posCercle;
  SDL_Point vitesseCercle;
  SDL_Color couleurFond;

  int recupCoord = 0;

  posCercle.x = 10;
  posCercle.y = 10;

  vitesseCercle.x = 10;
  vitesseCercle.y = 10;

  couleurFond.r = 128;
  couleurFond.g = 128;
  couleurFond.b = 128;
  couleurFond.a = 255;

  SDL_bool
      program_on = SDL_TRUE,   // Booléen pour dire que le programme doit continuer
      interessant = SDL_FALSE; // Booléen pour dire que le programme est en pause
  SDL_Event event;             // Evènement à traiter

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
          program_on = SDL_FALSE; // 'escape' ou 'q', d'autres façons de quitter le programme
          interessant = SDL_TRUE;
          break;
        default: // Une touche appuyée qu'on ne traite pas
          break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN: // Click souris
        if (SDL_GetMouseState(NULL, NULL) &
            SDL_BUTTON(SDL_BUTTON_LEFT))
        {
          recupCoord = 1;
          interessant = SDL_TRUE;
        }
        else if (SDL_GetMouseState(NULL, NULL) &
                 SDL_BUTTON(SDL_BUTTON_RIGHT))
        { // Si c'est un click droit
          // change_state(state, 2, window);           // Fonction à éxécuter lors d'un click droit
        }
        break;
      default: // Les évènements qu'on n'a pas envisagé
        break;
      }
    }
    interessant = SDL_FALSE;

    if (recupCoord == 1)
    {
      int x;
      int y;                     // Si c'est un click gauche
      SDL_GetMouseState(&x, &y); // Fonction à éxécuter lors d'un click gauche
      posCercle.x = x;
      posCercle.y = y;
      recupCoord = 0;

      vitesseCercle.x = ((rand() % 20) - 10)*2;
      vitesseCercle.y = ((rand() % 20) - 10)*2;
    }

    if(posCercle.x >= tailleFenetre.x && posCercle.y > 0 && posCercle.y < tailleFenetre.y){
      vitesseCercle.x = -1*vitesseCercle.x;
    }else if(posCercle.x <= 0 && posCercle.y > 0 && posCercle.y < tailleFenetre.y){
      vitesseCercle.x = -1*vitesseCercle.x;
    }else if(posCercle.y >= tailleFenetre.y && posCercle.x > 0 && posCercle.x < tailleFenetre.x){
vitesseCercle.y = -1*vitesseCercle.y;
    }else if(posCercle.y <= 0 && posCercle.x > 0 && posCercle.x < tailleFenetre.x){
vitesseCercle.y = -1*vitesseCercle.y;
    }else if(posCercle.x >= 0 && posCercle.x <= tailleFenetre.x && posCercle.y >= 0 && posCercle.y <= tailleFenetre.y){

      }else{
      posCercle.x = 100;
      posCercle.y = 100;
    }

    couleurFond.r = 255 * abs(vitesseCercle.x) * abs(vitesseCercle.y) / 100;
    couleurFond.g = 255 * posCercle.x / tailleFenetre.x;
    couleurFond.b = 255 * posCercle.y / tailleFenetre.y;

    SDL_SetRenderDrawColor(renderer, couleurFond.r, couleurFond.g, couleurFond.b, couleurFond.a);
    SDL_RenderClear(renderer);
    draw(renderer, posCercle.x, posCercle.y); // appel de la fonction qui crée l'image
    SDL_RenderPresent(renderer);
    // draw(state, &color, renderer, window);          // On redessine

    posCercle.x += vitesseCercle.x;
    posCercle.y += vitesseCercle.y;

    SDL_Delay(10); // Petite pause
  }

  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}