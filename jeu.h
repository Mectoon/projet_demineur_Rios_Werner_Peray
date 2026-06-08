//
// Created by arios on 27/05/2026.
//

#ifndef PROJET_DEMINEUR_RIOS_WERNER_PERAY_JEU_H
#define PROJET_DEMINEUR_RIOS_WERNER_PERAY_JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 12
#define FICHIER_SAUVEGARDE "sauvegarde.csv"

/**
 * @struct Case
 * @brief Representation d'une case de la grille.
 */
typedef struct {
    int mine;          // 1 = bombe, 0 = pas de bombe
    int visible;       // 1 = case revelee, 0 = case cachee
    int nb_mines;      // nombre de mines autour de la case

    int bonus;         // 1 = bonus present, 0 = pas de bonus
    int malus;         // 1 = malus présent à cette case , 0 = pas de malus présent à cette case
} Case;

/**
 * @struct Partie
 * @brief Representation de l'ensemble d'une partie.
 */
typedef struct {
    Case grille[max][max];
    int tour;          // numéro actuel du tour
    int taille;        // taille de la grille : entre 6 et 12
    int difficulte;    // 1 = facile, 2 = moyen, 3 = difficile
    int mode;          // 1 = classique, 2 = bonus/malus

    int nb_mines;      // nombre total de mines
    int nb_bonus;      // nombre total de bonus
    int nb_malus;      // nombre total de malus
    int malus;         // malus activé ou non à ce tour, 1 = malus activé, 0 = pas de malus en cours
    int tour_malus;    // numéro du tour d'activation du dernier malus

    int vies;          // entre 0 et + infini
    int etat;          // 0 = en cours, 1 = gagne, 2 = perdu

    int score;         // score qui dépend du temps
    time_t temps;      // temps mis pour finir la partie

} Partie;

void afficherMenuDemineur(void);

void afficher_regles(void);
/*
Affiche les règles du démineur lorsque l'utilisateur choisit 4 dans le menu.
*/

void lancer_nouvelle_partie(Partie *p);
/*
Demande à l'utilisateur la taille, la difficulté et le mode de jeu.
Puis elle appelle les fonctions déjà faites :
- creer_tableau_vide
- calculer_nombre_mines
- placer_bombes
- placer_bonus_malus si mode bonus/malus
- calculer_mines_autour
- afficher_grille
*/

/**
 * @brief Demarre le chronometre et initialise p->temps a 0s.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void demarrer_chrono(Partie *p);


/**
 * @brief Calcul le score suivant le temps et l'enregistre dans p->score.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void calculer_score(Partie *p);


/**
 * @brief affiche le score suivant le temps mis en secondes ou en minutes.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void afficher_score(Partie *p);


/**
 * @brief Calcule le nombre de mines en fonction de la taille de la grille et de la difficulte.
 *
 * La fonction utilise la difficulte stockee dans la structure Partie :
 * 1 - facile : 20% des cases sont des mines.
 * 2 - moyen : 25% des cases sont des mines.
 * 3 - difficile : 30% des cases sont des mines.
 * Elle stocke ensuite le nombre de mines dans la structure partie.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void calculer_nombre_mines(Partie *p);


/**
 * @brief Initialise une grille vide selon la taille donnee.
 *
 * Toutes les cases sont initialisees sans mine, non visibles,
 * avec 0 mine autour, sans bonus et sans malus.
 *
 * @param p Pointeur vers la structure Partie.
 * @param taille Taille de la grille a creer.
 * @return Rien.
 */
void creer_tableau_vide(Partie *p, int taille);


/**
 * @brief Place aleatoirement les bombes dans la grille.
 *
 * La fonction place le nombre de bombes contenu dans p->nb_mines.
 * Si une bombe est deja presente sur une case tiree au hasard,
 * un nouveau tirage est effectue.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void placer_bombes(Partie *p);


/**
 * @brief Place aleatoirement les bonus et les malus dans la grille.
 *
 * La fonction place les bonus et les malus uniquement sur des cases libres.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void placer_bonus_malus(Partie *p);


/**
 * @brief Calcule le nombre de mines autour de chaque case.
 *
 * Pour chaque case de la grille, la fonction compte les mines presentes
 * dans les 8 cases voisines. Une case contenant une mine recoit la valeur -1.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void calculer_mines_autour(Partie *p);

/**
 * @brief Demande si le joueur veut echanger une vie contre le bonus reveal
 *
 * @param p Pointeur vers la structure Partie.
 * @return 1 si oui, 2 si non.
 */
int donner_sa_langue_au_chat(Partie *p);

/**
 * @brief affiche la grille suivant donner_sa_langue_au_chat
 *puis affiche de nouveau la grille normale au bout de 3 secondes.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void afficher_grille_reveal(Partie *p);


/**
 * @brief Affiche la grille de jeu.
 *
 * Les cases cachees sont affichees avec '-'.
 * Les cases visibles affichent soit une mine, soit le nombre de mines autour,
 * soit un bonus ou un malus selon leur contenu.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void afficher_grille(Partie *p);


/**
 * @brief Revele une case choisie par le joueur.
 *
 * La fonction verifie d'abord si les coordonnees sont valides.
 * Si la case contient une mine, on perd une vie.
 * Si la case ne contient pas de mine, elle devient visible.
 * Si la case revelee contient 0 mine autour, les cases voisines sont revelees automatiquement.
 *
 * @param p Pointeur vers la structure Partie.
 * @param ligne Ligne de la case a reveler.
 * @param colonne Colonne de la case a reveler.
 * @return Rien.
 */
void reveler_case(Partie *p, int ligne, int colonne);


/**
 * @brief Met à jour l'état du malus en fonction du nombre de tours restants avec le malus activé.
 *
 * La fonction calcule le nombre de tours pendant lesquels le malus doit encore être actif.
 * Si le malus est toujours en cours, la variable correspondante dans la structure Partie est activée.
 * À chaque appel, le compteur de tours restants pour le malus est décrémenté.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void gestion_malus(Partie *p);


/**
Verifie si la partie est gagnee.
La fonction parcourt toute la grille et regarde s'il reste
au moins une case sans mine qui n'a pas encore ete revelee.
- si toutes les cases sans mine sont revelees, elle retourne 1
- sinon, elle retourne 0
*/
int partie_gagnee(Partie *p);
/*
Vérifie si la partie est gagnée.
La fonction parcourt toute la grille et regarde s'il reste
au moins une case sans mine qui n'a pas encore été révélée.
- si toutes les cases sans mine sont révélées, 1
- sinon, 0
*/

void jouer_partie(Partie *p);
/*
Gere le deroulement complet d'une partie :
affichage de la grille, choix d'une action,
revelation d'une case, sauvegarde, victoire ou defaite.
*/

#endif //PROJET_DEMINEUR_RIOS_WERNER_PERAY_JEU_H