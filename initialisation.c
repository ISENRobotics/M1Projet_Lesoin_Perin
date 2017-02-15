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
#include "initialisation.h"

#define USB_TIMEOUT 1000 /* milliseconds */

int debug_level = 0;
missile_usb *control;

  //---------------------------------------------------------------------------
  
void init(int *device_type){

	char *device = NULL;

  unsigned int set_event = 0;

  if (missile_usb_initialise() != 0) {
    fprintf(stderr, "missile_usb_initalise failed: %s\n", strerror(errno));
    //return -1;
  }
  
  control = missile_usb_create(debug_level, USB_TIMEOUT);
  if (control == NULL) {
    fprintf(stderr, "missile_usb_create() failed\n");
    //return -1;
  }
  
  if (missile_usb_finddevice(control, 0, *device_type) != 0) {
    fprintf(stderr, "USBMissileLauncher device not found\n");
    //return -1;
  }

  if (debug_level)
    fprintf(stderr, "Now we're ready.  Move the thing around, and FIRE!\n");

  //---------------------------------------------------------------------------

  int fd;
  struct input_event ev[64];
  int events;

  if (set_event) {

    if (device == NULL) { //
      fprintf(stderr, "No device given\n"); 
      //return 0;
    }
    
    if (IEOpen(device, &fd) < 0) {
      fprintf(stderr, "IEOpen(%s, fd) failed\n", device); //-------------------// 
      //return -1;
    }

    while (1) {

      if (IERead(fd, ev, &events) < 0) {
	fprintf(stderr, "IERead() failed\n");
	//return -1;
      }

      usleep(200000);
	
    }
} 

}
