#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "../lotB/recouvrement.h"
/**
 *\brief lis la COORDONNEE (x,y) DE LA GRILLE
 *\param 0 <=x <= g->size , 0<= y <= g->size , tableau char ** g NOT NULL
 *\return le char en coordonnées (x,y) de la grille g
*/
char lecture_grille(int x,int y,grille g)
{
    return g->matrix[x][y];
}



/**
 *\brief ORIENTE UNE TUILE t
 *\param tuile t, char "<", ">", "v" ou "^" donnant l'orientation de la tuile t
 *\return void
*/
void rot_tuile(tuile t, char ort){
  if(ort == '^' || ort == '<' || ort == 'v' || ort == '>'){
    t->ort = ort;
  }
}


/**
 *\brief INSERE LA TUILE t DANS LA GRILLE g
 *\ si la tuile n'entre pas entierement dans la grille, aucune action
 *\param grille g non null, t , x>=0 , y>= 0
 *\return 0 si on a bien inseré , 1 sinon. 
 c'est à dire la position qu'on veux poser est totalment recouvert 
 */
void inser_tuile(grille g,tuile t,int x,int y)
{
    int i,j;
    if( t->ort == '^'  && x+2 <= g->size && y+1 <= g->size)
    {
        for(i=0;i<3;i++)
            for (j = 0; j < 2; j++)
            {
                g->matrix[x+i][y+j]=t->point[i][j];
                empile(&g->pile_tuile, t);
                t->pos[0] = x;
                t->pos[1] = y;
            }
    }

    else if(t->ort == 'v' && x-2 >= 0 && y-1 >= 0)
    {
        for(i=0;i<3;i++)
            for (j = 0; j < 2; j++)
            {
                g->matrix[x-i][y-j]=t->point[i][j];
                empile(&g->pile_tuile, t);
                t->pos[0] = x;
                t->pos[1] = y;
            }
    }

    else if(t->ort == '<' && x-1 >= 0 && y+2 <= g->size)
    {
        for(i=0;i<2;i++)
            for (j = 0; j < 3; j++)
            {
                g->matrix[x-i][y+j]=t->point[j][i];
                empile(&g->pile_tuile, t);
                t->pos[0] = x;
                t->pos[1] = y;
            }
    }

    else if((x+1 <= g->size) && (y-2 >= 0))
    {
        for(i=0;i<2;i++)
            for (j = 0; j < 3; j++)
            {
                g->matrix[x+i][y-j]=t->point[j][i];
                empile(&g->pile_tuile, t);
                t->pos[0] = x;
                t->pos[1] = y;
            }
    }
}
