/*#include <iostream>
#include <string>
#include <libusb-1.0/libusb.h>
#include <usb.h>
#include "protocol.h"
#include "traitementCam.h"*/
#include "commun.h"

#define PI 3.14159


using namespace std;


  PololuMaestro::PololuMaestro() {
    //const unsigned short vendorId = 0x1ffb;//const unsigned short vendorId = 0x1ffb;
    //unsigned short productIDArray = 0x0089;//unsigned short productIDArray[] = {0x0089, 0x008a, 0x008b, 0x008c};
    libusb_init(&ctx);
    int count = libusb_get_device_list(ctx, &device_list);

    for(int i=0;i<count;i++) {
      device = device_list[i]; {
        cout << "Found device\n";
        break;
      }
    }

    libusb_free_device_list(device_list, 0);
    //libusb_exit(ctx);
  }

  struct __attribute__((__packed__)) PololuMaestro::servo {
    int16_t position;
    int16_t target;
    uint16_t speed;
    uint8_t acceleration;
  };

  struct PololuMaestro::maestro_variables {
    // The number of values on the data stack (0-32).  A value of 0 means the stack is empty.
    uint8_t stackPointer;

    /// The number of return locations on the call stack (0-10).  A value of 0 means the stack is empty.
    uint8_t callStackPointer;

    /// The error register.  Each bit stands for a different error (see uscError).
    /// If the bit is one, then it means that error occurred some time since the last
    /// GET_ERRORS serial command or CLEAR_ERRORS USB command.
    uint16_t errors;

    /// The address (in bytes) of the next bytecode instruction that will be executed.
    uint16_t programCounter;

    /// <remarks>This is public to avoid mono warning CS0169.</remarks>
    int16_t buffer[3];

    /// The data stack used by the script.  The values in locations 0 through stackPointer-1
    /// are on the stack.
    int16_t stack[32];

    /// The call stack used by the script.  The addresses in locations 0 through
    /// callStackPointer-1 are on the call stack.  The next return will make the
    /// program counter go to callStack[callStackPointer-1].
    uint16_t callStack[10];

    /// 0 = script is running.
    /// 1 = script is done.
    /// 2 = script will be done as soon as it executes one more instruction
    ///     (used to implement step-through debugging features)
    uint8_t scriptDone;

    /// <remarks>This is public to avoid mono warning CS0169.</remarks>
    uint8_t buffer2;

    servo servos[6];
  };

  bool PololuMaestro::deviceMatchesVendorProduct(libusb_device *device, unsigned short idVendor, unsigned short idProduct) {
    libusb_device_descriptor desc;
    libusb_get_device_descriptor(device, &desc);
    return idVendor == desc.idVendor && idProduct == desc.idProduct;
  }

  uint16_t PololuMaestro::getPosition(unsigned int channel) {
    maestro_variables vars;
    libusb_device_handle *device_handle;

    libusb_open(device, &device_handle);
    libusb_control_transfer(device_handle, 0xC0, REQUEST_GET_VARIABLES, 0, 0, (unsigned char*)&vars, (ushort)sizeof(uscVariables), (ushort)5000);
    libusb_close(device_handle);

    return vars.servos[channel].position;
  }

  void PololuMaestro::setTarget(uint8_t channel, uint16_t target) {
    libusb_device_handle *device_handle;

    libusb_open(device, &device_handle);
    libusb_control_transfer(device_handle, 0x40, REQUEST_SET_TARGET, target, channel, 0, 0, (ushort)5000);
    libusb_close(device_handle);
  }

  void PololuMaestro::setSpeed(uint8_t channel, uint16_t speed) {
    libusb_device_handle *device_handle;

    libusb_open(device, &device_handle);
    libusb_control_transfer(device_handle, 0x40, REQUEST_SET_SERVO_VARIABLE, speed, channel, 0, 0, (ushort)5000);
    libusb_close(device_handle);
  }

  void PololuMaestro::setAcceleration(uint8_t channel, uint16_t accel) {
    libusb_device_handle *device_handle;

    libusb_open(device, &device_handle);
    libusb_control_transfer(device_handle, 0x40, REQUEST_SET_SERVO_VARIABLE, accel, channel | 0x80, 0, 0, (ushort)5000);
    libusb_close(device_handle);
  }

  uint8_t low(uint16_t n) {
    return n & 0x7F;
  }

  uint8_t high(uint16_t n) {
    return (n >> 7) & 0x7F;
  }


    Servo::Servo(PololuMaestro *_driver, uint8_t _channel) {
        driver = _driver;
        channel = _channel;
        cout << "Servo created \n";
    }

    void Servo::setAngle(uint16_t angle) {
      float ratio = (angle - (float)min_angle) / ((float)max_angle - (float)min_angle);

      float pos = (float)min_ms + (ratio * ((float)max_ms - (float)min_ms));

      driver->setTarget(channel, (uint16_t)pos * 4);
    }

    void Servo::setSpeed(uint16_t speed) {
      driver->setSpeed(channel, speed);
    }

    void Servo::setAcceleration(uint16_t accel) {
      driver->setAcceleration(channel, accel);
    }

    float Servo::getPosition() {
      float ms = (float)(driver->getPosition(channel)) / 4.0;
      float pos = (ms - min_ms) / (max_ms - min_ms);

      return min_angle + (pos * (max_angle - min_angle));
    }

    float Servo::getMs() {
      return driver->getPosition(channel) / 4.0;
    }

    void Servo::inc(int16_t i) {
      setAngle(getPosition() + i);
    }

    void Servo::minAngle(uint16_t _min_angle) {
      min_angle = _min_angle;
    }

    void Servo::maxAngle(uint16_t _max_angle) {
      max_angle = _max_angle;
    }

    void Servo::minMs(uint16_t _min_ms) {
      min_ms = _min_ms;
    }

    void Servo::maxMs(uint16_t _max_ms) {
      max_ms = _max_ms;
    }

    void Servo::configuration(int angle){
    	min_angle = 64 ;
    	max_angle = 3280;
    	min_ms = 800;
    	max_ms = 2200;
    	driver->setSpeed(channel, 0);
    	driver->setAcceleration(channel, 0);
    	setAngle(angle);
    }



int main(int argc, char* argv[]) {

	char key=0;
	int focus1, focus2;
	Mat image1, image2;
	Mat imageBinaire1, imageBinaire2;
	Mat imageTracking1, imageTracking2;
	VideoCapture fluxVideo1, fluxVideo2;
	CvPoint positionObj1, positionObj2;
	int dx1=0, dy1=0, dx2, dy2;

	PololuMaestro driver;
	Servo pan1(&driver, 2);
	pan1.configuration(2000);
	Servo tilt1(&driver, 3);
	tilt1.configuration(2000);
	Servo pan2(&driver, 0);
	pan2.configuration(2000);
	Servo tilt2(&driver, 1);
	tilt2.configuration(1800);

	Webcam * maWebcam = new Webcam();
    Webcam * maWebcam1 = new Webcam();
    fluxVideo1 = maWebcam1->initFlux(0);
    Webcam * maWebcam2 = new Webcam();
    fluxVideo2 = maWebcam2->initFlux(1);

    while(key!='q' && key!='Q') {

        fluxVideo1 >> image1; //récupération du flux video dans la var image
        imageBinaire1 = maWebcam1->binairisation(image1); //binairisation de l'image
        positionObj1=maWebcam1->calculBarycentre(imageBinaire1); //calcul barycentre
        imageTracking1 = maWebcam1->tracking(positionObj1, image1); //affiche un point rouge sur la cible

        fluxVideo2 >> image2; //récupération du flux video dans la var image
        imageBinaire2 = maWebcam2->binairisation(image2); //binairisation de l'image
        positionObj2=maWebcam2->calculBarycentre(imageBinaire2); //calcul barycentre
        imageTracking2 = maWebcam2->tracking(positionObj2, image2); //affiche un point rouge sur la cible*/


        // l'origine des pixel est en haut à gauche
        dx1=positionObj1.x - 320;
        dy1=240 - positionObj1.y;
        dx2=positionObj2.x - 320;
        dy2=240 - positionObj2.y;

        //cout << " dX1="<< dx1 << " dY1=" << dy1 << endl;
        //cout << " dX2="<< dx2 << " dY2=" << dy2 << endl;

        if( dx1==(-321) && dy1==(241) ){
        	cout << "tracking 1 manquant" << endl;
        }
        else if( dx2==(-321) && dy2==(241) ){
        	cout << "tracking 2 manquant" << endl;
        }
        else {
        	int hauteur = profondeur( (float)pan1.getPosition(), (float)pan2.getPosition(), 50);
        	cout << "La distance de l'objet est : " << hauteur << endl;
        }

        int marge = 5000;
        //traitement tracking cam
        if( (maWebcam1->nbPixels)>((maWebcam2->nbPixels)+marge) ){ // permet de réorienter les webcam vers la cible principale
        	focus1 = 1;
        	focus2 = 0;
        }else if( (maWebcam2->nbPixels)>((maWebcam1->nbPixels)+marge) ){
        	focus2 = 1;
        	focus1 = 0;
        }
        else{
        	focus1 = 1;
        	focus2 = 1;
        }
        traitementCam(dx1, dy1, pan1, tilt1, focus1, 1);
        traitementCam(dx2, dy2, pan2, tilt2, focus2, 2);

        //Affichage des fenetres :
        maWebcam->affiche(imageTracking1, imageBinaire1, imageTracking2, imageBinaire2);

        if(waitKey(30) >= 0); // on patiente 30 millisecondes avant de passer à l'image suivante

    }

    delete maWebcam1;
    delete maWebcam2;
    return 0;

}



