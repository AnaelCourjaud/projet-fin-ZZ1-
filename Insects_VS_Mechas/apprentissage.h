#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "general.h"


void gestionTable(float tableQ[NBPERCEPTION][NBDEFENSES], int tablesauv[2][NBPERCEPTION], float gamma, float epsilon);
int preferencelearning(int perception, float tableQ[NBPERCEPTION][NBDEFENSES], float epsilon);
float reelAleatoireUniforme();
int tailleTableau(int tablesauv[2][NBPERCEPTION]);
void initTableQ(float tableQ[NBPERCEPTION][NBDEFENSES]);
void affichageTable(float tableQ[NBPERCEPTION][NBDEFENSES]);
void sauvegarder(float tableQ[NBPERCEPTION][NBDEFENSES]);
int loadConfig(float tableQ[NBPERCEPTION][NBDEFENSES], char nom_fic[100]);

#endif