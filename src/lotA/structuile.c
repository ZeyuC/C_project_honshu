#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structuile.h"


/**
 *\brief CREE ET REMPLI ALEATOIREMENT UNE TUILE
 */
tuile ini_tuile(int x,int y){
  int i,j,a;
  char context[6]={'F','L','P','R','U','V'};
  tuile t = (tuile)malloc(sizeof(tuile));
  for (i = 0; i < 3; i++){
    for(j = 0; j < 2; j++){
      a = rand()%6;
      t->point[i][j] = context[a];
    }
  }
  t->ort = '^';
  t->pos[0] = x;
  t->pos[1] = y;
  t->num    = -1;
  return t;
}


/**
 *\brief CREE ET REMPLI UNE TUILE CONNAISSANT SES 6 TERRAINS
 * terrains : a,b,c,d,e,f
 */
tuile ini_tuile_sachant(const char a,const char b,const char c,const char d,const char e,const char f){
  tuile t = (tuile)malloc(sizeof(tuile));
  t->point[0][0] = a ;
  t->point[0][1] = b ;
  t->point[1][0] = c ;
  t->point[1][1] = d ;
  t->point[2][0] = e ;
  t->point[2][1] = f ;

  t->ort = '^';
  t->pos[0] = -1;
  t->pos[1] = -1;
  t->num    = -1;
  return t;
}


