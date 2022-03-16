#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>
// Debug flags
#define LINE_SENSOR_DEBUG 0

// Start button pin
#define START_BUTTON_PIN 2

// Distance sensor
#define DISTANCE_SENSOR_TRIG_PIN 11
#define DISTANCE_SENSOR_ECHO_PIN 3

// Servos
#define VERT_SERVO_PIN 9
#define HORI_SERVO_PIN 10

// Grabber
#define GRABBER_OPEN_ANGLE 120
#define GRABBER_CLOSE_ANGLE 0

// Arm lifter
#define LIFTER_UP_ANGLE 115
#define LIFTER_DOWN_ANGLE 60

// LEDs
#define MOVING_LED_PIN 6
#define RED_LED_PIN 4
#define GREEN_LED_PIN 5

//Pins
/*
#define LINE_SENSOR_LEFT_PIN A0
#define LINE_SENSOR_MIDDLE_PIN A2
#define LINE_SENSOR_RIGHT_PIN A4
*/
#define LINE_SENSOR_LEFT_PIN A0
#define LINE_SENSOR_MIDDLE_PIN A1
#define LINE_SENSOR_RIGHT_PIN A2
#define COLOR_SENSOR_WHITE_LED_PIN 7
#define COLOR_SENSOR_PIN A4
#define LEFT_MOTOR_PIN 2
#define RIGHT_MOTOR_PIN 1


// Line sensor sentivity
#define LINE_SENSOR_LEFT_THRESHOLD 300
#define LINE_SENSOR_LEFT_MARGIN 50
#define LINE_SENSOR_MIDDLE_THRESHOLD 50
#define LINE_SENSOR_MIDDLE_MARGIN 25
#define LINE_SENSOR_RIGHT_THRESHOLD 100
#define LINE_SENSOR_RIGHT_MARGIN 20

// For red line
# define LINE_SENSOR_RED_LEFT_THRESHOLD 150
#define LINE_SENSOR_RED_LEFT_MARGIN 25
#define LINE_SENSOR_RED_MIDDLE_THRESHOLD 25
#define LINE_SENSOR_RED_MIDDLE_MARGIN 3
#define LINE_SENSOR_RED_RIGHT_THRESHOLD 35
#define LINE_SENSOR_RED_RIGHT_MARGIN 5

// For blue line
# define LINE_SENSOR_BLUE_LEFT_THRESHOLD 200
#define LINE_SENSOR_BLUE_LEFT_MARGIN 50
#define LINE_SENSOR_BLUE_MIDDLE_THRESHOLD 30
#define LINE_SENSOR_BLUE_MIDDLE_MARGIN 10
#define LINE_SENSOR_BLUE_RIGHT_THRESHOLD 60
#define LINE_SENSOR_BLUE_RIGHT_MARGIN 15

// Line following
#define STRAIGHT_SPEED 255
#define CORRECTION_SPEED_LOW 150
#define CORRECTION_SPEED_HIGH 255

// Rotation
#define ROTATION_TIME_90 2500
#define ROTATION_SPEED_LOW 0
#define ROTATION_SPEED_HIGH 255




#endif