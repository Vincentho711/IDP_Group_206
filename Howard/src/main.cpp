#include <Arduino.h>
#include "sensors.hpp"
#include "motor.hpp"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(LEFT_MOTOR_PIN);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(RIGHT_MOTOR_PIN);

Line_sensor *line_sensor;
Color_sensor *color_sensor;
uint8_t line_reading;
Motor motor(leftMotor, rightMotor);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void loop()
{
  // put your main code here, to run repeatedly:
  line_reading = line_sensor->get_line_readings();
  Serial.print(line_reading + "\n");
  motor.go_forward();
  //bool return_status = motor->Line_following(line_reading);
  // Serial.print(return_status + "\n");
}