#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "general.h"

void gestionTable(float tableQ[NBPERCEPTION][NBDEFENSES], int tablesauv[2][NBRCOUPSMAXENREGISTRABLES],int nombreDeCoupsIA, float gamma, float epsilon);
int preferencelearning(int perception, float tableQ[NBPERCEPTION][NBDEFENSES], float temperature);
int noaleatoire(int perception, float tableQ[NBPERCEPTION][NBDEFENSES]);
float reelAleatoireUniforme();
//int tailleTableau(int tablesauv[2][NBPERCEPTION]);
void initTableQ(float tableQ[NBPERCEPTION][NBDEFENSES]);
void affichageTable(float tableQ[NBPERCEPTION][NBDEFENSES]);
void affichageSauv( int tablesauv[2][NBRCOUPSMAXENREGISTRABLES], int taille);
void sauvegarder(float tableQ[NBPERCEPTION][NBDEFENSES]);
int loadConfig(float tableQ[NBPERCEPTION][NBDEFENSES], char nom_fic[100]);



#endif