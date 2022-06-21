#ifndef __SAUVEGARDER_H__
#define __SAUVEGARDER_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define HAUTEUR 3
#define LARGEUR 5

void sauvegarder(int[HAUTEUR][LARGEUR]);
int loadConfig(int [HAUTEUR][LARGEUR], char [100]);

#endif