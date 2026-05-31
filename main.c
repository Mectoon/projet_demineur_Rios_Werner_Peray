#include <stdio.h>
#include "jeu.h"
#include "sauvegarde.h"
int main(void) {
    int taille=0;           //Déclaration de la variable comprenant la valeur de la largeur de la grille
    Partie *p;              //Déclaration du pointeur p vers la structure Partie


    afficherMenuDemineur();


    scanf("%d", &taille);
    p->taille= taille;





    p = malloc(sizeof(Partie));         //Allocation dynamique de mémoire pour la structure Partie
    if (p == NULL) {            //Test de réussite de l'allocation
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }
    creer_tableau_vide(p, taille);











    free(p);                            //Libération de la mémoire à la fin du programme
    return 0;
}