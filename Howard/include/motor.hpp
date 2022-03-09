#ifndef MOTOR_H
#define MOTOR_H
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include "constants.hpp"
#include <Servo.h>

class Motor
{
public:
    Motor(Adafruit_DCMotor *leftMotor, Adafruit_DCMotor *rightMotor);
    bool Line_following(uint8_t line_readings, bool ignore_all_zeroes = false);
    void go_forward(int duration);
    void go_forward();
    void stop();
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
    int no_readings_count;
};

class ServoManager
{
public:
    ServoManager();
    void attach_servos(Servo *vert_servo, Servo *hori_servo);
    void lift_arm();
    void lower_arm();
    void open_grabber();
    void close_grabber();

private:
    Servo *vertServo;
    Servo *horiServo;
    bool initialised_servos;
    bool grabber_closed;
    bool lifter_up;
};

#endif