#include "traitement.h"
#include "action.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void traitement(int p_Dx, int p_Dy){

	int delay = ((11*fabs(p_Dx))+(14*fabs(p_Dy)))/2; // coef proportionnels au nb de pixels et au delay max 

	int R = 20; // Demi-largeur du carré correspondant à la zone "d'accrochage", 10% de précision sur la hauteur

	if((p_Dx<(0) && p_Dy>(R)) || (p_Dx<(-R) && p_Dy>(0))){ // Cible en haut à gauche
		action(1,delay);
	}
	else if((p_Dx>(0) && p_Dy>(R)) || (p_Dx>(R) && p_Dy>(0))){ // Cible en haut à droite
	  action(2,delay);
	}
	else if((p_Dx<(0) && p_Dy>(-R)) || (p_Dx<(-R) && p_Dy<(0))){ // Cible en bas à gauche
		action(3,delay);
	}
	else if((p_Dx>(0) && p_Dy<(-R)) || (p_Dx>(R) && p_Dy<(0))){ // Cible en bas à droite
		action(4,delay);
	}
	else if(p_Dx<(R) && p_Dy>(-R) && p_Dx>(-R) && p_Dy<(R)){										// Cible accrochée 
		action(10,delay);
	}
	else{
		fprintf(stderr,"erreur traitement \n");
	}
	
}
