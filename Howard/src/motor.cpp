#include <motor.hpp>

Motor::Motor()
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    left_motor = AFMS.getMotor(LEFT_MOTOR_PIN);
    right_motor = AFMS.getMotor(RIGHT_MOTOR_PIN);
    if (!AFMS.begin())
    {   // create with the default frequency 1.6KHz
        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Motor Shield found.");
};

bool Motor::Line_following(uint8_t line_readings)
{
    Serial.print("HELLO \n");
    left_motor->run(FORWARD);
    left_motor->setSpeed(STRAIGHT_SPEED);
    right_motor->run(FORWARD);
    this->right_motor->setSpeed(STRAIGHT_SPEED);

    /*
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
        left_motor->setSpeed(ROTATION_SPEED_LOW);
        right_motor->run(FORWARD);
        right_motor->setSpeed(ROTATION_SPEED_HIGH);
        no_readings = false;
    }

    else if (line_readings == 0b00000011 || line_readings == 0b00000001) {
        Serial.print("Drive_left\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(ROTATION_SPEED_HIGH);
        right_motor->run(FORWARD);
        right_motor->setSpeed(ROTATION_SPEED_LOW);
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
    */
    return true;
}