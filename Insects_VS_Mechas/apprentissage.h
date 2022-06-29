#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#include "general.h"

#define NBPERCEPTION 19
#define PERCEPTIONMAX 35
#define NBDEFENSES 3
#define TAILLECHAR 5

void gestionTable(float tableQ[NBPERCEPTION][NBDEFENSES], int tablesauv[2][NBPERCEPTION], float gamma, float epsilon);
int preferencelearning(int perception, float tableQ[NBPERCEPTION][NBDEFENSES], float epsilon);
float reelAleatoireUniforme();
int tailleTableau(int tablesauv[2][NBPERCEPTION]);
void initTableQ(float tableQ[NBPERCEPTION][NBDEFENSES]);
void affichageTable(float tableQ[NBPERCEPTION][NBDEFENSES]);

#endif