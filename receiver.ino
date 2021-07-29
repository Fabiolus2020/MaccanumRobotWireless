#include <Wire.h>
#include <Adafruit_MotorShield.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

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

typedef struct package Package;
Package data;

// Set initial motor speed at 0
int motorspeedModeOne = 0;
int motorspeedModeTwo = 0;

void setup() {
  Serial.begin(9600);
  AFMS.begin(4000);  // OR with a different frequency, say 4KHz
  while (!Serial);


  myRadio.begin();
  //set the address
  myRadio.openReadingPipe(0, address);
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  //Set module as receiver
  myRadio.startListening();
}

void loop() {
  if ( myRadio.available())
  {
    myRadio.read( &data, sizeof(data) );
    //  Serial.print(data.joyposX);
    //  Serial.println("joyposX");
    //Serial.println(data.joyposY);
    // Serial.println("joyposY");
    // Serial.println(data.potValue);
    // Serial.println(data.stateNum);
    // Serial.println(data.SideWayRightState);
    // Serial.println(data.SideWayLeftState);
    // Serial.println(data.ForwardRightState);
    // Serial.println(data.ForwardLeftState);
    // Serial.println(data.BackwardRightState);
    // Serial.println(data.BackwardLeftState);

    if (data.joyposX < 485)//Going Forward
    {
      if (data.stateNum == 1)
      {
        myMotor1->run(FORWARD);
        myMotor2->run(FORWARD);
        myMotor3->run(FORWARD);
        myMotor4->run(FORWARD);
        motorspeedModeOne = map(data.joyposX, 485, 0, 0, 255);
        myMotor1->setSpeed(motorspeedModeOne);
        myMotor2->setSpeed(motorspeedModeOne);
        myMotor3->setSpeed(motorspeedModeOne);
        myMotor4->setSpeed(motorspeedModeOne);
      }
      else if (data.stateNum == 2)
      {
        myMotor1->run(FORWARD);
        myMotor2->run(FORWARD);
        myMotor3->run(FORWARD);
        myMotor4->run(FORWARD);
        motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
        myMotor1->setSpeed(motorspeedModeTwo);
        myMotor2->setSpeed(motorspeedModeTwo);
        myMotor3->setSpeed(motorspeedModeTwo);
        myMotor4->setSpeed(motorspeedModeTwo);
      }
    }
if (data.joyposX > 600)//Going Backward
  {
    if (data.stateNum == 1)
    {
      myMotor1->run(BACKWARD);
      myMotor2->run(BACKWARD);
      myMotor3->run(BACKWARD);
      myMotor4->run(BACKWARD);
      motorspeedModeOne = map(data.joyposX, 600, 1023, 0, 255);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)//Going Backward
    {
      myMotor1->run(BACKWARD);
      myMotor2->run(BACKWARD);
      myMotor3->run(BACKWARD);
      myMotor4->run(BACKWARD);
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  if (data.joyposY > 600)//Going left
  {
    if (data.stateNum == 1)
    {
      myMotor1->run(BACKWARD);
      myMotor2->run(FORWARD);
      myMotor3->run(BACKWARD);
      myMotor4->run(FORWARD);
      motorspeedModeOne = map(data.joyposY, 600, 1023, 0, 255);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)//Going left
    {
      myMotor1->run(BACKWARD);
      myMotor2->run(FORWARD);
      myMotor3->run(BACKWARD);
      myMotor4->run(FORWARD);
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  if (data.joyposY < 470)//Going right
  {
    if (data.stateNum == 1)
    {
      myMotor1->run(FORWARD);
      myMotor2->run(BACKWARD);
      myMotor3->run(FORWARD);
      myMotor4->run(BACKWARD);
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)//Going right
    {
      myMotor1->run(FORWARD);
      myMotor2->run(BACKWARD);
      myMotor3->run(FORWARD);
      myMotor4->run(BACKWARD);
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  if (data.SideWayRightState == 0) {
    if (data.stateNum == 1)
    {
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor1->run(BACKWARD);
      myMotor2->run(FORWARD);
      myMotor3->run(FORWARD);
      myMotor4->run(BACKWARD);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)
    {
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->run(BACKWARD);
      myMotor2->run(FORWARD);
      myMotor3->run(FORWARD);
      myMotor4->run(BACKWARD);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  if (data.SideWayLeftState == 0) {
    if (data.stateNum == 1)
    {
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor1->run(FORWARD);
      myMotor2->run(BACKWARD);
      myMotor3->run(BACKWARD);
      myMotor4->run(FORWARD);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)
    {
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->run(FORWARD);
      myMotor2->run(BACKWARD);
      myMotor3->run(BACKWARD);
      myMotor4->run(FORWARD);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  if (data.ForwardRightState == 0) {
    if (data.stateNum == 1)
    {
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor1->run(FORWARD);
      myMotor4->run(FORWARD);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)
    {
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->run(FORWARD);
      myMotor4->run(FORWARD);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  else if (data.ForwardLeftState == 0) {
    if (data.stateNum == 1)
    {
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor2->run(FORWARD);
      myMotor3->run(FORWARD);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)
    {
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor2->run(FORWARD);
      myMotor3->run(FORWARD);
      // myMotor4->run(BACKWARD);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
    }
  }
  else if (data.BackwardRightState == 0) {
    if (data.stateNum == 1)
    {
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor2->run(BACKWARD);
      myMotor3->run(BACKWARD);
      myMotor2->setSpeed(motorspeedModeOne);
      myMotor3->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)
    {
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor2->run(BACKWARD);
      myMotor3->run(BACKWARD);
      myMotor2->setSpeed(motorspeedModeTwo);
      myMotor3->setSpeed(motorspeedModeTwo);
    }
  }
  else if (data.BackwardLeftState == 0) {
    if (data.stateNum == 1)
    {
      motorspeedModeOne = map(data.joyposY, 470, 0, 0, 255);
      myMotor1->run(BACKWARD);
      myMotor4->run(BACKWARD);
      myMotor1->setSpeed(motorspeedModeOne);
      myMotor4->setSpeed(motorspeedModeOne);
    }
    else if (data.stateNum == 2)
    {
      motorspeedModeTwo = map(data.potValue, 0, 1023, 0, 255);
      myMotor1->run(BACKWARD);
      myMotor4->run(BACKWARD);
      myMotor1->setSpeed(motorspeedModeTwo);
      myMotor4->setSpeed(motorspeedModeTwo);
    }
  }
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
  }
}
