#include "commun.h"



void traitement(missile_usb * control_traitement,int p_Dx, int p_Dy){


   // cout<< "traitement" << endl;

    int delay =1000; //1000 ou ((11*fabs(p_Dx))+(14*fabs(p_Dy)))/2;

    int R = 40;
   // int *compteur;

    //sleep(4);
    //*compteur=0;



    if(p_Dx==(-641) && p_Dy==(481)){
        action(control_traitement,20, delay);
        printf("hors du cadre");
	}

	else if(p_Dx<(R) && p_Dy>(-R) && p_Dx>(-R) && p_Dy<(R)) {
		printf(" cible verrouillé ");
        action(control_traitement,10, delay);
	}

	else if((p_Dx<(0) && p_Dy>(0))) {
		action(control_traitement, 1, delay);
		printf("cas 1 ");
	}
	else if((p_Dx>(0) && p_Dy>(0))) {
	  action(control_traitement, 2, delay);
	  printf("cas 2 ");
	}
	else if((p_Dx<(0) && p_Dy<(0))) {
		action(control_traitement, 3, delay);
		printf("cas 3 ");
	}
	else if((p_Dx>(0) && p_Dy<(0))) {
		action(control_traitement, 4, delay);
		printf("cas 4 ");
	}


	else{
        printf("erreur de traitement");
	}

	//rajouter le tir dans les 10%

}
