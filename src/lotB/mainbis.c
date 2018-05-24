#include <stdlib.h>
#include <stdio.h>
#include "../lotA/structgrille.h"




int add_to_grille(grille g, tuile t, int x, int y){
  int k,i;
  int somme = g->pile_tuile.som;
  if (!(test_limite(g, t, x, y))){    /*on vérifie que la tuile rentre dans la grille*/
    return 0;
  }
  if (!(testlac(g,t,x,y)) || !(recouvre_ancien(g,t,x,y))) {
    return 0
  }
  else{
    terrain* liste_ter = ter_recouvert_tuile(g,t);   /*on liste les terrains qu'occupera la nouvelle tuile si elle est posée*/
    empile(g->pile_tuile,t);
    for (i=0; i<6; i++){
      g->pile_tuile.som --;
      k = tuile_of(g,liste_ter[i]->x, liste_ter[i]->y);
      g->pile_tuile.som ++;
      if (!(test_fully_covered(g,k))) {
        return 0;
      }
    }
  }
  return 1;
}

int plus_de_tuile(pile p){
  int i;
  int count = 0;
  for (i = 0; i < p.som; i++){
    if (p.t[i]->pos[0] != -1){
      count ++;
    }
  }
  return count == p.som;
}


int end_of_game(grille g, pile hand, tuile t){
  int count = 0;
  if (plus_de_tuile(hand)){
    return 1;
  }
  else {
    for (i = 0; i < g->size; i++){
      for (j = 0; j < g->size; j++){
        t->ort = '^';
        if (add_to_grille(g,t,i,j){
          count++;
        }
        t->ort = '>';
        if (add_to_grille(g,t,i,j){
          count++;
        }
        t->ort = '<';
        if (add_to_grille(g,t,i,j){
          count++;
        }
        t->ort = 'v';
        if (add_to_grille(g,t,i,j){
          count++;
        }
      }
    }
    return count==0;
  }
}



int main(){
  int x,y,i,j;
  tuile tuile_test = ini_tuile();
  int findujeu = 0;
  int bonne_coord = 0;
  while (findujeu == 0){
    while (!bonne_coord){
      printf("Entrez les coordonnées pour placer la tuile dans la grille.\n x : ");
      scanf(" %d", &x);
      printf(" y : ");
      scanf(" %d", &y);
      bonne_coord = add_to_grille(g,t,x,y);
    }
    inser_tuile(g, t, x, y);
    findujeu = end_of_game(g, hand, tuile_test);
  }
  return 0;
}
