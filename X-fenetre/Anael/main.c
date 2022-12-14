#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  SDL_Window
      *window_1 = NULL,
      *window_2 = NULL,
      *window_3 = NULL;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError()); // l'initialisation de la SDL a échoué
    exit(EXIT_FAILURE);
  }

  /* Création de la fenêtre de gauche */
  window_1 = SDL_CreateWindow(
      "Fenêtre à gauche",    // codage en utf8, donc accents possibles
      0, 0,                  // coin haut gauche en haut gauche de l'écran
      400, 300,              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE); // redimensionnable

  if (window_1 == NULL)
  {
    SDL_Log("Error : SDL window 1 creation - %s\n",
            SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit();              // On referme la SDL
    exit(EXIT_FAILURE);
  }
  window_2 = SDL_CreateWindow(
      "Fenêtre à gauche",    // codage en utf8, donc accents possibles
      0, 0,                  // coin haut gauche en haut gauche de l'écran
      400, 300,              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE); // redimensionnable

  if (window_2 == NULL)
  {
    SDL_Log("Error : SDL window 2 creation - %s\n",
            SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit();              // On referme la SDL
    exit(EXIT_FAILURE);
  }
  window_3 = SDL_CreateWindow(
      "Fenêtre à gauche",    // codage en utf8, donc accents possibles
      0, 0,                  // coin haut gauche en haut gauche de l'écran
      400, 300,              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE); // redimensionnable

  if (window_3 == NULL)
  {
    SDL_Log("Error : SDL window 3 creation - %s\n",
            SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit();              // On referme la SDL
    exit(EXIT_FAILURE);
  }

  SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer

  int chrono = 0;

  while (program_on)
  {

    if (chrono <= 100)
    {
      SDL_SetWindowSize(window_1, 100 + chrono, 200);
      SDL_SetWindowSize(window_2, 100 + chrono, 200 + chrono);
      SDL_SetWindowSize(window_3, 100, 200 + chrono);

      SDL_SetWindowPosition(window_1, chrono, 0);
      SDL_SetWindowPosition(window_2, 0, chrono);
      SDL_SetWindowPosition(window_3, chrono, chrono);
    }
    else
    {
      SDL_SetWindowSize(window_1, 100 - chrono, 200);
      SDL_SetWindowSize(window_2, 100 - chrono, 200 - chrono);
      SDL_SetWindowSize(window_3, 100, 200 - chrono);

      SDL_SetWindowPosition(window_1, chrono, 0);
      SDL_SetWindowPosition(window_2, 0, chrono);
      SDL_SetWindowPosition(window_3, chrono, chrono);
    }

    SDL_Delay(10);
    chrono++;
    if (chrono == 500)
    {
      SDL_DestroyWindow(window_3);
      chrono += 100;
    }
    if (chrono >= 1000)
    {
      program_on = SDL_FALSE;
    }
  }

  SDL_Delay(1000);

  SDL_DestroyWindow(window_1);
  SDL_DestroyWindow(window_2);

  SDL_Quit();

  return 0;
}