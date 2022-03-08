#include "motor.hpp"

Motor::Motor(Adafruit_DCMotor *leftMotor, Adafruit_DCMotor *rightMotor) : left_motor(leftMotor), right_motor(rightMotor)
{
    motor_shield_found = true;
};

void Motor::go_forward(int duration)
{
    if (motor_shield_found)
    {
        Serial.print("Going forward.\n");
        left_motor->setSpeed(STRAIGHT_SPEED);
        left_motor->run(FORWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(FORWARD);
        delay(duration);
    }
    else
    {
        Serial.print("Motor shield not found.\n");
    }
}

void Motor::stop()
{
    if (motor_shield_found)
    {
        Serial.print("Stop.\n");
        left_motor->setSpeed(0);
        left_motor->run(RELEASE);
        right_motor->setSpeed(0);
        right_motor->run(RELEASE);
    }
}
void Motor::go_forward_then_stop()
{
    if (motor_shield_found)
    {
        Serial.print("Going forward.\n");
        left_motor->setSpeed(STRAIGHT_SPEED);
        left_motor->run(FORWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(FORWARD);
        delay(3000);
        Serial.print("Stopping now.\n");
        left_motor->setSpeed(0);
        left_motor->run(RELEASE);
        right_motor->setSpeed(0);
        right_motor->run(RELEASE);
        // delay(3000);
    }
    else
    {
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
    }
    else
    {
        Serial.print("Motor shield not found.\n");
    }
}

bool Motor::Line_following(uint8_t line_readings, bool ignore_all_zeroes = false)
{
    if (line_readings == 0b00000010)
    {
        Serial.print("Drive_forward\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(STRAIGHT_SPEED);
        right_motor->run(FORWARD);
        right_motor->setSpeed(STRAIGHT_SPEED);
        no_readings_count = 0;
    }
    else if (line_readings == 0b00000100)
    {
        Serial.print("Drive_right\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(CORRECTION_SPEED_LOW);
        right_motor->run(FORWARD);
        right_motor->setSpeed(CORRECTION_SPEED_HIGH);
        no_readings_count = 0;
    }
    else if (line_readings == 0b00000001)
    {
        Serial.print("Drive_left\n");
        left_motor->run(FORWARD);
        left_motor->setSpeed(CORRECTION_SPEED_HIGH);
        right_motor->run(FORWARD);
        right_motor->setSpeed(CORRECTION_SPEED_LOW);
        no_readings_count = 0;
    }
    else if (line_readings == 0b00000000)
    {
        if (ignore_all_zeroes)
        {
            Serial.print("Ignoring all Zeros.Drive_forward \n");
            left_motor->run(FORWARD);
            left_motor->setSpeed(STRAIGHT_SPEED);
            right_motor->run(FORWARD);
            right_motor->setSpeed(STRAIGHT_SPEED);
            no_readings_count = 0;
        }
        else
        {
            Serial.print("All Zeros. \n");
            if (no_readings_count > 1000)
            {
                Serial.print("Stop NOW.\n");
                left_motor->run(FORWARD);
                left_motor->setSpeed(0);
                right_motor->run(FORWARD);
                right_motor->setSpeed(0);
                no_readings_count = 0;
                return false;
            }
            else
            {
                Serial.print("In else statement. \n");
                left_motor->run(FORWARD);
                left_motor->setSpeed(STRAIGHT_SPEED);
                right_motor->run(FORWARD);
                right_motor->setSpeed(STRAIGHT_SPEED);
                no_readings_count++;
            }
        }
    }
    // Junction detection
    else
    {
        Serial.print("Junction detected\n");
        left_motor->run(RELEASE);
        left_motor->setSpeed(0);
        right_motor->run(RELEASE);
        right_motor->setSpeed(0);
        no_readings_count = 0;
        return false;
    }
    return true;
}

void Motor::turn_left_90()
{
    left_motor->run(RELEASE);
    right_motor->run(FORWARD);
    left_motor->setSpeed(ROTATION_SPEED_LOW);
    right_motor->setSpeed(ROTATION_SPEED_HIGH);
    delay(ROTATION_TIME_90);
    right_motor->run(RELEASE);
    right_motor->setSpeed(0);
}

void Motor::turn_right_90()
{
    left_motor->run(FORWARD);
    right_motor->run(RELEASE);
    left_motor->setSpeed(ROTATION_SPEED_HIGH);
    right_motor->setSpeed(ROTATION_SPEED_LOW);
    delay(ROTATION_TIME_90);
    left_motor->run(RELEASE);
    left_motor->setSpeed(0);
}

void Motor::turn_180()
{
    turn_right_90();
    go_backward(1250);
    turn_right_90();
}

// Servo manager for controlling vertServo (lifting arm) and horiServo (closing grabber)
ServoManager::ServoManager()
{
    initialised_servos = false;
    grabber_closed = false;
};

void ServoManager::attach_servos(Servo *vert_servo, Servo *hori_servo)
{
    vertServo = vert_servo;
    horiServo = hori_servo;
    // Set grabber to close to start off with
    hori_servo->write(GRABBER_CLOSE_ANGLE);
}

void ServoManager::lift_arm()
{
}

void ServoManager::lower_arm()
{
}

void ServoManager::open_grabber()
{
    // Check if grabber is closed first
    if (grabber_closed)
    {
        Serial.print("Opening grabber. \n");
        // Sweep from close to open grabber
        for (int angle = GRABBER_CLOSE_ANGLE; angle <= GRABBER_OPEN_ANGLE; angle += 1)
        {
            horiServo->write(angle);
            delay(10);
        }
        grabber_closed = false;
    }
}

void ServoManager::close_grabber()
{
    if (!grabber_closed)
    {
        Serial.print("Closing grabber. \n");
        // And back from open to close grabber
        for (int angle = GRABBER_OPEN_ANGLE; angle >= GRABBER_CLOSE_ANGLE; angle -= 1)
        {
            horiServo->write(angle);
            delay(10);
        }
        grabber_closed = true;
    }
}