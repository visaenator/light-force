/*
 Name:		Lamppu.ino
 Created:	5/9/2016 1:16:41 PM
 Author:	Jodi
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
String valueString = "";
String inputString = "";
volatile boolean mutex;
volatile boolean stringComplete = false;
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
	lcd.begin(16, 2);
	inputString.reserve(256);
	mutex = false; 
	/*pinMode(ledPin1, OUTPUT);
	pinMode(ledPin3, OUTPUT);
	pinMode(ledPin2, INPUT);*/

}

// the loop function runs over and over again until power down or reset
void loop() {
	//lcd.print("ASD");
	/*analogWrite(currently, 255);
	buttonState = digitalRead(ledPin2);
	if(buttonState == HIGH){
		changeLedState();
	}*/
  if(!mutex && stringComplete){
		lcd.clear();
		//Serial.println(inputString);
		if(inputString.length() < 16){
			lcd.print(inputString);
		}
		else if(inputString.length() > 16 && inputString.length() <= 32){
			lcd.print(inputString.substring(0, 16));
			lcd.setCursor(0,1);
			lcd.print(inputString.substring(16, inputString.length()));
		}
		else{
			lcd.print("FU TALK LESS");
		}
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
			//	Check if found command is in list of known commands
				//	Save command, save value
				//	Change flag to indicate command and value are available
		}else{
			char inChar = (char)Serial.read();
			if(inChar == '/'){
				stringComplete = true;
			}
			else{
				commandString += inChar;
			}
		}
		
			
		inputString += inChar;
		if(inputString.substring(inputString.length() - 2, inputString.length()).equals("CR")){
			stringComplete = true;
			mutex = false;
		}
	}
}