/**
* \file Honshu_Opt.h
*
* 3 fonctions :
* -affiche_score (grille l): Affichage du score atteint par la grille actuelle
*
* -rappel_moyens() : Rappel des moyens de gagner des points affiché lors de l’exécution d’une commande
*
* -Honshu_Opt(grille g,) : Affichage de la solution trouvée (grille et points) par votre solveur lors de
l’exécution d’une commande
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Honshu_Opt.h"
/**
 *\brief calcule le nombre de Forest
 *\param un grille
 *\return un entier qui est le nombre de Forest
 */
int num_forest(grille g)
{
    int i,j;
    int count=0;
    for ( i = 0; i < g->size; ++i)
    {
    	for (j = 0; j < g->size; ++j)
    	{
    		if(g->matrix[i][j]=='F')
    			count++;
    	}
    }
    return count;
}


void copy(tuile tu, pile p, int a){
  int i,j;
  for (i=0; i<3; i++){
    for (j=0; j<2; j++){
      p.t[a]->point[i][j] = tu->point[i][j];
    }
  }
  p.t[a]->pos[0] = tu->pos[0];
  p.t[a]->pos[1] = tu->pos[1];
  p.t[a]->ort = tu->ort;
}


/**
 *\brief calcule le nombre de Lac
 *\param un grille
 *\return un entier qui est le nombre de Lac
 */
int num_Lac(grille g)
{
	int i,j;
    int count=0;
    for ( i = 0; i < g->size; ++i)
    {
    	for (j = 0; j < g->size; ++j)
    	{
    		if(g->matrix[i][j]=='L')
    			count++;
    	}
    }
    return count;
}

/**
 *\brief calcule le min nombre entre Resource et Usine
 *\param un grille
 *\return un entier qui est le min entre R et U
 */
int num_R_and_U(grille g)
{
	 int i,j;
    int count_R=0,count_U=0;
    for ( i = 0; i < g->size; ++i)
    {
    	for (j = 0; j < g->size; ++j)
    	{
    		if(g->matrix[i][j]=='R')
    			count_R++;
    		if(g->matrix[i][j]=='U')
    			count_U++;
    	}
    }
    if(count_U < count_R)
    	return count_U;
    else
    	return count_R;
}

/**
 *\brief Affichage du score atteint par la grille actuelle
 *\param un grille
 *\return un entier qui est le score atteint par la grille actuelle
 */
int score(grille g)
{
    int score;
    int num_v = trouver_village(g);
    int num_F = num_forest(g);
    int num_L = num_Lac(g);
    int num_r_u = num_R_and_U(g);
    if(num_L-1>=0)
    score = num_v + num_F*2 + (num_L-1)*3 + num_r_u * 4;
    else
    score = num_v + num_F*2 + num_r_u * 4;
    return score;
}

/**
 *\brief Rappel des moyens de gagner des points affiché lors de l’exécution d’une commande
 *\param
 *\return
 */
void rappel_moyens()
{
	printf("-------------------------------------\n");
	printf("Vous marquez:\n * 2 points pour chaque foret.\n * 3x(nb de lacs -1) points.\n * 4 points pour chaque ressource allouee à une usine.\n * nb de villes contigues du plus grand village points.\n");
    printf("Attention : \n Une Usine ne peut traiter qu ’une Ressource\n   et une Ressource ne peut etre allouee qu'à une Usine.\n\n");
    printf("-------------------------------------\n");
}


/**
 *\brief  Affichage de la solution trouvée (grille et points) par votre solveur lors de l’exécution d’une commande
 *\param un grille un pile
 *\return une grille avec la solution opt
 */
int Honshu_Opt(grille g, pile p)
{
	int i,j,x,y;
    int n_main=0;
    for (i = 0; i < p.som; i++)
      if(p.t[i]->pos[0]==-1)
       n_main++;

    int s=score(g);
    if(n_main == 0)
        return s;

    tuile t_main[n_main];
    n_main=0;
    for (i = 0; i < p.som; i++)
      if(p.t[i]->pos[0]==-1)
        {
          t_main[n_main]=p.t[i];
          n_main++;
        }
    int best=-1;
    tuile t;
    char ort[4]={'^','v','<','>'};
    for(i=0;i<n_main;i++)
    {
    	t=t_main[i];
    	for(j=0;j<4;j++)
    	{
    		t->ort=ort[j];
    		for(x=0;x< g->size;x++)
    		{
                for(y=0;y < g->size;y++)
    			{
    				if(add_to_grille(g,t,x,y,0))
    				{
    					inser_tuile(g,t,x,y);
    					p.t[t->num]->pos[0]=x;
    					p.t[t->num]->pos[1]=y;
                        p.t[t->num]->ort=t->ort;
                        int Tpm_scroe = Honshu_Opt(g,p);
    					if(Tpm_scroe>best){
                best = Tpm_scroe;
              }
              retrait(g,&p);
    				}
    			}
            }
        }
    }
    return best;
}



/**
 *\brief  Affichage de la solution trouvée (grille et points) par votre solveur lors de l’exécution d’une commande
 *\param un grille un pile
 *\return une grille avec la solution opt
 */
int solveur(grille g, pile pt, pile res)
{
    srand(time(NULL));
    int i,j,x,y;
    int n_main=0;
    pile p = pt;
    tuile t_main[p.som];
    for (i = 0; i < p.som; i++)
      if(p.t[i]->pos[0]==-1)
        {
          t_main[n_main]=p.t[i];
          n_main++;
        }
    int s=score(g);
    if(n_main == 0)
        {
            return s;
        }

    int best=-1,condition=0,Tpm_scroe;
    tuile t;
    char ort[4]={'^','v','<','>'};

    for(i=0;i<n_main;i++)
    {
        t=t_main[i];
        for ( j = 0; j < 4; ++j)
        {
            t->ort=ort[j];
            for(x=0;x< g->size;x++)
            {
                for(y=0;y < g->size;y++)
                {
                   /*maximiser le nombre de R et U */
                   if(add_to_grille(g,t,x,y,0)&&(test_recouvert_V(g,t,x,y)||test_recouvert_F(g,t,x,y))
                        &&test_recouvert_R(g,t,x,y)&&test_recouvert_U(g,t,x,y))
                    {
                        condition=1;
                        inser_tuile(g,t,x,y);
                        p.t[t->num]->pos[0]=x;
    					          p.t[t->num]->pos[1]=y;
                        p.t[t->num]->ort=t->ort;
                        Tpm_scroe = solveur(g,p,res);
                        if(Tpm_scroe>best){
                          best = Tpm_scroe;
                         
                        }
                    }
                }
            }
        }
    }

    /*si la condition est très stricte,on insere permier tuile de t_main*/
    if(condition==0)
    {
       t=t_main[0];
       t->ort='v';
       for(x=0;x< g->size;x++)
            {
                for(y=0;y < g->size;y++)
                {
                    if(add_to_grille(g,t,x,y,0))
                    {
                        inser_tuile(g,t,x,y);
                        p.t[t->num]->pos[0]=x;
    					          p.t[t->num]->pos[1]=y;
                        p.t[t->num]->ort=t->ort;
                        Tpm_scroe = solveur(g,p,res);
                        if(Tpm_scroe>best){
                          best = Tpm_scroe;
                         
                        }
                    }
                }
            }
     }
    return best;
}
/*
struct coordinate
{
    int x;
    int y;
    char tpye;
};*/
/*
struct coordinate coord(grille g)
{
    int z = (int)((rand() / (RAND_MAX + 1.0))*4);

    int i,j,c_len=0;
    struct coordinate c_array[g->size*g->size];
    for(i=0;i<g->size;i++)
        for(j=0;j<g->size;j++)
        {
            if(g->matrix[i][j]!='.')
               {
                c_array[c_len].x=i;
                c_array[c_len].y=j;
               }
        }
    int r = (int)((rand() / (RAND_MAX + 1.0))*c_len);
    struct coordinate c;
    c.x=c_array[r].x;
    c.y=c_array[r].y;
    if(z==0)
        c.ort='^';
    else if(z==1)
        c.ort='v';
    else if(z==2)
        c.ort='<';
    else
        c.ort='>';
    return c;
}

tuile Next_t_main(grille g,pile p)
{
     int i;
     int n_main=0;
     double t = T;
     for (i = 0; i < p.som; i++)
       if(p.t[i]->pos[0]==-1)
          n_main++;
     tuile t_main=(tuile)malloc(sizeof(struct tuile_s)*n_main);
     n_main=0;
     for (i = 0; i < p.som; i++)
      if(p.t[i]->pos[0]==-1)
        {
          t_main[n_main]=*p.t[i];
          n_main++;
        }
      printf("n_main %d\n",n_main);
     int x = (int)((rand() / (RAND_MAX + 1.0))*n_main);
     int y = (int)((rand() / (RAND_MAX + 1.0))*n_main);
     printf("ccc %d %d\n",x,y);
     if(x == y)
       {
        printf("x==y\n");
        return t_main;
        }
     else
     {
        tuile temp=&t_main[x];
        t_main[x]=t_main[y];
        t_main[y]=*temp;
        printf("huan \n");
     }

     for(i=0;i<n_main;i++)
     {
        struct coordinate c = coord(g);
        t_main[i].pos[0]=c.x;
        t_main[i].pos[1]=c.y;
        t_main[i].ort=c.ort;
          printf("aaaa\n");

         while (add_to_grille(g,&t_main[i],c.x,c.y,0)==0)
           {
            c = coord(g);
            t_main[i].pos[0]=c.x;
            t_main[i].pos[1]=c.y;
            t_main[i].ort=c.ort;
           }
         t_main[i].pos[0]=c.x;
         t_main[i].pos[1]=c.y;
         inser_tuile(g,&t_main[i],c.x,c.y);
     }

     for(i=0;i<n_main;i++)
          retrait(g,p);

     printf("huan_1\n");
     return t_main;
}




int scroe_tuile(grille g,tuile tuile,int n_main)
{
    int i=0;
    struct grille_s g_n;
    g_n=*g;
    struct tuile_s t;
    t = *tuile;
    printf("avant scroe_g %d score_g_n %d \n",score(g),score(&g_n));
    for(i=0;i<n_main;i++)
    {
        inser_tuile(g,&tuile[i],tuile[i].pos[0],tuile[i].pos[1]);
    }
    printf("scroe_g %d score_g_n %d \n",score(g),score(&g_n));
    int score_ = score(g);
    g = &g_n;
    tuile = &t;
    return score_;
}

tuile solveur(grille g, pile p)
{



    int i,n_main=0,size=g->size;
    double t = T;
    for (i = 0; i < p.som; i++)
      if(p.t[i]->pos[0]==-1)
       n_main++;

    tuile t_main=(tuile)malloc(sizeof(struct tuile_s)*n_main);

    n_main=0;
    for (i = 0; i < p.som; i++)
      if(p.t[i]->pos[0]==-1)
        {
          t_main[n_main]=*p.t[i];
          n_main++;
        }
   struct coordinate Coor_P[size*size];
   struct coordinate Coor_V[size*size];
   struct coordinate Coor_F[size*size];
   struct coordinate Coor_U[size*size];
   struct coordinate Coor_R[size*size];
   int num_F=0,num_P=0,num_V=0,num_U=0,num_R=0;
   for (i = 0; i < size; ++i)
   {
       for (int j = 0; j < size; ++j)
       {
           if(g->matrix[i][j]=='P')
            {
                Coor_P[num_P].x=i;
                Coor_P[num_P].y=j;
                Coor_P[num_P].tpye='P';
                num_P++;
            }
           else if (g->matrix[i][j]=='V')
            {
                Coor_P[num_P].x=i;
                Coor_P[num_P].y=j;
                Coor_P[num_P].tpye='V';
                num_V++;
            }
           else if (g->matrix[i][j]=='F')
            {
                Coor_P[num_P].x=i;
                Coor_P[num_P].y=j;
                Coor_P[num_P].tpye='F';
                num_F++;
            }
           else if (g->matrix[i][j]=='R')
            {
                Coor_P[num_P].x=i;
                Coor_P[num_P].y=j;
                Coor_P[num_P].tpye='R';
                num_R++;
            }
           else if (g->matrix[i][j]=='U')
           {
                Coor_P[num_P].x=i;
                Coor_P[num_P].y=j;
                Coor_P[num_P].tpye='U';
                num_U++;
           }
           else continue;
       }
   }
   for(i=0;i<)
   return t_main;
}

char best_ort(grille g,tuile t,int x,int y,pile p)
{
     int i,j,k;
     int cur_point=0,new_point=0;
     for(i = 0; i< g->size;i++)
        for(j = 0; j< g->size;j++)
            if(g->matrix[i][j]!='.')
                cur_point++;


     int best_ort[4];
     char ort[4]={'^','v','<','>'};
     for(i = 0;i<4;i++)
     {
        t->ort=ort[i];

        inser_tuile(g,t,x,y);
        new_point=0;
        for(k = 0; k< g->size;k++)
        for(j = 0; j< g->size;j++)
            if(g->matrix[k][j]!='.')
                new_point++;
        best_ort[i]=new_point;
        retrait(g,p);
     }
     int indice=0;
     for(i=0;i<4;i++)
     {
        if(best_ort[indice]>best_ort[i])
            indice=i;
     }
     return ort[indice];
}

struct coordinate coord(grille g,tuile t,pile p)
{
    int i,j;


    struct coordinate coor;
    coor.x=0;
    coor.y=0;
    coor.ort='^';
    for(i = 0; i< g->size;i++)
        for(j = 0; j< g->size;j++)
            if(add_to_grille(g,t,i,j,0)==1)
                {
                    coor.x=i;
                    coor.y=j;
                    coor.ort = best_ort(g,t,i,j,p);
                    return coor;
                }
    return coor;
}
*/
