/*
 Name:		Lamppu.ino
 Created:	5/9/2016 1:16:41 PM
 Author:	Jodi
*/

String inputString = "";
volatile boolean mutex;
volatile boolean stringComplete = false;


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	inputString.reserve(256);
	mutex = false; 
}

// the loop function runs over and over again until power down or reset
void loop() {
  if(!mutex && stringComplete){
		Serial.println(inputString);
		inputString = "";
		mutex = true;
		stringComplete = false; 
	}
}

//Interrupt handler for UART
void serialEvent(){
	while(Serial.available()){
		mutex = false; 
		char inChar = (char)Serial.read();
		inputString += inChar;
		if(inChar == '\n'){
			stringComplete = true;
			mutex = true;
			Serial.println(inputString);
		}
	}
}