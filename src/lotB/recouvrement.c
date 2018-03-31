#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "recouvrement.h"

/**
 *\brief Liste des terrains recouverts sur le plateau
 *\param une grille et nombre de terrain recouvert 
 *\return un tableux de tpye terrain qui contient les coordonnée de terrain recouverts
 */
terrain ter_recouvert(grille l,int n)
{

    int i,j;
    int count=0;
    int size = l->size;
    terrain t = (terrain)malloc(sizeof(terrain)*n);
    for (i = 0; i < size; i++)
    {
    	for (j = 0; j < size ; j++)
    	{
    		if(l->matrix[i][j]!='.')
              {
           	    t[count].x=i;
              	t[count].y=j;
              	t[count].type=l->matrix[i][j];
              	count++;
              }
    	}
    }
    return t;
}


/**
 *\brief Liste des terrains recouverts par une tuile si on essaie de la poser
   sur le plateau
 *\param une grille et une tuile
 *\return un tableux de tpye terrain qui contient les coordonnée de terrain recouverts par une tuile
 */
terrain ter_recouvert_tuile(grille l, tuile tuile_s)
{
     int i,j;

     terrain t = (terrain)malloc(sizeof(terrain)*6);
     char ort = tuile_s->ort;
   
     int x,y,size,count=0;
     x=tuile_s->pos[0];
     y=tuile_s->pos[1];
     size=l->size;
     printf("%d %d %d %c\n",count,x,y,l->matrix[1][1]);
     if(ort == '^'){
     	count=0;
     	for ( i = 0; i < 3; ++i)
     	{
     		for (j = 0; j < 2; ++j)
     		{
               
     			t[count].x=x+i;
              	t[count].y=y+j;
                
              	t[count].type=l->matrix[x+i][y+j];

              	count++;

     		}
     	}
     }
     else if(ort == '<'){
     	count=0;
     	for ( i = 0; i < 2; ++i)
     	{
     		for (j = 0; j < 3; ++j)
     		{

     			t[count].x=x-i;
              	t[count].y=y+j;
              	t[count].type=l->matrix[x-i][y+j];

              	count++;
     		}
     	}

     }
     else if(ort == '>'){
     	count=0;
     	for ( i = 0; i < 2; ++i)
     	{
     		for (j = 0; j < 3; ++j)
     		{
     			t[count].x=x+i;
              	t[count].y=y-j;
              	t[count].type=l->matrix[x+i][y-j];
              	count++;
     		}
     	}
     }
     else {
     	count=0;
     	for ( i = 0; i < 3; ++i)
     	{
     		for (j = 0; j < 2; ++j)
     		{
     			t[count].x=x-i;
              	t[count].y=y-j;
              	t[count].type=l->matrix[x-i][y-j];
              	count++;
     		}
     	}
     }
     
    return t;


}

/**
 *\brief test si l'endroit qu'on poser pour une nouvelle tuile est totalement recouvert 
 *\param une grille et une nouvelle tuile qu'on veut poser 
 *\return 0 si il est pas totalement recouvert 1 sinon
 */
int test_recouvert(grille l,tuile new_t)
{

     int i = 0;
     terrain t = (terrain)malloc(sizeof(terrain)*6);
     t= ter_recouvert_tuile(l,new_t);
     
     int test=1;
     for (i = 0; i < 6; i++)
     {
     	if(t[i].type=='.')
     		test=0;
     }
     if(test == 1)
     	return 1;
     
     return 0;
}



