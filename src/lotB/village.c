#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "village.h"


/**
 *\brief calcule le cardinal de le village le plus grand
 *\param une grille g
 *\return un entier entier qui représente le cardinal de le village le plus grand dans grille g
 */
int trouver_village(grille g)
{

	int i,j,in=0,out=0;
	int max_count=0;
	int size = g->size;
   
    char ** m = (char**)malloc(sizeof(char*)*(size+2));
    for(i=0;i<size+2;i++)
    {
    	m[i]=(char*)malloc(sizeof(char)*(size+2));
    }

	for(i=0;i<size+2;i++)
    	for(j=0;j<size+2;j++)
    	{
    		 if(i==0||j==0||i==size+1||j==size+1)
    		 m[i][j]='0';
    		 else
    		 	m[i][j]=g->matrix[i-1][j-1];
    	}

    ville open_v = (ville)malloc(sizeof(ville)*size);

    for ( i = 1; i < size+1; ++i)
    {
    	for ( j = 1; j < size+1; ++j)
    	{
    		if(m[i][j]=='V')
    		{

    			in=0,out=0;
 				m[i][j]='0';
    			open_v[out].x=i;
    			open_v[out].y=j;
    			out++;

    			while(in != out)
    			{
	    			ville v=&open_v[in];
	    			in++;
	    			if(m[v->x-1][v->y]=='V')
	    			{
	    				m[v->x-1][v->y]='0';
	    				open_v[out].x=v->x-1;
	    				open_v[out].y=v->y;
	    				out++;
	    			}
	    			 if(m[v->x+1][v->y]=='V')
	    			{	
	    				m[v->x+1][v->y]='0';
	    				open_v[out].x=v->x+1;
	    				open_v[out].y=v->y;
	    				out++;
	    			}
	    			 if(m[v->x][v->y-1]=='V')
	    			{
	    				m[v->x][v->y-1]='0';
	    				open_v[out].x=v->x;
	    				open_v[out].y=v->y-1;
	    				out++;
	    			}
	    			 if(m[v->x][v->y+1]=='V')
	    			 {
	    				m[v->x][v->y+1]='0';
	    				open_v[out].x=v->x;
	    				open_v[out].y=v->y+1;
	    				out++;
	    			}
    		    }

    		}
    		if(out>max_count)
    		max_count = out;
    	}
    }
    for(i=0;i<size+2;i++)
    	free((void *)m[i]);
    free((void *)m);
    free(open_v);
    return max_count;
}

