int coord_village[size][2] = {
	for (i=0; i<=size; i++){
		printf("{0,0},");
	}
	printf("{0,0}");
}

/**
 *\brief liste les coordonnées des villages de la grille
 *\param la grille g
 *\return le vecteur coord_village modifié
*/


void trouver_village(grille g)
{
	k = 0
	for (i=0; i<size; i++){
		for (j=0; j<size; j++){
			if (g[i][j] == 'V'){
				coord_village[k][0] = i;
				coord_village[k][1] = j;
				k++;
			}
		}
	}

}
	
	


int vec[size*size][2] = {
	for (i=0; i<=size; i++){
		printf("{-1,-1},");
	}
	printf("{-1,-1}");
}

/**
 *\brief vérifie la présence d'un village à la case (x,y)
 *\param les cordonnées x et y, la grille g
 *\return 1 si il y a présence
*/


int presence(int x, int y, vecteur v)
 {
	k=0;
	s = size(v);
	for (i=0, i<s, i++){
	    if (v[i][0] = x and v[i][1]= y ){
	    k = k + 1;
	    }
	if (k = 1){
	   return 1;
	}
	else{
	   return 0;
	}
	    

}

/**
 *\brief retourne la ville associée au village en (x,y), si ville il y a
 *\param les cordonnées x et y, la grille g
 *\return le vecteur vec avec les coordonées des villages de la ville du village (x,y)
*/


void trouver_ville(int x, int y, grille g)
{
	y = 0;
	k = 0;
	s = 1;
	l = x;
	c = y;
	for (i=0; i<size; i++){
	    if (coord_village[i][0] == l && coord_village[i][1] == c){
	       y = y + 1;
	   }
	       
	if (y = 0){
	   printf(" ");
	}
	vec[0][0]=x;
	vec[0][1]=y;
	
	while (vec[s][0] != -1) {

	    if (l == 0){

	       if (c == 0){

				if (g[0][1]=='V'){
					
					if (presence(0,1,vec)==0){
					vec[s][0] = 0;
					vec[s][1] = 1;
					s++;
					}
				} 

		        else if (g[1][0]=='V'){

					if (presence(1,0,vec)==0){
					vec[s][0] = 1;
					vec[s][1] = 0;
					s++;
					}

				}	

			}
	       
			else{
	       
				if (c = (size-1)){

					if (g[0][size-2]=='V'){
					
						if (presence(0,(size - 2),vec)==){
						vec[s][0] = 0;
						vec[s][1] = (size-2);
						s++;
						}
					}

					else if (g[1][size-1]=='V'){
						
						if (presence(1,(size-1),vec)==0){
						vec[s][0] = 1;
						vec[s][1] = (size-1);
						s++;
						}
					}

				}

				else{

					if (g[l][c-1]){
						
						if (presence(1,(c-1),vec)==0){
						vec[s][0] = l;
						vec[s][1] = (c-1);
						s++;
						}

					}

					else if (g[l][c+1]){
						
						if (presence(1,(c+1),vec)==0){
						vec[s][0] = 1;
						vec[s][1] = (c+1);
						s++;
						}

					}

					else if (g[l+1][c]){
						
						if (presence((l+1),c,vec)==0){
						vec[s][0] = (l+1);
						vec[s][1] = c;
						s++;
						}

					}
				}
			}
	    }
	
	    else{

			if (l == (size-1)){

				if (c == 0){

					if (g[size-2][0]=='V'){
						
						if (presence((size-2),0,vec)==0){
						vec[s][0] = (size-2);
						vec[s][1] = 0;
						s++;
						}
					}

					elseif (g[size-1][1]=='V'){

						if (presence((size-1),1,vec)==0){
						vec[s][0] = (size-1);
						vec[s][1] = 1;
						s++:
						}
					}	

				else{

					if (c == (size-1)){
		      
						if (g[size-1][size-2]=='V'){
							
							if (presence((size-1),(size-2),vec)==0){
							vec[s][0] = (size-1);
							vec[s][1] = (size-2);
							s++;
							}
						}

						else if (g[size-2][size-1]=='V'){

							if (presence((size-2),(size-1),vec)==0){
							vec[s][0] = (size-2);
							vec[s][1] = (size-1);
							s++;
							}
						}

					}

					else{

						if (g[l][c-1]=='V'){
	
							if (presence(1,(c-1),vec)==0){
							vec[s][0] = l;
							vec[s][1] = (c-1);
							s++;
							}

						}

						else if (g[l-1][c]=='V'){
	
							if (presence((l-1),c,vec)==0){
							vec[s][0] = (l-1)
							vec[s][1] = c
							s++
							}
						}

						else if (g[l][c+1]=='V'){
	
							if (presence(1,(c+1),vec)==0){
							vec[s][0] = l;
							vec[s][1] = (c+1);
							s++;
							}
						}
			}
			
			else{

				if (c == 0){

					if (g[l-1][c]=='V'){
						
						if (presence((l-1),c,vec)==0){
						vec[s][0] = (l-1);
						vec[s][1] = c;
						s++;
						}
					}

					else if (g[l][c+1]=='V'){

						if (presence(l,(c+1),vec)==0){
						vec[s][0] = l;
						vec[s][1] = (c+1);
						s++
						}
					}

					else if (g[l+1][c]=='V'){
	
						if (presence((l+1),c,vec)==0){
						vec[s][0] = (l+1);
						vec[s][1] = c;
						s++;
						}
					}
				}
			   
				else{

		           if(c == (size-1)){

						if (g[l-1][c]=='V'){

							if (presence((l-1),c,vec)==0){
							vec[s][0] = (l-1);
		            	    vec[s][1] = c;
		            	    s++;
							}
						}

						else if (g[l][c-1]=='V'){

							if (presence(l,c-1,vec)==0){
							vec[s][0] = l
		              	    vec[s][1] = (c-1)
		                    s++
							}
						}

						else if (g[l+1][c]=='V'){

							if (presence(l+1,c,vec)==0){
							vec[s][0] = (l+1);v
		                    vec[s][1] = c;
		                    s++;
							}
						}

					}

					else{

						if (g[l][c-1]='V'){

							if (presence(l,(c-1),vec)=0){
							vec[s][0] = l;
		            	    vec[s][1] = (c-1);
		            	    s++;
							}
						}

						else if (g[l-1][c]=='V'){

							if (presence((l-1),c,vec)==0){
							vec[s][0] = (l-1);
		              	    vec[s][1] = c;
		                    s++;
							}
						}

						else if (g[l][c+1]=='V'){

							if (presence(l,c+1,vec)==0){
							vec[s][0] = l;
		                    vec[s][1] = (c+1);
		                    s++;
							}

						}

						else if (g[l+1][c]='V'){

							if (presence((l+1),c,vec)==0){
							vec[s][0] = (l+1);
							vec[s][1] = c;
							s++;
							}
						}
			   
	    		    }
	
	k++;
	l = vec[k][0];
	c = vec[k][1];
	}
printf("La ville contient %ld villages",s);
}