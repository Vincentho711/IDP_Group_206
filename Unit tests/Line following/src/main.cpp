#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>

#define leftIR A0
#define MiddleIR A3
#define RightIR A2
#define IRthresh 200
#define IRmargin 50

#define SpeedStraight 200
#define RotationSpeedLow 0
#define RotationSpeedHigh 255

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);

bool digLeft = false;
bool digMiddle = true;
bool digRight = false;

int no_read_counter = 0;


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

  Serial.print("Ana:");
  Serial.print(anaLeft);
  Serial.print("\t");
  Serial.print(anaMiddle);
  Serial.print("\t");
  Serial.print(anaRight);
  Serial.print("\n");

  Serial.print("Dig:");
  Serial.print(digLeft);
  Serial.print(digMiddle);
  Serial.print(digRight);
  Serial.print("\n");

  Serial.print("-----------------");
  Serial.print("\n");
  //digMiddle = 1;
  
 if (digLeft==0 && digMiddle==1 && digRight==0) {
    Serial.print("Drive_forward\n");
    leftMotor->run(FORWARD);
    leftMotor->setSpeed(SpeedStraight);
    rightMotor->run(FORWARD);
    rightMotor->setSpeed(SpeedStraight);  
  }
  else if (digLeft==1 && digRight==0) {
    Serial.print("Drive_right\n");
    leftMotor->run(FORWARD);
    leftMotor->setSpeed(RotationSpeedLow);
    rightMotor->run(FORWARD);
    rightMotor->setSpeed(RotationSpeedHigh);
  }

  else if (digLeft==0 && digRight==1) {
    Serial.print("Drive_left\n");
    leftMotor->run(FORWARD);
    leftMotor->setSpeed(RotationSpeedHigh);
    rightMotor->run(FORWARD);
    rightMotor->setSpeed(RotationSpeedLow);
  }

  else{
    no_read_counter++;
    if(no_read_counter<5)
    {
      Serial.print("Drive_forward\n");
      leftMotor->run(FORWARD);
      leftMotor->setSpeed(SpeedStraight);
      rightMotor->run(FORWARD);
      rightMotor->setSpeed(SpeedStraight); 
    }else{
      leftMotor->run(RELEASE);
      leftMotor->setSpeed(0);
      rightMotor->run(RELEASE);
      rightMotor->setSpeed(0);
      no_read_counter = 0;
    }
    
  }
}