#include "commun.h"



void traitement(missile_usb * control_traitement,float angleCibleLauncherPan, float angleLauncherPan, float angleCibleLauncherTilt, float angleLauncherTilt){


    int delay = 90; //110

    float ecartPan = angleCibleLauncherPan - angleLauncherPan;
    int mouvPan=ecartPan/2;
    int nb_inc_pan=abs(mouvPan);

    float ecartTilt = (angleCibleLauncherTilt - angleLauncherTilt)/2.5;
    cout << "ecartTilt = " << ecartTilt << endl;
    int mouvTilt=ecartTilt;
    int nb_inc_tilt=abs(mouvTilt);

    int i=0;

    if (ecartPan<-5) {
    	printf("cible à gauche\n");
    	for (i=0;i<=nb_inc_pan;i++) {
    		action(control_traitement,1,delay);
    	}
    }
    else if (ecartPan>5) {
        printf("cible à droite\n");
        for (i=0;i<=nb_inc_pan;i++) {
        	action(control_traitement,2,delay);
        }
    }



    if (ecartTilt<-5) {
    	printf("cible en haut\n");
    	for (i=0;i<=nb_inc_tilt;i++) {
    		action(control_traitement,4,delay); //
    	}
    }
    else if (ecartTilt>5) {
        printf("cible en bas\n");
        for (i=0;i<=nb_inc_tilt;i++) {
        	action(control_traitement,3,delay); //
        }
    }
	else {
		action(control_traitement,10,delay);
        printf("Cible vérouillée par le lance missile \n  ");
	}


}
