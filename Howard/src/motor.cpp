#include <motor.hpp>

Motor::Motor()
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    left_motor = AFMS.getMotor(LEFT_MOTOR_PIN);
    right_motor = AFMS.getMotor(RIGHT_MOTOR_PIN);
};