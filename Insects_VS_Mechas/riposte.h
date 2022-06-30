#ifndef RIPOSTE_H
#define RIPOSTE_H


#define NBENNEMIVAGUE 3 //nb d'ennemis au debut de la vague
#define NBRMAXCOMBATTANTS 10

#include "general.h"
#include "affichage.h"

int appartient(int , int []);
void initValNull(int [], combattant_t *[]);
void supprValNull(int [], combattant_t *[]);
void tristat(combattant_t *[], int [], int []);
int rechercheIndPhysInf(int [], int , combattant_t *[]);
int rechercheIndMagieInf(int [], int , combattant_t* []);
int rechercheMagieNulle( combattant_t *[]);
int recherchePhysNulle( combattant_t *[]);
void degatInflige(combattant_t *[]);



#endif