#ifndef MOTOR_H
#define MOTOR_H
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include <constants.hpp>

class Motor{
    public:
    // Attribute
    Adafruit_DCMotor *left_motor;
    Adafruit_DCMotor *right_motor;
    Motor();
    private:
    bool Line_following(uint8_t line_readings);

        
};

#endif