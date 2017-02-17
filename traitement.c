#include "traitement.h"
#include "action.h"
#include <math.h>

void traitement(int p_Dx, int p_Dy){


	if(p_Dx<0 && p_Dy>0 ){
		action(1);
	}
	else if(p_Dx>0 && p_Dy>0 ){
	  action(2);
	}
	else if(p_Dx<0 && p_Dy<0 ){
		action(3);
	}
	else if(p_Dx>0 && p_Dy<0 ){
		action(4);
	}
	else{
		action(10);
	}

	//rajouter le tir dans les 10%

}
