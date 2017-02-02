// 
// 
// 

#include "i2c_interface.h"

class I2CInterface {

	I2CInterface::I2CInterface(){
	// Print some shit maybe? Do inits?
	};

	int I2CInterface::i2c_init(){
	// Initialize the interface, returns return code integer
	};

	byte I2CInterface::i2c_transmit(int address, byte data=NULL){
	// Transmit byte data to i2c address.
	}


};
