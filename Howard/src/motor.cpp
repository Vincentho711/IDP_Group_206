#include <motor.hpp>

Motor::Motor()
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    left_motor = AFMS.getMotor(LEFT_MOTOR_PIN);
    right_motor = AFMS.getMotor(RIGHT_MOTOR_PIN);
};

bool Motor::Line_following(uint8_t line_readings) {

    bool no_readings = false;

    if (line_readings == 0b01000000) {
        Serial.print("Drive_forward\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(FORWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);  
        no_readings = false;
    }
    else if (line_readings == 0b11000000 || line_readings == 0b10000000) {
        Serial.print("Drive_right\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(ROTATION_SPEED_LOW);
        right_motor->run(FORWARD);
        right_motor->setSpeed(ROTATION_SPEED_HIGH);
        no_readings = false;
    }

    else if (line_readings == 0b01100000 || line_readings == 0b00100000) {
        Serial.print("Drive_left\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(ROTATION_SPEED_HIGH);
        right_motor->run(FORWARD);
        right_motor->setSpeed(ROTATION_SPEED_LOW);
        no_readings = false;
    }

    else if (line_readings == 0b00000000) {
        if (no_readings) {
            left_motor->run(RELEASE);
            left_motor->setSpeed(0);
            right_motor->run(RELEASE);
            right_motor->setSpeed(0);
            return false;
        }
        else {
            left_motor->run(FORWARD);
            left_motor->setSpeed(STRAIGHT_SPEED);
            right_motor->run(FORWARD);
            right_motor->setSpeed(STRAIGHT_SPEED); 
            delay(2000);
            no_readings = true;
        }
        
    }

    // Junction detection
    else {
        Serial.print("Junction detected\n");
        left_motor->run(RELEASE);
        left_motor->setSpeed(0);
        right_motor->run(RELEASE);
        right_motor->setSpeed(0);
        return false;
    }

    return true;
}