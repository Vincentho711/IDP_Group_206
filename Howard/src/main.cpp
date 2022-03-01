#include <Arduino.h>
#include "sensors.hpp"
#include "motor.hpp"

Line_sensor *line_sensor;
uint8_t line_reading;
Motor *motor;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  line_reading = line_sensor->get_line_readings();
  Serial.print(line_reading + "\n");
  motor->go_forward();
  // bool return_status = motor->Line_following(line_reading);
  // Serial.print(return_status + "\n");
}