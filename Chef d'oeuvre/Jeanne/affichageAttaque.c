#include "affichageAttaque.h"

char spriteaenvoyer(int resultat, int etat[2])
{
    char spriteaenvoyer;
    int total;
    // ABCD AB/CD: 0X = attaque perso/ennemi de l'etat X(0,1,2,3); 10 = degat ; 20 = attente ;31 = victoire; 32 = défaite
    switch (resultat)
    {
    case 0:
        total = 100 * etat[0] + 10 + etat[1];
        spriteaenvoyer = strcat('0', total + '0');
    case 1:
        total = 1000 + 100 * etat[0] + etat[1];
        spriteaenvoyer = total + '0';
    case 2:
        total = 2000 + 20;
        spriteaenvoyer = total + '0';
    case 3:
        total = 100 * etat[0] + etat[1];
        spriteaenvoyer = strcat('0', total + '0');
    }
    return spriteaenvoyer;
}

int main()
{
    int PV[2] = {10, 6};
    int etat[2] = {EAU, DEFENSE};
    int resultat = gagnant(etat);
    char nomsprite = spriteaenvoyer(etat);
    printf("%s", nomsprite);
    return 0;
}