#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <SPI.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Initiliase motor object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void loop() {
    // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->run(FORWARD);
  leftMotor->setSpeed(255);
  rightMotor->run(FORWARD);
  rightMotor->setSpeed(255);

}