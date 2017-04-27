/*#include <iostream>
#include <string>
#include <libusb-1.0/libusb.h>
#include <usb.h>
#include "protocol.h"
#include "traitementCam.h"*/
#include "commun.h"


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



int main(int argc, char* argv[]) {

	char key=0;
	Mat image;
	Mat imageBinaire;
	Mat imageTracking;
	VideoCapture fluxVideo;
	CvPoint positionObj;
	int dx=0, dy=0;

	PololuMaestro driver;
	Servo pan(&driver, 0);
    pan.minAngle(64);
    pan.maxAngle(3280);
    pan.minMs(800);
    pan.maxMs(2200);
    pan.setSpeed(0);
    pan.setAcceleration(0);
    pan.setAngle(1672);
	Servo tilt(&driver, 1);
    tilt.minAngle(64);
    tilt.maxAngle(3280);
    tilt.minMs(800);
    tilt.maxMs(2200);
    tilt.setSpeed(0);
    tilt.setAcceleration(0);
    tilt.setAngle(1672);

    Webcam * maWebcam = new Webcam();
    cout << "webcam opened" << endl;
    fluxVideo = maWebcam->initFlux();

    while(key!='q' && key!='Q') {

        fluxVideo >> image; //récupération du flux video dans la var image

        imageBinaire = maWebcam->binairisation(image); //binairisation de l'image

        positionObj=maWebcam->calculBarycentre(imageBinaire); //calcul barycentre
        imageTracking = maWebcam->tracking(positionObj, image); //affiche un point rouge sur la cible

        // l'origine des pixel est en haut à gauche
        dx=positionObj.x - 320;
        dy=240 - positionObj.y;

        cout << " dX="<< dx << " dY=" << dy << endl;

        //traitement
        float panAngle=pan.getPosition();
        float tiltAngle=tilt.getPosition();
		int panCoef=2; // coeff idéal 5.025
		int tiltCoef=2;  //coef idéal 6.7
	    int R = 40;
	    int delay = 20;

	    if(dx==(-321) && dy==(241)){
	    	pan.setAngle(panAngle-0); // - car quand postition augmente tourelle va vers gauche et non droite
	    	tilt.setAngle(tiltAngle-0);
	        printf("hors du cadre");
		}
		else if(dx<(R) && dy>(-R) && dx>(-R) && dy<(R)) {
			printf(" cible verrouillé ");
			pan.setAngle(panAngle-0);
			tilt.setAngle(tiltAngle-0);
		}
		else if((dx<(0) && dy>(0))) {
			pan.setAngle(panAngle+delay);
			tilt.setAngle(tiltAngle-delay);
			printf("cas 1 ");
		}
		else if((dx>(0) && dy>(0))) {
			pan.setAngle(panAngle-delay);
			tilt.setAngle(tiltAngle-delay);
			printf("cas 2 ");
		}
		else if((dx<(0) && dy<(0))) {
			pan.setAngle(panAngle+delay);
			tilt.setAngle(tiltAngle+delay);
			printf("cas 3 ");
		}
		else if((dx>(0) && dy<(0))) {
			pan.setAngle(panAngle-delay);
			tilt.setAngle(tiltAngle+delay);
			printf("cas 4 ");
		}

        //Affichage des fenetres :
        maWebcam->affiche(imageTracking, imageBinaire);

        if(waitKey(30) >= 0); // on patiente 30 millisecondes avant de passer à l'image suivante

    }

    delete maWebcam;
    return 0;

}



