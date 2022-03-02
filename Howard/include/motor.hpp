#ifndef MOTOR_H
#define MOTOR_H
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include "constants.hpp"

class Motor
{
public:
    Motor(Adafruit_DCMotor *leftMotor, Adafruit_DCMotor *rightMotor);
    bool Line_following(uint8_t line_readings);
    void go_forward();
    void go_forward_then_stop();
    void go_backward(int duration);
    void turn_left_90();
    void turn_right_90();
    void turn_180();

private:
    Adafruit_MotorShield *motorShield;
    Adafruit_DCMotor *left_motor;
    Adafruit_DCMotor *right_motor;
    bool motor_shield_found = false;
    bool no_readings;
    
};

#endif