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
StageManager stage_manager(motor, line_sensor, color_sensor, servo_manager, distance_sensor);

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
  servo_manager->attach_servos(vertServo, horiServo);

  // Distance sensor
  pinMode(DISTANCE_SENSOR_TRIG_PIN, OUTPUT);
  pinMode(DISTANCE_SENSOR_ECHO_PIN, INPUT);

  // lower arm
  // servo_manager->lower_arm();

  digitalWrite(COLOR_SENSOR_WHITE_LED_PIN, HIGH); // sets the white LED on
  digitalWrite(MOVING_LED_PIN, HIGH); // Set the moving LED on

  // Lift arm and close grabber
  servo_manager->lift_arm();
  servo_manager->close_grabber();
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
  /*

  digitalWrite(COLOR_SENSOR_WHITE_LED_PIN, HIGH); // sets the white LED on
  delay(1000);            // waits for a second
  digitalWrite(COLOR_SENSOR_WHITE_LED_PIN, LOW); // sets the white LED on
  delay(1000);
  */
  // line_reading = line_sensor->get_line_readings();
  stage_manager.loop();
  /*
  if (start){
    // Serial.print("Entered loop if statement. \n");
    stage_manager.loop();
    start = 1;
  }
  else
  {
    Serial.print("Entered loop else statement. Stop forever. \n");
    motor.stop();
  }
  
  /*
  servo_manager->lower_arm();
  delay(3000);
  servo_manager->open_grabber();
  delay(2000);
  servo_manager->close_grabber();
  delay(2000);
  servo_manager->lift_arm();
  delay(3000);
  
  // Test LED
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(MOVING_LED_PIN, HIGH);
  delay(3000);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(MOVING_LED_PIN, LOW);
  delay(3000);
  */
  // distance_sensor->get_distance()
  /*
  // lower arm
  Serial.print("lowering arm. \n");
  for (int angle = LIFTER_UP_ANGLE; angle >= LIFTER_DOWN_ANGLE; angle -= 1)
  {
    vertServo->write(angle);
    delay(10);
  }
  delay(1000);
  Serial.print("Lifting arm. /n");
  // Sweep from down to up angle
  for (int angle = LIFTER_DOWN_ANGLE; angle <= LIFTER_UP_ANGLE; angle += 1)
  {
    vertServo->write(angle);
    delay(10);
  }
  */
  // servo_manager->lower_arm();

  // servo_manager->lift_arm();
  // delay(1000);
  // distance_sensor->get_distance();
  /*
  if (start)
  {
    distance_sensor->get_distance();
    // line_reading = line_sensor->get_line_readings();
    //stage_manager.loop(line_reading);
  }
  */

  // motor.turn_right_90();
  // motor.turn_left_90();
  // motor.turn_180();
  // motor.stop();
  // delay(3000);
  // motor.turn_right_90();
  // motor.go_backward(1250);
  // motor.turn_right_90();
  // motor.stop();
  // delay(3000);
  // distance_sensor->get_distance();
  // color_sensor->is_red();
}