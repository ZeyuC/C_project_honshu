/**
* \file Honshu_Opt.h
*- un type terrain
* 3 fonctions :
* -int score (grille g): Affichage du score atteint par la grille actuelle
*
* -void rappel_moyens() : Rappel des moyens de gagner des points affiché lors de l’exécution d’une commande
*
* -Honshu_Opt(grille g,) : Affichage de la solution trouvée (grille et points) par votre solveur lors de
l’exécution d’une commande
*/
#include "../lotA/structgrille.h"
#include "../lotA/structuile.h"
#include "../lotA/structure.h"
#include "../lotB/village.h"
#include "../lotB/recouvrement.h"
#include "../lotC/retrait.h"
#include "retrait.h"
#ifndef HONSHU_OPT_H
#define HONSHU_OPT_H

/**
 *\brief Affichage du score atteint par la grille actuelle
 *\param un grille
 *\return un entier qui est le score atteint par la grille actuelle
 */
int score(grille g);

/**
 *\brief Rappel des moyens de gagner des points affiché lors de l’exécution d’une commande
 *\param
 *\return
 */
void rappel_moyens();

/**
 *\brief  Affichage de la solution trouvée (grille et points) par votre solveur lors de l’exécution d’une commande
 *\param un grille une tableau tuile P une tableau tuile M
 *\return une grille avec la solution opt
 */
int Honshu_Opt(grille g,pile p);


/**
 *\brief  Affichage de la solution trouvée (grille et points) par votre solveur lors de l’exécution d’une commande
 *\param un grille un pile
 *\return une grille avec la solution opt
 */
int solveur(grille g, pile p, pile res);

#endif
