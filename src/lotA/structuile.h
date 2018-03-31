/**
 * \file structuile.h
 * 
 * 1 type et 3 fonctions
 * 
 * - type \a tuile : pointeur vers une structure contenant 
 * \a point : un tableau de char 3x2 
 * \a pos : un couple d'int pour la position de la tuile
 * \a num : l'identifiant unique de la tuile
 * \a ort : orientation de la tuile
 * 
 * - ini_tuile(void) : génère une tuile aléatoirement
 * - initi_tuiles(nb_tuile) : génère nb_tuile aléatoirement
 * - initi_tuiles_fichier( FILE* fp) : génère les tuiles à partir d'un fichier
 */

#ifndef TUILES_H
#define TUILES_H

/**
 *\param point : cases de la tuile
 *\param pos   : position de la tuile
 *\param num   : identifiant de la tuile
 *\param ort   : orientation de la tuile
 */
struct tuile_s
{
    char point[3][2];
    int pos[2];
    int num;
    char ort;
};
typedef struct tuile_s* tuile;


/**
 *\brief CREE ET REMPLI ALEATOIREMENT UNE TUILE
 */
tuile ini_tuile();

/**
 *\brief CREE ET REMPLI UNE TUILE CONNAISSANT SES 6 TERRAINS
 * terrains : a,b,c,d,e,f
 */
tuile ini_tuile_sachant(const char a,const char b,const char c,const char d,const char e,const char f);
 




#endif
