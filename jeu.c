
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
    printf("4) Regles du Jeu\n");
    printf("*------------------------------*\n");
    printf("Par Axel, Jules et Theodore\n");
}

void afficher_regles(void)
{
    printf("\n");
    printf("*------------------------------*\n");
    printf("*        REGLES DU JEU         *\n");
    printf("*------------------------------*\n");
    printf("Le but du demineur est de reveler toutes les cases qui ne contiennent pas de mine.\n");
    printf("Si le joueur revele une mine, il perd une vie.\n");
    printf("Les nombres affiches indiquent le nombre de mines autour de la case.\n");
    printf("La partie est gagnee quand toutes les cases sans mine sont revelees.\n");
    printf("La partie est perdue quand le joueur n'a plus de vie.\n");
    printf("\n");
    printf("Mode classique : le joueur joue avec une seule vie.\n");
    printf("Mode bonus/malus : des bonus et des malus peuvent apparaitre dans la grille.\n");
    printf("Bon jeu à vous !\n");
    printf("*------------------------------*\n");
}

void lancer_nouvelle_partie(Partie *p) {
    int taille;
    int difficulte;
    int mode;

    printf("\n");
    printf("*------------------------------*\n");
    printf("*       NOUVELLE PARTIE !       *\n");
    printf("*------------------------------*\n");

    do
    {
        printf("Choisissez la taille de la grille entre 6 et 12 : ");
        scanf("%d", &taille);
    } while (taille < 6 || taille > 12);

    do
    {
        printf("\nVeuillez saisir la difficulte :\n");
        printf("1) Facile\n");
        printf("2) Moyen\n");
        printf("3) Difficile\n");
        printf("Votre choix : ");
        scanf("%d", &difficulte);
    } while (difficulte < 1 || difficulte > 3);

    do
    {
        printf("\nVeuillez choisir le mode de jeu :\n");
        printf("1) Classique\n");
        printf("2) Bonus / Malus\n");
        printf("Votre choix : ");
        scanf("%d", &mode);
    } while (mode < 1 || mode > 2);

    p->difficulte = difficulte;
    p->mode = mode;
    p->etat = 0;
    p->tour=0;
    p->malus=0;
    if (mode == 1)
    {
        p->vies = 1;
    }
    else
    {
        p->vies = 3;
    }

    creer_tableau_vide(p, taille);
    calculer_nombre_mines(p);
    placer_bombes(p);

    if (p->mode == 2)
    {
        placer_bonus_malus(p);
    }

    calculer_mines_autour(p);

    printf("\nLa partie a bien ete creee.\n");
    printf("Taille : %d x %d\n", p->taille, p->taille);
    printf("Nombre de mines : %d\n", p->nb_mines);
    printf("Nombre de vies : %d\n", p->vies);
    demarrer_chrono(p);
    afficher_score(p);

    afficher_grille(p);
    /*
    La suite sera gerée plus tard dans la boucle de jeu :
    - demander une ligne et une colonne
    - réveler une case
    - vérifier gagné ou perdu
    - sauvegarder
    */
}

void demarrer_chrono(Partie *p) {
    p->temps = time(NULL);
}

void calculer_score(Partie *p) {
    time_t temps_fin;
    int duree;

    temps_fin = time(NULL);

    duree = (int)(temps_fin - p->temps); // score défini par le temps mis

    p->score = duree;
}

void afficher_score(Partie *p) {
    int minutes;
    int secondes;

    minutes = p->score / 60;
    secondes = p->score % 60;

    printf("Temps final : %d min %d s\n", minutes, secondes);
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

void placer_bombes(Partie *p){
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

                //Si il y a un malus en cours
                if (p->malus==1) printf(" ? ");
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

    // Si la case contient une mine, le joueur perd une vie
    if (p->grille[ligne][colonne].mine == 1) {
        printf("Mine touchee !\n");
        p->vies--;
    }
    // Si la case contient un malus, il s'active et le numéro du tour d'activation du malus est enregistré
    if (p->grille[ligne][colonne].malus == 1)
    {
        printf("Un Malus a ete active !\nLe plateau est caché pour 2 tours !! \n");
        p->tour=p->tour_malus;
    }
    if (p->grille[ligne][colonne].bonus == 1)
    {
        printf("Genial! Vous avez gagne une vie grace a un bonus !\n");
        p->vies++;
    }
}
void gestion_malus(Partie *p){
    int tour_malus_restant=0;
    tour_malus_restant = p->tour-p->tour_malus; //Calcul du nombre restant de tours avec le malus
    if (tour_malus_restant>0)
    {
        p->malus=1; //Effet de malus activé
    }

    p->tour_malus--;    // Décrémentation du compteur de tours avec le malus activé
}
