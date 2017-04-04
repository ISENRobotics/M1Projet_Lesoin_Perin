#include "commun.h"

//---------------------------------------------------------------------------

void action(missile_usb * control_action, int p_commande, int p_delay){

  unsigned int set_fire = 0, set_left = 0, set_right = 0;
  unsigned int set_up = 0, set_down = 0, set_stop = 0;

  int delay = p_delay; // butée = 3.5 s


  //---------------------------------------------------------------------------

	/*if (p_commande == 0) {
		delay = 3000;
		set_left=1;
		set_down=1; } */
		//set_stop = 1;

	if(p_commande == 1){ //4 zones -> sens de la lecture
		set_left = 1;
		set_up = 1;
		//set_stop = 1;
	}
	else if(p_commande == 2){
		set_right = 1;
		set_up = 1;
		//set_stop = 1;
	}
	else if(p_commande == 3){
		set_left = 1;
		set_down = 1;
		//set_stop = 1;
	}
	else if(p_commande == 4){
		set_right = 1;
		set_down = 1;
		//set_stop = 1;
	}
	else if(p_commande == 10){
		set_fire = 1;
        set_stop = 1;
	}
	else if(p_commande == 20){
        //set_stop = 1;
	}

  char msg = 0x00;


    if (set_left)
      msg |= MISSILE_LAUNCHER_CMD_LEFT; //masque de la commande en hexa

    if (set_right)
      msg |= MISSILE_LAUNCHER_CMD_RIGHT;

    if (set_up)
      msg |= MISSILE_LAUNCHER_CMD_UP;

    if (set_down)
      msg |= MISSILE_LAUNCHER_CMD_DOWN;

    if (set_fire)
      msg |= MISSILE_LAUNCHER_CMD_FIRE;

    missile_do(control_action, msg, /*device_type*/DEVICE_TYPE_MISSILE_LAUNCHER);

    if (set_stop) {
      usleep(delay * 1000);
      missile_do(control_action, MISSILE_LAUNCHER_CMD_STOP, DEVICE_TYPE_MISSILE_LAUNCHER);
    }

}
