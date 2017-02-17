#include "commun.h"


int debug_level = 0;

  //---------------------------------------------------------------------------

missile_usb * init(int *device_type){

	char *device = NULL;

  unsigned int set_event = 0;

  if (missile_usb_initialise() != 0) {
    fprintf(stderr, "missile_usb_initalise failed: %s\n", strerror(errno));
    return NULL;
  }


    missile_usb* control_init=missile_usb_create(debug_level, USB_TIMEOUT);


  if (control_init == NULL) {
    fprintf(stderr, "missile_usb_create() failed\n");
    return NULL;
  }

  if (missile_usb_finddevice(control_init, 0, *device_type) != 0) {
    fprintf(stderr, "USBMissileLauncher device not found\n");
    return NULL;
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

 /*   if (control_init!= NULL) {
        cout<< control_init->timeout << " / succès initialisation" << endl;
    } */

    return control_init;
}
