#ifndef __AFFICHAGEATTAQUE_H__
#define __AFFICHAGEATTAQUE_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "resolution.h"

#define EAU 0
#define FEU 1
#define TERRE 2
#define DEFENSE 3

#define ligneTexture 2
#define colonneTexture 10

SDL_Texture * textureAttaque(SDL_Texture * [ligneTexture][colonneTexture], int , int [2], int );

#endif