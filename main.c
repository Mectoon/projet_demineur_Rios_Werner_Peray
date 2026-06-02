#include <stdio.h>
#include "jeu.h"
#include "sauvegarde.h"

int main(void) {

    int choix;              //Variable qui stocke le choix de l'utilisateur dans le menu// Variable qui stocke le choix de l'utilisateur dans le menu
    int taille=0;           //Déclaration de la variable comprenant la valeur de la largeur de la grille
    Partie *p;              //Déclaration du pointeur p vers la structure Partie 
    int quitter =0;

    srand(time(0));  //Initialise au hasard pour placer les mines aléatoirement

    p = malloc(sizeof(Partie));         //Allocation dynamique de mémoire pour la structure Partie
    if (p == NULL) {            //Test de réussite de l'allocation
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }
    while (quitter == 0) {
        afficherMenuDemineur();

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                lancer_nouvelle_partie(p);
                break;

            case 2:
                printf("\nReprendre une partie n'est pas encore disponible.\n");


                //Partie a faire avec l'onglet sauvegarde.c.
                //Appeler une fonction qui charge une partie sauvegardee.

                break;

            case 3:
                printf("\nVous avez quitte le jeu.\n");
                quitter = 1;
                break;

            case 4:
                afficher_regles();
                break;
            default:                                    //Message d'erreur si la saisie de l'utilisateur n'est pas valide
                printf("Erreur de saisie ");
                break;

        }
    }

    free(p);                       //Libération de la mémoire à la fin du programme
    return 0;
}
