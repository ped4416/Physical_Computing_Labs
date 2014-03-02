/*
 * Some code taken from an arduino example http://www.ladyada.net/learn/arduino/lesson5.html
 */

int buttonPin = 7;// buttonSwitch is connected to pin 7
int tiltPin = 8;// tiltSwitch is connected to pin 8
int led1Pin = 6;//LED1 connected to pin 6
int led2Pin = 9;//LED2 connected to pin 9
int led3Pin = 10;//LED3 connected to pin 10
int led4Pin = 11;//LED4 connected to pin 11

int tiltValue; // variable for reading the tiltpin status
int tiltValueDelay; // variable for reading the tiltpin delayed status

int buttonVal;// variable for reading the button status
int buttonVal2;// variable for reading the delayed button status
int buttonState;//variable to hold the button state
int ledState = 0;// Variable for the LED state to count from 0 off through 1,2,3,4 for each of the LEDs
int tiltState;// Variable to hold the state of the output pin

void setup() {
  pinMode(buttonPin, INPUT);// Set the button pin as input
  pinMode(tiltPin, INPUT);// Set the tiltSwitch pin as input
  
  //setup all 4 LEDs as outputs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);

  // Set up serial communication at 9600bps
  Serial.begin(9600);           
  buttonState = digitalRead(buttonPin);// read the initial state of the button
  tiltState = digitalRead(tiltPin);// read the initial state of tiltButton
}

void loop(){
  //a method to stop all current being sent to any LEDs via a tiltSwitch
  tiltSwitch();
  //a method to allow a basic switch to iterate through 4 leds left to right
  pushSwitch();
}

//A method to allow a tiltSwitch to turn the current off that goes to any LEDs in a circuit. 
void tiltSwitch(){
  //setup to allow the tilt sensor to reset the LEDs to 0!
  //this has to be called after the main button setup as it was interfering before. 
  tiltValue = digitalRead(tiltPin);   // reads the value at a digital input 
  delay(10); // 10 milliseconds is a good delay amount
  tiltValueDelay = digitalRead(tiltPin);// reads the input again fro bounces
  if (tiltValue == tiltValueDelay) { // make sure there are 2 consistant readings!
     if (tiltValue != tiltState) {  // the tilt button state has changed!
       if (tiltValue == HIGH) {   // check if the button is pressed this can be HIGH or LOW.. only a test of pushing
          ledState = 0;//set teh ledState counter to 0 
          // Set all LEDs to LOW or 0.. 
          if (ledState == 0) { // all-off when state is at 0. 
            digitalWrite(led1Pin, LOW);
            digitalWrite(led2Pin, LOW);
            digitalWrite(led3Pin, LOW);
            digitalWrite(led4Pin, LOW);
         }
       }
     }  
  }
}

//a method to allow a push button to count through 4 LEDs 1 at a time making sure only 1 is ever lit.   
void pushSwitch(){
    //setup for the main button presses
  buttonVal = digitalRead(buttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good delay amount
  buttonVal2 = digitalRead(buttonPin);     // read the input again to check for bounces
  if (buttonVal == buttonVal2) {           // make sure we got 2 consistant readings!
    if (buttonVal != buttonState) {         // the button state has changed!
      if (buttonVal == HIGH) {               // check if the button is pressed
        if (ledState == 0) {          // if its off as when the tilt switch is applied or upon sketh launch
          ledState = 1;               // turn LED1 on
        } else if (ledState == 1) {   // if LED1 is on
            ledState = 2;             // Turn on LED 2
        } else if (ledState == 2) {   // if LED 2 is on
             ledState = 3;           // Turn on LED 3
        } else if (ledState == 3) { // if LED 3 is on 
             ledState = 4;           // turn LED 4 on
        } else if (ledState == 4) { //  if LED 4 is on
             ledState = 1;           // back to LED 1
	}
      }
    }
    buttonState = buttonVal;// save the new state in the button variable
  } 
  //now perform simple tests for each stage of the ledState and light the appropriate LED 
  //while making sure no other bulb can be lit       
  if (ledState == 1) { // LED 1 on all others off
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
  }

  if (ledState == 2) { //LED 2 on all others off
     digitalWrite(led1Pin, LOW);
     digitalWrite(led2Pin, HIGH);
     digitalWrite(led3Pin, LOW);
     digitalWrite(led4Pin, LOW);
  }
  if (ledState == 3)  { //LED 3 on all others off

    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, LOW);
  }  
  if (ledState == 4)  { //LED 4 on all others off
  
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, HIGH);
  }  
}
