/*
 Name:		Lamppu.ino
 Created:	5/9/2016 1:16:41 PM
 Author:	Jodi
*/

String valueString = "";

volatile boolean mutex;
volatile boolean stringComplete;
const int SERIAL_STR_LEN = 256;
const int SERIAL_BUF_LEN = 5;
const int NUM_COMMANDS = 5;
//Change size here to accommodate all commands we need. Or to conserve memory change type to array of pointers?
String commands[NUM_COMMANDS];
char inputString[SERIAL_STR_LEN];


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	mutex = false; 
	stringComplete = false;
}

// the loop function runs over and over again until power down or reset
void loop() {
	if(!mutex && stringComplete){
		mutex = true;
		Serial.println(inputString);
		memset(inputString, 0, SERIAL_STR_LEN);
		mutex = false;
		stringComplete = false; 
	}
}


//Interrupt handler for UART
void serialEvent(){
	if(!mutex){
		//Reserve access to buffer.
		mutex = true;
		while(Serial.available()){
			// Indicate reading is ongoing.
			stringComplete = false;
			// Read bytes until terminator or max length.
			byte inChar = Serial.readBytesUntil(0, inputString, SERIAL_STR_LEN);
			// Indicate read Complete, result stored in array.
			stringComplete = true;
		}
	}
	// Release mutex
	mutex = false;
	
}

boolean validate_tlv(String tlv_data){
	int slashes = 0;
	for(int i = 0; i < tlv_data.length(); i++){
		if(tlv_data[i] == '/'){
			slashes = slashes + 1;
		}
	}
	if(slashes == 2){

		return true;
	}
	else{
		return false;
	}
}