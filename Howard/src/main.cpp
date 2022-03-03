#include <Arduino.h>
#include "sensors.hpp"
#include "motor.hpp"
#include "stage_manager.hpp"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(LEFT_MOTOR_PIN);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(RIGHT_MOTOR_PIN);

Line_sensor *line_sensor;
Color_sensor *color_sensor;
uint8_t line_reading;
Motor motor(leftMotor, rightMotor);
StageManager stage_manager(motor);

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
  
  // motor.go_forward();
  // motor.go_forward_then_stop();
  // motor.turn_right_90();
  // motor.turn_left_90();
  // motor.turn_180();
  // exit(0);
  /*
  while (true){
    line_reading = line_sensor->get_line_readings();
    Serial.print((byte)line_reading + "\n");
  
    if (!motor.Line_following(line_reading))
    {
      break;
    }  
  }
  exit(0);
  */
  // bool return_status = motor.Line_following(line_reading);
  // Serial.print(return_status + "\n");

  // Run with stage manager
  // stage_manager.loop(line_reading);
  line_reading = line_sensor->get_line_readings();
  stage_manager.loop(line_reading);
}