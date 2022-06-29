#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

//#include "general.h"

#define NBETATS 19
#define ETATMAX 35
#define NBDEFENSES 3
#define TAILLECHAR 5

void gestionTable(float tableQ[NBETATS][NBDEFENSES], int tablesauv[2][NBETATS], float gamma, float epsilon);
int tailleTableau(int tablesauv[2][NBETATS]);
void initTableQ(float tableQ[NBETATS][NBDEFENSES]);
void affichageTable(float tableQ[NBETATS][NBDEFENSES]);

#endif