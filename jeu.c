
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "sauvegarde.h"

void afficher_menu_demineur(void) {
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

void afficher_regles(void){

    printf("\n");
    printf("*------------------------------*\n");
    printf("        REGLES DU JEU         \n");
    printf("*------------------------------*\n");
    printf("Le but du demineur est de reveler toutes les cases qui ne contiennent pas de mine.\n");
    printf("Si le joueur revele une mine, il perd une vie.\n");
    printf("Une case affiche un nombre qui indique combien de mines se trouvent autour d'elle\n");
    printf("\n");

    printf("MODE CLASSIQUE :\n");
    printf("- 1 seule vie\n");
    printf("- aucun bonus / malus\n");
    printf("\n");

    printf("MODE BONUS / MALUS :\n");
    printf("- 1 vie au depart\n");
    printf("- bonus : +1 vie\n");
    printf("- bonus revelation : affiche les positions des mines si le joueur a 2 vies\n");
    printf("- malus : cache la grille pendant 2 tours\n\n");
    printf("\n");

    printf("La partie est gagnee quand toutes les cases sans mine sont revelees.\n");
    printf("La partie est perdue quand le joueur n'a plus de vie.\n");
    printf("\n");

    printf("Bon jeu à vous !\n");
    printf("*------------------------------*\n");
}

void lancer_nouvelle_partie(Partie *p) {
    int taille;
    int difficulte;
    int mode;

    printf("\n");
    printf("*------------------------------*\n");
    printf("       NOUVELLE PARTIE !       \n");
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
        p->vies = 1;
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
    p->score = 0;
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
    int ligne;
    int colonne;

    // Calcul du nombre de bonus/malus suivant la taille de la grille
    p->nb_bonus = (int)(0.5 * p->taille);
    p->nb_malus = (int)(0.5 * p->taille);

    bonus_places = 0;
    malus_places = 0;

    // Placement des bonus vies
    while (bonus_places < p->nb_bonus) {

        // Tirage aléatoire d'une case
        ligne = rand() % p->taille;
        colonne = rand() % p->taille;

        // Vérification case libre
        if (p->grille[ligne][colonne].mine == 0 &&
            p->grille[ligne][colonne].bonus == 0 &&
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
            p->grille[ligne][colonne].malus == 0) {

            p->grille[ligne][colonne].malus = 1;
            malus_places++;
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

int donner_sa_langue_au_chat(Partie *p){

    int reponse = 0;

    // Le bonus reveal est proposé uniquement en mode Bonus/Malus
    // et seulement lorsque le joueur possède exactement 2 vies.
    if (p->mode == 2 && p->vies == 2)
    {
        while (reponse != 1 && reponse != 2) {
            printf("Vous avez 2 vies.\n");
            printf("Voulez-vous echanger 1 vie contre la vision de la grille ?\n");
            printf("1) Oui\n");
            printf("2) Non\n");
            printf("Votre choix : ");
            scanf("%d", &reponse);
        }

        // Si le joueur accepte, il perd une vie
        // et la fonction indique qu'il faut afficher la grille reveal.
        if (reponse == 1)
        {
            p->vies--;
            return 1;
        }
    }

    // Aucun reveal demandé
    return 0;
}

void afficher_grille_reveal(Partie *p)
{
    int i;
    int j;

    printf("\n--- BONUS REVEAL ---\n");

    // Affichage des numéros de colonnes
    printf("\n   ");
    for (j = 0; j < p->taille; j++) {
        printf("%2d ", j);
    }

    printf("\n");

    // Affichage de la grille
    for (i = 0; i < p->taille; i++) {

        // Affichage du numéro de ligne
        printf("%2d ", i);

        for (j = 0; j < p->taille; j++) {

            // Si la case contient une mine, on affiche X
            if (p->grille[i][j].mine == 1) {
                printf(" X ");
            }

            // Sinon, on affiche une case cachée
            else {
                printf(" - ");
            }
        }

        printf("\n");
    }

    printf("\nLa grille normale va se reafficher dans 3 secondes...\n");

    //attente des 3 secondes (aide de l'ia)
#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif

    afficher_grille(p);
}
 /* Si une case est cachée, on affiche "-"
 * Si une case est visible :
 * - on affiche X si c'est une mine
 * - sinon on affiche le nombre de mines autour
 */
void afficher_grille(Partie *p)
{
    int i;
    int j;

    // Affichage des numéros de colonnes
    printf("\n   ");
    for (j = 0; j < p->taille; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Affichage de chaque case de la grille
    for (i = 0; i < p->taille; i++) {
        printf("%2d ", i);

        for (j = 0; j < p->taille; j++) {

            // Si un malus est actif, toute la grille est cachée
            if (p->malus == 1) {
                printf(" ? ");
            }

            // Case non révélée
            else if (p->grille[i][j].visible == 0) {
                printf(" - ");
            }

            // Case révélée
            else {
                if (p->grille[i][j].mine == 1) {
                    printf(" X ");
                }
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
    int i;
    int j;

    // Vérification : la ligne et la colonne doivent être dans la grille
    if (ligne < 0 || ligne >= p->taille ||
        colonne < 0 || colonne >= p->taille) {
        printf("Coordonnees invalides.\n");
        return;
        }

    // Si la case est déjà visible, on ne peut pas la rejouer
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

    // Si la case contient un malus, il s'active pendant 2 tours
    if (p->grille[ligne][colonne].malus == 1) {
        printf("Un malus a ete active !\n");
        printf("La grille sera cachee pendant 2 tours.\n");

        // Le malus devient actif
        p->malus = 1;

        // On enregistre jusqu'à quel tour le malus reste actif
        p->tour_malus = p->tour + 2;
    }

    // Si la case contient un bonus, le joueur gagne une vie
    if (p->grille[ligne][colonne].bonus == 1) {
        printf("Genial ! Vous avez gagne une vie.\n");
        p->vies++;
    }

        printf("\n");
}

void gestion_malus(Partie *p){
    if (p->malus == 1 && p->tour > p->tour_malus) {
        p->malus = 0;
    }
}

int partie_gagnee(Partie *p) {
    int i;
    int j;

    // Parcours toutes les lignes de la grille
    for (i = 0; i < p->taille; i++) {

        // Parcours toutes les colonnes de la grille
        for (j = 0; j < p->taille; j++) {

            // Si case ne contient pas de mine et n'est pas encore visible,alors partie n'est pas encore gagnée
            if (p->grille[i][j].mine == 0 && p->grille[i][j].visible == 0) {
                return 0;
            }
        }
    }

    // Si toutes les cases sans mine sont révélées, la partie est gagnée
    return 1;
}


void jouer_partie(Partie *p) {
    int action;
    int ligne;
    int colonne;

    while (p->vies > 0 && p->etat == 0) {

        gestion_malus(p);

        if (donner_sa_langue_au_chat(p) == 1)
        {
            afficher_grille_reveal(p);
        }
        else
        {
            afficher_grille(p);
        }

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

                reveler_case(p, ligne, colonne);

                if (p->vies <= 0) {
                    p->etat = 2;
                    printf("\nVous avez perdu la partie.\n");
                    return;
                }

                if (partie_gagnee(p) == 1) {
                    p->etat = 1;
                    printf("\nBravo ! Vous avez gagne la partie.\n");
                    calculer_score(p);
                    afficher_score(p);
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