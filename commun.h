#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED


// TRACKING =================


#include <stdio.h>
#include <iostream>
#include <opencv/cv.h>
#include "opencv/highgui.h"
#include "Webcam.h"

#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define sign(x) ((x) > 0 ? 1 : -1)

#define STEP_MIN 5
#define STEP_MAX 100


using namespace std;


//  DRIVER ///================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/io.h>
#include <errno.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <asm/types.h>
#include <fcntl.h>
#include <stdint.h>
#include <math.h>
#include <usb.h>
#include <libusb-1.0/libusb.h>


// *****.h
#include "InputEvent.h"
#include "USBMissileLauncher.h"
#include "traitement.h"
#include "action.h"
#include "initialisation.h"
#include "servoController.h"
#include "traitementCam.h"
#include "protocol.h"

#define USB_TIMEOUT 10000 /* milliseconds */


typedef struct missile_usb missile_usb;

struct missile_usb {
  struct usb_device *device;
  usb_dev_handle    *handle;
  int                debug;
  int                timeout;
  int                interface_claimed;
};

extern int debug_level;


#endif












