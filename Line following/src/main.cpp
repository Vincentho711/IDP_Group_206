#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>

#define leftIR A0
#define MiddleIR A1
#define RightIR A2
#define IRthresh 400
#define IRmargin 100

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);






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

  bool digLeft;
  bool digMiddle;
  bool digRight;

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

Serial.print("\nleft");
Serial.print(anaLeft,digLeft);
Serial.print("\nmiddle");
Serial.print(anaMiddle,digMiddle);
Serial.print("\nright");
Serial.print(anaRight,digRight);



}