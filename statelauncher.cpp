/*
 * statelauncher.cpp
 *
 *  Created on: 3 mai 2017
 *      Author: isen
 */

#include "commun.h"


state_launcher::state_launcher() {
	angle_h=90;
	angle_v=75; //90
}

state_launcher::~state_launcher() {
	}

void state_launcher :: update_state(float new_ah, float new_av){
	angle_h=new_ah;
	angle_v=new_av;
}

int state_launcher :: get_angleV (){
	return angle_v;
}

int state_launcher :: get_angleH () {
	return angle_h;
}
