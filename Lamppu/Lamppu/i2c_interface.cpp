// 
// 
// 

#include "i2c_interface.h"

class I2CInterface {

	I2CInterface::I2CInterface(){
	// Print some shit maybe? Do inits?
	}

	int I2CInterface::i2c_init(){
	// Initialize the interface, returns return code integer
		Wire.begin();
		return 0;
	}

	byte I2CInterface::i2c_transmit(int address, byte data=NULL){
		// Transmit byte data to i2c address.
		// NOTE: i2c uses 7 bit addressing, take care when looking up addresses from datasheets
		// NOTE: i.e. shift high bits to the right to get the low bits for the address.
		Wire.beginTransmission(address);
		int bytes_written = Wire.write(data);
		byte resp = Wire.endTransmission();
		/*
		Response codes: 
			0: Success
			1: Data too long to fit in transmit buffer
			2: Received NACK on transmit of address
			3: Received NACK on transmit of data
			4: Other error
		*/
		return resp;
	}

	byte i2c_transmit(int address, char str[]){
		// Transmit a string
		// NOTE: i2c uses 7 bit addressing, take care when looking up addresses from datasheets
		// NOTE: i.e. shift high bits to the right to get the low bits for the address.
		Wire.beginTransmission(address);
		int bytes_written = Wire.write(str);
		byte resp = Wire.endTransmission();
		/*
		Response codes: 
			0: Success
			1: Data too long to fit in transmit buffer
			2: Received NACK on transmit of address
			3: Received NACK on transmit of data
			4: Other error
		*/
		return resp;
	}

	byte * i2c_read(int address, int bytes, byte * data, boolean stop=true){
		// Read amount of bytes shown by bytes to an array. Returns pointer to that array.
		// NOTE: i2c uses 7 bit addressing, take care when looking up addresses from datasheets
		// NOTE: i.e. shift high bits to the right to get the low bits for the address.
		Wire.requestFrom(address, bytes, stop);
		while(Wire.available() < bytes);
		for(int i = 0; i < bytes; i++){
			if (Wire.available() > 0){
				data[i] = Wire.read();
			}
		}
	}


};
