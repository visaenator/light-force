/*
 Name:		Lamppu.ino
 Created:	5/9/2016 1:16:41 PM
 Author:	Jodi
*/
String valueString = "";
String inputString = "";
volatile boolean mutex;
volatile boolean stringComplete;
const int NUM_COMMANDS = 5;
//Change size here to accommodate all commands we need. Or to conserve memory change type to array of pointers?
String commands[NUM_COMMANDS];
String commandString = "";
int ledPin1 = 5;
int ledPin2 = 6;
int ledPin3 = 7;
int sleep = 2000;
int currently = 7;
int buttonState = 0;


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	inputString.reserve(256);
	mutex = false; 
	stringComplete = false;
}

// the loop function runs over and over again until power down or reset
void loop() {
	if(!mutex && stringComplete){
		mutex = true;
		if(validate_tlv(inputString)){
			Serial.println(inputString);
		}
		mutex = false;
		stringComplete = false; 
	}
}

void changeLedState(){
		analogWrite(currently, 0);
		if(currently == 5){
				currently = 7;	
			}
			else{
				currently = 5;
			}
}


//Interrupt handler for UART
void serialEvent(){
	if(!mutex){
		mutex = true;
		delayMicroseconds(100);
		while(Serial.available()){
			stringComplete = false;
			char inChar = (char)Serial.read();
			inputString += inChar;
		}
		stringComplete = true;
	}
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

boolean look_for_slash(){
	char inChar = (char)Serial.read();
	if(inChar == '/'){
		return true;
	}
	else{
		inputString += inChar;
		return false;
	}

}