#ifndef MOTOR_H
#define MOTOR_H
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include "constants.hpp"

class Motor
{
public:
    Motor();
    bool Line_following(uint8_t line_readings);
    void go_forward();

private:
    Adafruit_MotorShield *motorShield;
    Adafruit_DCMotor *left_motor;
    Adafruit_DCMotor *right_motor;
    bool motor_shield_found = false;
    
};

#endif