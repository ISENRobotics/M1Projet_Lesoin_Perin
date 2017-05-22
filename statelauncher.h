/*
 * statelauncher.h
 *
 *  Created on: 3 mai 2017
 *      Author: isen
 */

#ifndef STATELAUNCHER_H_
#define STATELAUNCHER_H_

class state_launcher {

public :
	float angle_h;
	float angle_v;

public:
	state_launcher();
	~state_launcher();
	void update_state(float new_ah, float new_av);
	int get_angleV();
	int get_angleH();
};

#endif /* STATELAUNCHER_H_ */
