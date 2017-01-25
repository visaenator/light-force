// i2c_interface.h
/***
This library is a wrapper for functionalities needed from a generic i2c master using the Arduino Wire library. 

***/
#ifndef _I2C_INTERFACE_h
#define _I2C_INTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class I2CInterface {

public:
	I2CInterface();
	int i2c_init();
	byte i2c_transmit(int address, byte data=NULL);
	byte i2c_transmit(int address, char str[]);
	byte i2c_transmit(int address, byte data[], int len);
	byte* i2c_read(int address, int bytes, boolean stop=true);

};

#endif

