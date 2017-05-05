#include "commun.h"

#define PI 3.14159

int profondeur(float positionDroite, float positionGauche, float l){ // d = alpha sur l'image (soit l'angle)
	float angleDroite = 177 - ((positionDroite-64)/(3275.21/177)); //0deg=2550 180deg=700
	float angleGauche = 3 + (positionGauche-64)/(3275.21/177); //0deg=760 180deg=2400
	cout << endl << "L'angle de droite est: " << angleDroite << endl;
	cout << "L'angle de gauche est: " << angleGauche << endl;
	int h = ((int)((l*sin(angleDroite*(PI/180))*cos((90-angleGauche)*(PI/180)))/sin((180-angleGauche-angleDroite)*(PI/180))))*(-1); //formule trigo
	if(h>0){
		return h;
	}
	else {
		return 0;
	}
}



