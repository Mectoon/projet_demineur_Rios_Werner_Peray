#include <stdio.h>
#include "jeu.h"
#include "sauvegarde.h"
#include <stdlib.h>

void jouer_partie(Partie *p);;

int main(void) {
    int choix;          // Choix de l'utilisateur dans le menu
    Partie *p;          // Pointeur vers la structure Partie
    int quitter = 0;    // 0 = on reste dans le programme, 1 = on quitte

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

            default:                                    //Message d'erreur si la saisie de l'utilisateur n'est pas valide
                printf("Erreur de saisie ");
                break;

        }
    }

    free(p);                      //Libération de la mémoire à la fin du programme
    return 0;
}

/* Fonction qui gere une partie en cours */
void jouer_partie(Partie *p) {
    int action;
    int ligne;
    int colonne;

    while (p->vies > 0 && p->etat == 0) {  // Tant que le joueur a encore au moins une vie et que la partie est encore en cours, on continue la boucle de jeu

        gestion_malus(p);
        afficher_grille(p);

        printf("Vies restantes : %d\n", p->vies);
        printf("Tour : %d\n", p->tour);

        printf("\n1) Jouer un coup\n");
        printf("2) Sauvegarder et revenir au menu\n");
        printf("3) Revenir au menu sans sauvegarder\n");
        printf("Votre choix : ");
        scanf("%d", &action);

        switch (action) {

            case 1:
                printf("Choisissez une ligne : ");
                scanf("%d", &ligne);

                printf("Choisissez une colonne : ");
                scanf("%d", &colonne);

                reveler_case(p, ligne, colonne);  // Appelle la fonction qui révèle la case choisie par le joueur avec les coordonnées ligne / colonne saisies

                if (p->vies <= 0) {
                    p->etat = 2;
                    printf("\nVous avez perdu la partie.\n");
                    return;
                }

                if (partie_gagnee(p) == 1) {
                    p->etat = 1;
                    printf("\nBravo ! Vous avez gagne la partie.\n");
                    return;
                }

                p->tour++;
                break;

            case 2:
                SAUV_sauvegarde(p);
                printf("\nPartie sauvegardee. Retour au menu.\n");
                return;

            case 3:
                printf("\nRetour au menu sans sauvegarder.\n");
                return;

            default:
                printf("\nChoix invalide.\n");
                break;
        }
    }
}