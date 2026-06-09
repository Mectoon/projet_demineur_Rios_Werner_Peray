#include <stdio.h>
#include "jeu.h"
#include "sauvegarde.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    int choix;          // Choix de l'utilisateur dans le menu
    Partie *p;          // Pointeur vers la structure Partie
    int quitter = 0;    // 0 = on reste dans le programme, 1 = on quitte

    srand(time(0));  // Initialise au hasard pour placer les mines aléatoirement

    p = malloc(sizeof(Partie));   // Allocation dynamique de mémoire pour la structure Partie
    if (p == NULL) {              // Test de réussite de l'allocation
        printf("Erreur d'allocation memoire\n");
        return 1;
    }

    while (quitter == 0) {
        afficher_menu_demineur();

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                lancer_nouvelle_partie(p);
                p->tour = 1;
                jouer_partie(p);
                break;

            case 2:
                if (SAUV_charger_partie(p) == 1) {
                    printf("\nPartie chargee, amusez vous bien !\n");
                    jouer_partie(p);
                } else {
                    printf("\nAucune sauvegarde dispo.\n");
                }
                break;

            case 3:
                printf("\nVous avez quitte le jeu.\n");
                printf("A bientot !\n");
                quitter = 1;
                break;

            case 4:
                afficher_regles();
                break;

            default:
                printf("Erreur de saisie\n");
                break;
        }
    }

    free(p);   // Liberation de la mémoire à la fin du programme
    return 0;
}
