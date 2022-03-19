#include <Arduino.h>
#include "sensors.hpp"
#include "motor.hpp"
#include "stage_manager.hpp"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(LEFT_MOTOR_PIN);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(RIGHT_MOTOR_PIN);

Servo vertServo;
Servo horiServo;
ServoManager *servo_manager;
Line_sensor *line_sensor;
Distance_sensor *distance_sensor;
Color_sensor *color_sensor;
Motor motor(leftMotor, rightMotor);
StageManager stage_manager(motor, line_sensor, color_sensor, distance_sensor);

uint8_t line_reading;
bool start = 0;

// Interrupt handler for start button
void set_state()
{
  Serial.print("Start now. \n");
  start = !start;
  delay(200);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Set up start button
  pinMode(START_BUTTON_PIN, INPUT);
  // attachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN), set_state, RISING);

  // Set up the LED pin
  // Moving LED
  pinMode(MOVING_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(COLOR_SENSOR_WHITE_LED_PIN, OUTPUT);

  // Set up motor
  if (!AFMS.begin())
  { // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");

  // Set up servos
  vertServo.attach(VERT_SERVO_PIN);
  horiServo.attach(HORI_SERVO_PIN);

  // Attach configured servos onto servoManager object
  stage_manager.attach_servos(vertServo, horiServo);

  // Servo Manager not used for final competition
  // stage_manager.attach_servo_manager(servo_manager);

  // Distance sensor
  pinMode(DISTANCE_SENSOR_TRIG_PIN, OUTPUT);
  pinMode(DISTANCE_SENSOR_ECHO_PIN, INPUT);

  digitalWrite(COLOR_SENSOR_WHITE_LED_PIN, HIGH); // sets the white LED on
  digitalWrite(MOVING_LED_PIN, HIGH); // Set the moving LED on

  // Lift arm and close grabber
  stage_manager.lift_arm();
  stage_manager.close_grabber();
}

void loop()
{
  // put your main code here, to run repeatedly:
  stage_manager.loop();
}