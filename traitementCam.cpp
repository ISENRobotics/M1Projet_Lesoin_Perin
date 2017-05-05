#include "commun.h"

void traitementCam(int dx, int dy, Servo pan, Servo tilt, int focus, int numCam){
    float panAngle=pan.getPosition();
    float tiltAngle=tilt.getPosition();
    int R = 40; // zone de verrouillage
    int correctionX = abs((int)(dx/4)); // correction proportionnelle à l'écart
    int correctionY = abs((int)(dy/4));

    if(focus == 1){

		if(dx==(-321) && dy==(241)){
			//pan.setAngle(panAngle-0); // - car quand postition augmente tourelle va vers gauche et non droite
			//tilt.setAngle(tiltAngle-0);
			cout << "hors du cadre de cam " << numCam << endl;
		}
		else if(dx<(R) && dy>(-R) && dx>(-R) && dy<(R)) {
			cout << "cible verouillé par cam " << numCam << endl;
			//pan.setAngle(panAngle-0);
			//tilt.setAngle(tiltAngle-0);
		}
		else if((dx<(0) && dy>(0)) && (panAngle+correctionX)<3280 && (tiltAngle-correctionY)>64 ){
			pan.setAngle(panAngle+correctionX);
			tilt.setAngle(tiltAngle-correctionY);
			//cout << "cas 1" << endl;
		}
		else if((dx>(0) && dy>(0)) && (panAngle-correctionX)>64 && (tiltAngle-correctionY)>64 ) {
			pan.setAngle(panAngle-correctionX);
			tilt.setAngle(tiltAngle-correctionY);
			//cout << "cas 2" << endl;
		}
		else if((dx<(0) && dy<(0)) && (panAngle+correctionX)<3280 && (tiltAngle+correctionY)<3280 ) {
			pan.setAngle(panAngle+correctionX);
			tilt.setAngle(tiltAngle+correctionY);
			//cout << "cas 3" << endl;
		}
		else if((dx>(0) && dy<(0)) && (panAngle-correctionX)>64 && (tiltAngle+correctionY)<3280) {
			pan.setAngle(panAngle-correctionX);
			tilt.setAngle(tiltAngle+correctionY);
			//cout << "cas 4" << endl;
		}

    }else if(focus == 0){ //objet tracké non prioritaire

    	if( numCam == 1){
    		pan.setAngle(1000); // 45 degrés à droite
    		tilt.setAngle(2000);
    	}else if( numCam == 2){
    		pan.setAngle(3000); // 45 degrés à gauche
    		tilt.setAngle(1800);
    	}
    }

}

