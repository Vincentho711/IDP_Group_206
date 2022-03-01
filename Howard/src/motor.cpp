#include "motor.hpp"

Motor::Motor()
{
    // motorShield = new Adafruit_MotorShield();
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();

    if (!AFMS.begin())
    {
        motor_shield_found = false;
    }
    else
    {
        motor_shield_found = true;
        left_motor = AFMS.getMotor(LEFT_MOTOR_PIN);
        right_motor = AFMS.getMotor(RIGHT_MOTOR_PIN);
    }
};

void Motor::go_forward()
{
    if (motor_shield_found)
    {
        Serial.print("Going forward.\n");
        left_motor->setSpeed(STRAIGHT_SPEED);
        left_motor->run(FORWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(FORWARD);
    }else{
        Serial.print("Motor shield not found.\n");
    }
}

void Motor::go_backward(int duration)
{
    if (motor_shield_found)
    {
        Serial.print("Going backward.\n");
        left_motor->setSpeed(STRAIGHT_SPEED);
        left_motor->run(BACKWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(BACKWARD);
        delay(duration);
    }else{
        Serial.print("Motor shield not found.\n");
    }
}

bool Motor::Line_following(uint8_t line_readings)
{
    bool no_readings = false;

    if (line_readings == 0b00000010) {
        Serial.print("Drive_forward\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(FORWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);
        no_readings = false;
    }
    else if (line_readings == 0b00000110 || line_readings == 0b00000100) {
        Serial.print("Drive_right\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(CORRECTION_SPEED_LOW);
        right_motor->run(FORWARD);
        right_motor->setSpeed(CORRECTION_SPEED_HIGH);
        no_readings = false;
    }

    else if (line_readings == 0b00000011 || line_readings == 0b00000001) {
        Serial.print("Drive_left\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(CORRECTION_SPEED_HIGH);
        right_motor->run(FORWARD);
        right_motor->setSpeed(CORRECTION_SPEED_LOW);
        no_readings = false;
    }

    else if (line_readings == 0b00000000) {
        Serial.print("All Zeros. \n");
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

void Motor::turn_left_90() {
    left_motor->run(FORWARD);
    right_motor->run(FORWARD);
    left_motor->setSpeed(ROTATION_SPEED_LOW);
    right_motor->setSpeed(ROTATION_SPEED_HIGH);
    delay(ROTATION_TIME_90);
}

void Motor::turn_right_90() {
    left_motor->run(FORWARD);
    right_motor->run(FORWARD);
    left_motor->setSpeed(ROTATION_SPEED_HIGH);
    right_motor->setSpeed(ROTATION_SPEED_HIGH);
    delay(ROTATION_TIME_90);
}

void Motor::turn_180() {
    turn_right_90();
    go_backward(3000);
    turn_right_90();
}