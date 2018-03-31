/**
* \file structgrille.h
*
* 1 type et 2 fonctions :
*
* -type \a grille : pointeur vers une structure qui contient la grille carrée et sa taille
* et une pile de tuile
*
* -create(n) : crée une grille de taille n
* -destroy(g) : libère l'espace mémoire de la grille g
*/


#ifndef GRILLE_H
#define GRILLE_H
#include "pile.h"


struct grille_s{
  char** matrix;
  int size;
  pile pile_tuile;
};
typedef struct grille_s* grille;

/**
 *\brief Alloue DYNAMIQUEMENT et INITIALISE UNE GRILLE
 *\param taille >= 5
 *\return une grille g de taille n
 */
grille create(int n);

/**
 *\brief le nombre de terrain recouvert
 *\param un grille
 *\return un entier qui est le nombre de terrain recouvert
 */
int nombre_recouvert(grille g);

/**
 *\brief LIBERE L ESPACE MEMOIRE DE LA GRILLE
 *\param la grille à libérer
 *\return void
 */
void destroy(grille g);
#include "structure.h"

#endif
