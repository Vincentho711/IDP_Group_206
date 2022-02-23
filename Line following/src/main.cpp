#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>

#define leftIR A0
#define MiddleIR A1
#define RightIR A2
#define IRthresh 250
#define IRmargin 50

#define SpeedStraight 150
#define RotationSpeedLow 80
#define RotationSpeedHigh 100

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

bool digLeft = false;
bool digMiddle = true;
bool digRight = false;




void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  pinMode(leftIR, INPUT);
  pinMode(MiddleIR, INPUT);
  pinMode(RightIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int anaLeft = analogRead(leftIR);
  int anaMiddle = analogRead(MiddleIR);
  int anaRight = analogRead(RightIR);

  if (anaLeft >= (IRthresh + IRmargin)) {
    digLeft = true;
  }
  if (anaLeft <= (IRthresh - IRmargin)) {
    digLeft = false;
  }

  if (anaMiddle >= (IRthresh + IRmargin)) {
    digMiddle = true;
  }
  if (anaMiddle <= (IRthresh - IRmargin)) {
    digMiddle = false;
  }

  if (anaRight >= (IRthresh + IRmargin)) {
    digRight = true;
  }
  if (anaRight <= (IRthresh - IRmargin)) {
    digRight = false;
  }

  // Serial.println("left:");
  // Serial.println(anaLeft);
  // Serial.println(digLeft);

  // Serial.println("middle:");
  // Serial.println(anaMiddle);
  // Serial.println(digMiddle);

  // Serial.println("right:");
  // Serial.println(anaRight);
  // Serial.println(digRight);

  Serial.print(digLeft);
  Serial.print(digMiddle);
  Serial.print(digRight);
  Serial.print("\n");

  delay(1000);
  // if (digLeft==0 && digMiddle==1 && digRight==0) {
  //   leftMotor->setSpeed(SpeedStraight);
  //   rightMotor->setSpeed(SpeedStraight);  
  // }
  // else if (digLeft==1 && digRight==0) {
  //   leftMotor->setSpeed(RotationSpeedLow);
  //   rightMotor->setSpeed(RotationSpeedHigh);
  // }

  // else if (digLeft==0 && digRight==1) {
  //   leftMotor->setSpeed(RotationSpeedLow);
  //   rightMotor->setSpeed(RotationSpeedHigh);
  // }

  // else{
  //   leftMotor->run(RELEASE);
  //   leftMotor->setSpeed(0);
  //   rightMotor->run(RELEASE);
  //   rightMotor->setSpeed(0);
  // }
}