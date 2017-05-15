#include "commun.h"


float calculDistance(float angleCamGauche, float angleCamDroite, float l){ // d = alpha sur l'image (soit l'angle)
	//float h = ((l*sin(angleCamDroite*(PI/180))*cos((90-angleCamGauche)*(PI/180)))/sin((180-angleCamGauche-angleCamDroite)*(PI/180)));
	float h = (l*sin(angleCamDroite*(PI/180))*sin((angleCamGauche)*(PI/180)))/sin((180-angleCamGauche-angleCamDroite)*(PI/180));
	if(h>0){
		return h;
	}
	else {
		return 0;
	}
}



