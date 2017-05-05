#ifndef SERVOCONTROLLER_H_
#define SERVOCONTROLLER_H_

using namespace std;

class PololuMaestro
{
    public:
		PololuMaestro();
		struct __attribute__((__packed__)) servo;
		struct maestro_variables;
		bool deviceMatchesVendorProduct(libusb_device *device, unsigned short idVendor, unsigned short idProduct);
		uint16_t getPosition(unsigned int channel);
		void setTarget(uint8_t channel, uint16_t target);
		void setSpeed(uint8_t channel, uint16_t speed);
		void setAcceleration(uint8_t channel, uint16_t accel);
    private:
		uint8_t low(uint16_t n);
		uint8_t high(uint16_t n);
		libusb_context *ctx;
		libusb_device *device;
		libusb_device **device_list;
};


class Servo
{
    public:
		Servo(PololuMaestro *_driver, uint8_t _channel);
		void setAngle(uint16_t angle);
		void setSpeed(uint16_t speed);
		void setAcceleration(uint16_t accel);
		float getPosition();
		float getMs();
		void inc(int16_t i);
		void minAngle(uint16_t _min_angle);
		void maxAngle(uint16_t _max_angle);
		void minMs(uint16_t _min_ms);
		void maxMs(uint16_t _max_ms);
		void configuration(int angle);

    private:
		PololuMaestro *driver;
		uint8_t channel;
		uint16_t min_angle;
		uint16_t max_angle;
		uint16_t min_ms;
		uint16_t max_ms;
};


#endif
