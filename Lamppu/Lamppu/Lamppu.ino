/*
 Name:		Lamppu.ino
 Created:	5/9/2016 1:16:41 PM
 Author:	Jodi
*/
String valueString = "";
String inputString = "";
volatile boolean mutex;
volatile boolean stringComplete = false;
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
	while(Serial.available()){
		mutex = true;

		if(stringComplete == true){

			for(int i = 0; i < NUM_COMMANDS; i++){

				if (inputString.equals(commands[i])){

					//	Save command, save value
					commandString = inputString;
					inputString = "";

					while(!look_for_slash());
					inputString = "";

					while(!look_for_slash());
					valueString = inputString;
					inputString = "";

					//	Change flag to indicate command and value are available
					mutex = false;
					break;
				}
			}
			if(inputString.length() != 0){
				inputString = "";
				while(!look_for_slash);
				// TODO: Convert inputString to int and skip that many chars on the value. 
			}
				
				
		}else{
			while(!look_for_slash());
			stringComplete = true;
		}
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