/**
* \file recouvrement.h
*
* 3 fonctions :
* - un type terrain
* -ter_recouvert (grille l): Liste des terrains recouverts sur le plateau
*
* -ter_recouvert_tuile(grille l, pile p) : Liste des terrains recouverts par une tuile si on essaie de la poser
   sur le plateau
* -test_recouvert : Test de la règle Une tuile ne peut être totalement recouverte à
aucun moment de la partie
*/

#ifndef RECOUVRET_H
#define RECOUVRET_H
#include "../lotA/structgrille.h"
#include "../lotA/structuile.h"
#include "../lotA/structure.h"

struct terrain_s
{
	int x;
	int y;
	char type;
};
typedef struct terrain_s* terrain;

/**
 *\brief le nombre de terrain recouvert
 *\param un grille
 *\return un entier qui est le nombre de terrain recouvert
 */
int nombre_recouvert(grille g);


/**
 *\brief Liste des terrains recouverts sur le plateau
 *\param une grille
 *\return un tableau de type terrain qui contient les coordonnées des terrains recouverts
 */
terrain* ter_recouvert(grille l,int n);

/**
 *\brief Liste des terrains recouverts par une tuile si on essaie de la poser
   sur le plateau
 *\param une grille et une tuile
 *\return un tableau de type terrain qui contient les coordonnées des terrains recouverts par une tuile
 */
terrain* ter_recouvert_tuile(grille l, tuile tuile_s, int x, int y);

int** list_pos(grille g,int k);

int tuile_of(grille g, int x, int y);

int test_fully_covered(grille g,int k);

/**
 *\brief vérifie que l'on respecte la limite de la zone
 *\param une grille, une tuile et sa position x et y
 *\return 0 si le test échoue
 */



int test_limite(grille g, tuile t, int x, int y);

/**
*\brief on vérifie pour une nouvelle tuile qu'au moins une de ses cases recouvre autre chose que '.'
*\param grille g, tuile t , position de la tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/


int recouvre_ancien(grille g, tuile t, int x, int y);

/**
*\brief on vérifie pour chaque tuile si elle est posée sur une case Lac
*\param la pile p des tuiles, la grille g
*\return 1 si la règle est respectée et 0 sinon
*/

int testlac(grille g, tuile t, int x, int y);

int plus_de_tuile(pile p);

int end_of_game(grille g, pile hand, tuile t);

/**
 *\brief on vérifie pour une nouvelle tuile qu'il peut bien inserer dans la grille
 *\param  grille g, tuile t et les position de cette tuile x et y ,a==1 affiche les messages
 *\return 1 si la règle est respectée et 0 sinon
 */
int add_to_grille(grille g, tuile t, int x, int y, int a);
/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Ressouce
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_R(grille g, tuile t, int x, int y);

/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Usine
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_U(grille g, tuile t, int x, int y);

/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Forest
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_F(grille g, tuile t, int x, int y);

/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Ville
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_V(grille g, tuile t, int x, int y);

#endif
