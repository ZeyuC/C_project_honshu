#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "retrait.h"
/**
* \file recouvrement.c
*
* 1 fonctions :
* -
* -retrait (grille g): retire la tuile qu'on vient de poser
*
*/


/**
 *\brief  retire la tuile qu'on vient de poser
 *\param  un grille et le pile initial
 *\return
 */
void retrait(grille g,pile* pt)
{
    int n = g->pile_tuile.t[g->pile_tuile.som]->num;
    pt->t[n]->pos[0]=-1;
    pt->t[n]->pos[1]=-1;
	g->pile_tuile.som--;
	int num = g->pile_tuile.som;
	tuile* t = (tuile*)malloc(sizeof(tuile)*(num+1));
	int i,j;
	for(i=0;i<=num;i++)
	{
		t[i]=g->pile_tuile.t[i];
		g->pile_tuile.som--;
	}

	for(i=0;i<g->size;i++)
		for(j=0;j<g->size;j++)
			g->matrix[i][j]='.';

	for(i=0;i<=num;i++)
	{
		inser_tuile(g,t[i],t[i]->pos[0],t[i]->pos[1]);
	}
}
