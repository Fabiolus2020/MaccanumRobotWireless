//Fabiolus 2021/07/23
//the_fabiolous@hotmail.com
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//data being sent to the receiver, joystick position, pot values and button count.
struct package
{
  int joyposX;
  int joyposY;
  int potValue;
  int stateNum;
  int SideWayRightState;
  int SideWayLeftState;
  int ForwardRightState;
  int ForwardLeftState;
  int BackwardRightState;
  int BackwardLeftState;
};


//define object for wieless communication
typedef struct package Package;
Package data;

// Define Joystick Connections
#define joyY A0
#define joyX A1

// Define Joystick Values - Start at 512 (middle position) this might change depending on batteries and motor type.
int joyposX = 512;
int joyposY = 512;
//int modeCount;

//defining joystick button followed by declaring variables and build mechanical state machine to keep count of joystick and have 3 modes
const int buttonPin  = 7;
int buttonState      = 0;     // current state of the button
int lastButtonState  = 0;     // previous state of the button
int modeState        = 0;     // remember current led state
int stateNum;

//LED pin only two modes for this robot
#define ledModeStatusCount A3


// Set initial motor speed at 0
int motorspeedModeOne = 0;
int motorspeedModeTwo = 0;

// Set button for diagonal mode drive, upon pushing button specific direction is iniated.
#define buttonSideWayRight 0
#define buttonSideWayLeft 6
#define buttonForwardRight 2
#define buttonForwardLeft 3
#define buttonBackwardRight 4
#define buttonBackwardLeft 5

int SideWayRightState;
int SideWayLeftState;
int ForwardRightState;
int ForwardLeftState;
int BackwardRightState;
int BackwardLeftState;


//Define potentiometer
#define Pot A2
int potValue = 0;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //define Radio as object
  myRadio.begin();

  //set the address
  myRadio.openWritingPipe(address);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  myRadio.setChannel(115);

  //Set module as transmitter
  myRadio.stopListening();

  pinMode(ledModeStatusCount, OUTPUT);
  digitalWrite(ledModeStatusCount, LOW);
  //joystick select/push button
  pinMode(buttonPin, INPUT_PULLUP);  // initialize the button pin as a input

  pinMode(buttonSideWayRight, INPUT_PULLUP);
  pinMode(buttonSideWayLeft, INPUT_PULLUP);
  pinMode(buttonForwardRight, INPUT_PULLUP);
  pinMode(buttonForwardLeft, INPUT_PULLUP);
  pinMode(buttonBackwardRight, INPUT_PULLUP);
  pinMode(buttonBackwardLeft, INPUT_PULLUP);
  delay(10);

}

void loop() {
  //prepare to capture data to pass wirelessly using data for identifier.
  myRadio.write(&data, sizeof(data));

  // read the pushbutton input pin
  buttonState = digitalRead(buttonPin);
  // check if the button is pressed or released
  // by comparing the buttonState to its previous state, this is the best I could get to being bulletproof and no debouning effect using joystick
  if (buttonState != lastButtonState) {

    // change the state of the led when someone pressed the button
    if (buttonState == 0) {
      data.stateNum++;
      if (data.stateNum > 2) data.stateNum = 0;
    }

    // remember the current state of the button
    lastButtonState = buttonState;
  }

  data.joyposX = analogRead(joyX);
  data.joyposY = analogRead(joyY);
  data.potValue = analogRead(Pot);

  // Serial.print(data.joyposX);
  // Serial.println("joyposX");
  // Serial.println(data.joyposY);
  // Serial.println("joyposY");
  // Serial.println(data.potValue);
  //Serial.println(data.stateNum);

  if (digitalRead(buttonSideWayRight) == LOW) {
    data.SideWayRightState = 0;
  }
  else {
    data.SideWayRightState = 1;
  }
  if (digitalRead(buttonSideWayLeft) == LOW) {
    data.SideWayLeftState = 0;
  }
  else {
    data.SideWayLeftState = 1;
  }
  if (digitalRead(buttonForwardRight) == LOW) {
    data.ForwardRightState = 0;
  }
  else {
    data.ForwardRightState = 1;
  }
  if (digitalRead(buttonForwardLeft) == LOW) {
    data.ForwardLeftState = 0;
  }
  else {
    data.ForwardLeftState = 1;
  }
  if (digitalRead(buttonBackwardRight) == LOW) {
    data.BackwardRightState = 0;
  }
  else {
    data.BackwardRightState = 1;
  }
  if (digitalRead(buttonBackwardLeft) == LOW) {
    data.BackwardLeftState = 0;
  }
  else {
    data.BackwardLeftState = 1;
  }

    Serial.println(data.SideWayRightState);
   Serial.println(data.SideWayLeftState);
   Serial.println(data.ForwardRightState);
   Serial.println(data.ForwardLeftState);
   Serial.println(data.BackwardRightState);
   Serial.println(data.BackwardLeftState);

}
