#include "commun.h"

int traitementCam(int dx, int dy, Servo pan, Servo tilt, int focus, int numCam, int panCam1, int panCam2, int tiltCam1, int tiltCam2){
    float panAngle=pan.getPosition();
    float tiltAngle=tilt.getPosition();
    int R = 20; // zone de verrouillage
    int correctionX = abs((int)(dx/4)); // correction proportionnelle à l'écart
    int correctionY = abs((int)(dy/4));

    if(focus == 1){

		if(dx==(-321) && dy==(241)){
			cout << "hors du cadre de cam " << numCam << endl;
			return 0;
		}
		else if(dx<(R) && dy>(-R) && dx>(-R) && dy<(R)) {
			cout << "cible verouillé par cam " << numCam << endl;
			return 1;
		}
		else if((dx<(0) && dy>(0)) && (panAngle+correctionX)<3280 && (tiltAngle-correctionY)>64 ){
			pan.setAngle(panAngle+correctionX);
			tilt.setAngle(tiltAngle-correctionY);
			return 0;
		}
		else if((dx>(0) && dy>(0)) && (panAngle-correctionX)>64 && (tiltAngle-correctionY)>64 ) {
			pan.setAngle(panAngle-correctionX);
			tilt.setAngle(tiltAngle-correctionY);
			return 0;
		}
		else if((dx<(0) && dy<(0)) && (panAngle+correctionX)<3280 && (tiltAngle+correctionY)<3280 ) {
			pan.setAngle(panAngle+correctionX);
			tilt.setAngle(tiltAngle+correctionY);
			return 0;
		}
		else if((dx>(0) && dy<(0)) && (panAngle-correctionX)>64 && (tiltAngle+correctionY)<3280) {
			pan.setAngle(panAngle-correctionX);
			tilt.setAngle(tiltAngle+correctionY);
			return 0;
		}

    }else if(focus == 0){ //objet tracké non prioritaire
    	if( numCam==1 && panCam2<2000 ){
    		pan.setAngle(panCam2-500); // 45 degrés à gauche
    		tilt.setAngle(2000); //2000
    		return 0;
    	}else if( (numCam==1) ){
    	    pan.setAngle(panCam2-500); // 45 degrés à droite
    	    tilt.setAngle(2000);
    	    return 0;
    	}else if( numCam==2 && panCam1<2000 ){
    		pan.setAngle(panCam1+500); // 45 degrés à gauche
    		tilt.setAngle(1800); //1800
    		return 0;
    	}else if( (numCam==2) ){
    		pan.setAngle(panCam1+500); // 45 degrés à droite
        	tilt.setAngle(1800);
        	return 0;
    	}

    }

}

