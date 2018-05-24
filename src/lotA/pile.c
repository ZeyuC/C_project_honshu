#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/**
 *\brief crée une pile vide p
 */
pile init()
{
  pile p;
  p.som = -1;
  return p;
}


/**
 *\brief ajoute la tuile new en haut de la pile p
 *\param pile p et tuile new
 */
void empile(pile *p, tuile new_t)
{
  p->t[p->som + 1] = new_t;
  p->som = p->som + 1;
}


/**
 *\brief retire la tuile au sommet de p
 *\param une pile p
 *\return la tuile retirée du sommet de p
 */
tuile depile(pile *p)
{
  tuile s;
  s = p->t[p->som];
  p->som = p->som - 1;
  return (s);
}

/**
 *\brief alloue dynamiquement et ALEATOIREMENT nb_tuiles TUILES
 *\param nb_tuile : nombre de tuile
 *\return un tableau de tuiles de taille nb_tuile
 */
pile initi_tuiles(int nb_tuile)
{
    int k;
    pile p_tuile;

    for ( k = 0; k < nb_tuile; k++)
    {
        p_tuile.t[k] = ini_tuile(-1,-1);
        p_tuile.t[k]->num = k;
    }
    p_tuile.som = k;
    return p_tuile;
}


/**
 *\brief alloue dynamiquement des TUILES A PARTIR D UN FICHIER
 *\param le fichier
 *\return tableau de TUILES REMPLIES
 */
pile initi_tuile_fichier(FILE *fp,int* nb_tuile)
{

    int num,i,j,k;
    char buf[100];
    fscanf(fp,"%d",nb_tuile);

    pile p_tuile;
    printf("nbtuile = %d\n",*nb_tuile);
    p_tuile.som = *nb_tuile;

    for(i=0;i<*nb_tuile;i++)
    {
      p_tuile.t[i] = ini_tuile();
        fscanf(fp,"%d",&num);
        p_tuile.t[i]->num=num;

        for(j=0;j<3;j++)
        {
            for (k = 0; k < 2; k++)
            {
        	     	 fscanf(fp,"%s",buf);
                 if(*buf=='U' || *buf=='V'|| *buf=='P'|| *buf=='L'|| *buf=='F'|| *buf=='R')
                 p_tuile.t[i]->point[j][k]=*buf;

                 else {
                  printf("Les types de terrains ne peuvent etre que U,V,P,L,F,R.Veuillez changer le fichier\n");
                  p_tuile.som = -1;
                 }
            }

        }
    }
    return p_tuile;
}
