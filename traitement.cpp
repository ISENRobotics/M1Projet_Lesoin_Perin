#include "commun.h"

void traitement(missile_usb * control_traitement,int p_Dx, int p_Dy){


    cout<< "traitement" << endl;

    int delay = 100;//((11*fabs(p_Dx))+(14*fabs(p_Dy)))/2;

    int R = 20;

	if(p_Dx<0 && p_Dy>0 ){
		action(control_traitement, 1, delay);
	}
	else if(p_Dx>0 && p_Dy>0 ){
	  action(control_traitement, 2, delay);
	}
	else if(p_Dx<0 && p_Dy<0 ){
		action(control_traitement, 3, delay);
	}
	else if(p_Dx>0 && p_Dy<0 ){
		action(control_traitement, 4, delay);
	}
	else{
		action(control_traitement,10, delay);
	}

	//rajouter le tir dans les 10%

}
