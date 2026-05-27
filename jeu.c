//
// Created by arios on 27/05/2026.
//

#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>

void afficherMenuDemineur(void) {
    printf("\n");
    printf("*------------------------------*\n");
    printf("*----- Jeu de DEMINEUR -----*\n");
    printf("1) Nouvelle Partie\n");
    printf("2) Reprendre Partie\n");
    printf("3) Quitter le jeu\n");
    printf( "4) Regles du Jeu\n");
    printf("*------------------------------*\n");
    printf("Par Axel, Jules et Théodore\n");
}


void calculer_nombre_mines(Partie *p) {
    int nb_cases;
    int nb_mines = 0;

    // Calcul du nombre total de cases de la grille
    nb_cases = p->taille * p->taille;

    // Si difficulté facile
    if (p->difficulte == 1) {
        nb_mines = (int)(0.20 * nb_cases);
    }

    // Si difficulté moyenne
    else if (p->difficulte == 2) {
        nb_mines = (int)(0.25 * nb_cases);
    }

    // Si difficulté difficile
    else if (p->difficulte == 3) {
        nb_mines = (int)(0.30 * nb_cases);
    }

    // Stockage nombre mines dans la structure Partie
    p->nb_mines = nb_mines;

}

 /* Initialise toutes les cases de la grille :
 * - pas de mine
 * - case non visible
 * - 0 mine autour
 * - pas de bonus
 * - pas de malus
 */
void creer_tableau_vide(Partie *p, int taille) {
    int i;
    int j;

    // Enregistrement taille choisie dans structure Partie
    p->taille = taille;

    // Parcourt des lignes de la grille
    for (i = 0; i < p->taille; i++) {

        // Parcourt des colonnes de la grille
        for (j = 0; j < p->taille; j++) {

            p->grille[i][j].mine = 0;
            p->grille[i][j].visible = 0;
            // calculer_mines_autour() changera ce paramètre
            p->grille[i][j].nb_mines = 0;
            p->grille[i][j].bonus = 0;
            p->grille[i][j].malus = 0;
        }
    }
}

void placer_bombes(Partie *p) {
    int bombes_placees = 0;
    int ligne;
    int colonne;

    while (bombes_placees < p->nb_mines) {

        // Ligne au hasard entre 0 et taille - 1
        ligne = rand() % p->taille;

        // Colonne au hasard entre 0 et taille - 1
        colonne = rand() % p->taille;

        if (p->grille[ligne][colonne].mine == 0) {

            p->grille[ligne][colonne].mine = 1;
            bombes_placees++;
        }

        // Si la case a déjà une mine, la boucle recommence
    }
}

 /* Un bonus ou un malus ne peut pas être placé :
 * - sur une mine
 * - sur un autre bonus
 * - sur un autre malus
 */
void placer_bonus_malus(Partie *p) {
    int bonus_places;
    int malus_places;
    int bonus_reveal_place;
    int ligne;
    int colonne;

    // Calcul du nombre de bonus/malus suivant la taille de la grille
    p->nb_bonus = (int)(0.5 * p->taille);
    p->nb_malus = (int)(0.5 * p->taille);

    bonus_places = 0;
    malus_places = 0;
    bonus_reveal_place = 0;

    // Placement des bonus vies
    while (bonus_places < p->nb_bonus) {

        // Tirage aléatoire d'une case
        ligne = rand() % p->taille;
        colonne = rand() % p->taille;

        // Vérification case libre
        if (p->grille[ligne][colonne].mine == 0 &&
            p->grille[ligne][colonne].bonus == 0 &&
            p->grille[ligne][colonne].bonus_reveal == 0 &&
            p->grille[ligne][colonne].malus == 0) {

            p->grille[ligne][colonne].bonus = 1;
            bonus_places++;
        }
    }

    // Placement des malus
    while (malus_places < p->nb_malus) {

        ligne = rand() % p->taille;
        colonne = rand() % p->taille;

        // Vérification case libre
        if (p->grille[ligne][colonne].mine == 0 &&
            p->grille[ligne][colonne].bonus == 0 &&
            p->grille[ligne][colonne].bonus_reveal == 0 &&
            p->grille[ligne][colonne].malus == 0) {

            p->grille[ligne][colonne].malus = 1;
            malus_places++;
        }
    }

    // Placement du bonus reveal unique
    while (bonus_reveal_place == 0) {

        ligne = rand() % p->taille;
        colonne = rand() % p->taille;

        if (p->grille[ligne][colonne].mine == 0 &&
            p->grille[ligne][colonne].bonus == 0 &&
            p->grille[ligne][colonne].bonus_reveal == 0 &&
            p->grille[ligne][colonne].malus == 0) {

            p->grille[ligne][colonne].bonus_reveal = 1;
            bonus_reveal_place = 1;
        }
    }
}



 /* Pour chaque case, on regarde les 8 cases voisines :
 * - haut
 * - bas
 * - gauche
 * - droite
 * - les 4 diagonales
 */
void calculer_mines_autour(Partie *p) {
    int i;
    int j;
    int k;
    int l;
    int ligne_voisine;
    int colonne_voisine;
    int compteur;

    // Parcourt toutes les lignes
    for (i = 0; i < p->taille; i++) {

        // Parcourt toutes les colonnes
        for (j = 0; j < p->taille; j++) {

            // Compteur de mines autour de la case actuelle
            compteur = 0;

            // Si la case actuelle contient une mine, on l'initialise à -1 pour la reconnaitre
            if (p->grille[i][j].mine == 1) {
                p->grille[i][j].nb_mines = -1;
            }

            // Sinon, on compte les mines autour
            else {

                // k représente le décalage de ligne : -1, 0 ou 1
                for (k = -1; k <= 1; k++) {

                    // l représente le décalage de colonne : -1, 0 ou 1
                    for (l = -1; l <= 1; l++) {

                        // On évite de compter la case elle-même
                        if (!(l == 0 && k == 0)) {

                            // Coordonnées de la case voisine
                            ligne_voisine = i + l;
                            colonne_voisine = j + k;

                            // On vérifie que la case voisine est bien dans la grille
                            if (ligne_voisine >= 0 &&
                                ligne_voisine < p->taille &&
                                colonne_voisine >= 0 &&
                                colonne_voisine < p->taille) {

                                // Si la case voisine contient une mine, on augmente le compteur
                                if (p->grille[ligne_voisine][colonne_voisine].mine == 1) {
                                    compteur++;
                                }
                            }
                        }
                    }
                }

                // On enregistre le nombre de mines autour de la case
                p->grille[i][j].nb_mines = compteur;
            }
        }
    }
}



 /* Si une case est cachée, on affiche "-"
 * Si une case est visible :
 * - on affiche X si c'est une mine
 * - sinon on affiche le nombre de mines autour
 */
void afficher_grille(Partie *p) {
    int i;
    int j;

    printf("\n   ");

    // Affichage numéros de colonnes
    for (j = 0; j < p->taille; j++) {
        printf("%2d ", j);
    }

    printf("\n");

    // Parcours des lignes
    for (i = 0; i < p->taille; i++) {

        // Affichage du numéro de ligne
        printf("%2d ", i);

        // Parcours des colonnes
        for (j = 0; j < p->taille; j++) {

            // Si la case est cachée
            if (p->grille[i][j].visible == 0) {
                printf(" - ");
            }

            // Si la case est visible
            else {

                // Si la case contient une mine
                if (p->grille[i][j].mine == 1) {
                    printf(" X ");
                }

                // Sinon, on affiche le nombre de mines autour
                else {
                    printf(" %d ", p->grille[i][j].nb_mines);
                }
            }
        }

        printf("\n");
    }

    printf("\n");
}

/* - si les coordonnées sont valides
 * - si la case est déjà visible
 * - si la case contient une mine
 */
void reveler_case(Partie *p, int ligne, int colonne) {
    // Vérification : la ligne et la colonne doivent être dans la grille
    if (ligne < 0 || ligne >= p->taille ||
        colonne < 0 || colonne >= p->taille) {

        printf("Coordonnees invalides.\n");
        return;
        }

    // Si la case est déjà visible
    if (p->grille[ligne][colonne].visible == 1) {
        printf("Cette case est deja visible.\n");
        return;
    }

    // On rend la case visible
    p->grille[ligne][colonne].visible = 1;

    // Si la case contient une mine, la partie est perdue
    if (p->grille[ligne][colonne].mine == 1) {
        printf("Mine touchee !\n");

        // Perd une vie
        p->vies--;
    }
}