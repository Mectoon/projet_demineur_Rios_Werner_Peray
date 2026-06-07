//
// Created by arios on 27/05/2026.
//

#ifndef PROJET_DEMINEUR_RIOS_WERNER_PERAY_SAUVEGARDE_H

#define PROJET_DEMINEUR_RIOS_WERNER_PERAY_SAUVEGARDE_H
#include "jeu.h"
/**
 * @brief Efface tout le contenu du fichier sauvegarde.csv
 * @return Rien.
 */
void SAUV_initialisation();
/**
 * @brief Charge la dernière partie sauvegardée en lisant directement les 5 dernières lignes du fichier.
 *
 * La fonction ouvre le fichier sauvegarde.csv et lit toutes ses lignes.
 * Seules les 5 dernières sont conservées, car elles correspondent à la dernière partie sauvegardée.
 * La première ligne contient les paramètres généraux de la partie.
 * Les quatre suivantes contiennent les coordonnées des mines,des cases visibles, malus et bonus.
 *
 * @param p Pointeur vers la structure Partie à remplir.
 * @return Rien.
 */
int SAUV_charger_partie(Partie *p);
/**
 * @brief Charge des coordonnées de la forme x-y dans la grille.
 *
 * La fonction reçoit une ligne contenant des couples x-y séparés par des virgules.
 * Chaque couple correspond à une case de la grille dont la valeur doit être activée.
 *
 * @param p Pointeur vers la structure Partie.
 * @param ligne Chaîne contenant les coordonnées à charger.
 * @param champ Chaîne indiquant le champ à modifier (mine, visible, bonus ou malus).
 * @return Rien.
 */
void SAUV_charger_coordonnees(Partie *p, const char *ligne, const char *champ);

/**
 * @brief Sauvegarde l'état complet d'une partie de démineur dans un fichier CSV.
 *
 * Cette fonction ouvre le fichier "sauvegarde.csv"
 * en mode ajout, puis écrit toutes les informations essentielles permettant
 * de restaurer ultérieurement la partie.
 *
 * Les données sauvegardées sont :
 *   - le mode de jeu (p->mode)
 *   - la difficulté (p->difficulte)
 *   - la taille de la grille (p->taille)
 *   - le nombre de vies restantes (p->vies)
 *   - le numéro du tour actuel (p->tour)
 *   - le tour d’activation du dernier malus (p->tour_malus)
 *   - le temps déjà écoulé (p->temps)
 *
 * Après ces informations générales, la fonction sauvegarde également
 * les coordonnées des éléments du jeu :
 *   - positions des mines
 *   - positions des cases visibles
 *   - positions des cases malus
 *   - positions des cases bonus
 *
 * Ces coordonnées sont écrites via la fonction SAUV_ecrire_coordonnees(),
 * sous la forme "x-y" séparées par des virgules.
 *
 * @param p Pointeur vers la structure Partie contenant l'état actuel du jeu.
 */
void SAUV_sauvegarde(Partie *p);
/**
 * @brief Sauvegarde dans le fichier CSV les coordonnées des cases possédant
 *        une propriété donnée (mine, visible, bonus ou malus).
 *
 * Parcourt toute la grille et écrit "i-j," pour chaque case où la propriété
 * indiquée par "champ" vaut 1. Termine toujours par un retour à la ligne.
 * "champ" est un "const char *" car la fonction ne modifie jamais
 * la chaîne : elle est utilisée uniquement pour "retrouver" le paramètre
 * de la structure grille à modifier.
 *
 * @param p     Partie contenant la grille.
 * @param f     Fichier CSV déjà ouvert en écriture.
 * @param champ Nom du champ où les coordonnées doivent être extraites
 * ("mine", "visible", "bonus", "malus").
 */
void SAUV_ecrire_coordonnees(Partie *p, FILE *f, const char *champ);
#endif //PROJET_DEMINEUR_RIOS_WERNER_PERAY_SAUVEGARDE_H

