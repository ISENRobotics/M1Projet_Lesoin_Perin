#include "commun.h"



void traitement(missile_usb * control_traitement,int pos_c, int pos_l){


    int delay =110;        //1000 ou ((11*fabs(p_Dx))+(14*fabs(p_Dy)))/2;

   // int R = 40;

    float ecart=pos_c-pos_l;
    cout << "ecart = " << ecart << endl;
    int mouv=ecart/2;
    int nb_inc=abs(mouv);
    //cout << "le nb d'incrémentations est : " << nb_inc << endl;
    int i=0;

    if (ecart<-5) {
    	printf("cible à gauche\n");
    	for (i=0;i<=nb_inc;i++) {
    		action(control_traitement,1,delay);
    	}
    }

    else if (ecart>5) {
        printf("cible à droite\n");
        for (i=0;i<=nb_inc;i++) {
        	action(control_traitement,2,delay);
        }
    }

	else {
		action(control_traitement,10,delay);
        printf("Cible vérouillée par le lance missile \n  ");
	}


}
