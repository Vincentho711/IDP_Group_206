#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>

#define ROTATION_TIME 3000
#define RotationSpeedLow 30
#define RotationSpeedHigh 100

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void turn_left_90(Adafruit_DCMotor *leftM, Adafruit_DCMotor *rightM){
  leftM->run(FORWARD);
  rightM->run(FORWARD);
  leftM->setSpeed(RotationSpeedLow);
  rightM->setSpeed(RotationSpeedHigh);
  delay(ROTATION_TIME);
}

void turn_right_90(Adafruit_DCMotor *leftM, Adafruit_DCMotor *rightM){
  leftM->run(FORWARD);
  rightM->run(FORWARD);
  leftM->setSpeed(RotationSpeedHigh);
  rightM->setSpeed(RotationSpeedLow);
  delay(ROTATION_TIME);
}

void turn_180(Adafruit_DCMotor *leftM, Adafruit_DCMotor *rightM){
  turn_right_90(leftM, rightM);
  leftM->run(BACKWARD);
  rightM->run(BACKWARD);
  leftM->setSpeed(30);
  rightM->setSpeed(30);
  delay(2000);
  turn_right_90(leftM, rightM);
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  
  turn_left_90(leftMotor, rightMotor);

  exit(0);

}