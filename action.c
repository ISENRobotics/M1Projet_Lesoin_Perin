#include "traitement.h"
#ifndef DEPEND
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/io.h>
#include <errno.h>
#include <linux/input.h>
#endif
#include "InputEvent.h"
#include "USBMissileLauncher.h"
#include "traitement.h"
#include "action.h"

#define USB_TIMEOUT 1000 /* milliseconds */

missile_usb *control;
  
  //---------------------------------------------------------------------------

void action(int p_commande, int p_delay){

  unsigned int set_fire = 0, set_left = 0, set_right = 0;
  unsigned int set_up = 0, set_down = 0, set_stop = 0;
  
  int delay = p_delay; // butée = 3.5 s

  //---------------------------------------------------------------------------

	if (p_commande == 0) {
		delay = 3000; 
		set_left=1;
		set_down=1;
		set_stop = 1;
	}
	else if(p_commande == 1){ // cible en haut à gauche
		set_left = 1; 
		set_up = 1;
		set_stop = 1;
	}
	else if(p_commande == 2){ // cible en haut à droite
		set_right = 1; 
		set_up = 1;
		set_stop = 1;
	}
	else if(p_commande == 3){ // cible en bas à gauche
		set_left = 1; 
		fprintf(stderr,"tour\n");
		set_down = 1;
		set_stop = 1;
	}
	else if(p_commande == 4){ // cible en bas à droite
		set_right = 1; 
		set_down = 1;
		set_stop = 1;
	}
	else if(p_commande == 10){ // cible accrochée
		set_fire = 1; 
		set_stop = 1;
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

    missile_do(control, msg, DEVICE_TYPE_MISSILE_LAUNCHER);
    
    if (set_stop) {
      usleep(delay * 1000);
      missile_do(control, MISSILE_LAUNCHER_CMD_STOP, DEVICE_TYPE_MISSILE_LAUNCHER);
    }
    
}
