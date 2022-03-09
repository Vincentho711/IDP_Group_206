#include "stage_manager.hpp"

StageManager::StageManager(Motor &motor, Color_sensor *color_sensor, ServoManager *servo_manager, Distance_sensor *Distance_sensor) : motor(motor), color_sensor(color_sensor),
                                                                                                                                      servo_manager(servo_manager), distance_sensor(distance_sensor)
{
    // Initialise first state
    stage = &home_to_ramp_1;
    current_stage = "home_to_ramp_1";
};

void StageManager::home_to_ramp_1(uint8_t line_readings)
{
    // Execute Line following until it returns False
    /*
    this->motor.go_forward();
    delay(5000);
    stage = &ramp_1;
    */
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    if (!this->motor.Line_following(line_readings, false))
    {
        if (line_readings == 0b00000110 || line_readings == 0b00000111 || line_readings == 0b00000011 || line_readings == 0b00000101)
        {
            // Move forward slightly to prevent double detection of junction before transition
            motor.go_forward(250);
            stage = &ramp_1;
        }
    }

    /*
    if (!(this->motor.Line_following(line_readings)))
    {

        // Transition to ramp_1 stage
        stage = &ramp_1;
        current_stage = "ramp_1";
    }
    */
}

void StageManager::ramp_1(uint8_t line_readings)
{
    // Do someting
    current_stage = "ramp_1";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    if (!this->motor.Line_following(line_readings, true))
    {
        // Transition to next stage when it reaches the second junction
        if (line_readings == 0b00000110 || line_readings == 0b00000111 || line_readings == 0b00000011 || line_readings == 0b00000101)
        {
            // Move forward slightly to prevent double detection of junction before transition
            motor.go_forward(250);
            stage = &ramp_1_to_block;
        }
    }
}

void StageManager::ramp_1_to_block(uint8_t line_readings)
{
    current_stage = "ramp_1_to_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Keep line following until we are 10cm away from block
    if (!this->motor.Line_following(line_readings, false))
    {
        float distance = distance_sensor->get_distance();
        // Transition to next stage when distance sensor is 10cm away from block
        if (distance < 10)
        {
            stage = &stop_and_open_grabber;
        }
    }
    // this->motor.turn_180();
    // delay(10000);
}

void StageManager::stop_and_open_grabber(uint8_t line_readings)
{
    current_stage = "stop_and_open_grabber";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Stop first
    motor.stop();
    // Open grabber
    servo_manager->open_grabber();
    servo_manager->lower_arm();
    // Transition to next stage when grabber has been opened
    stage = &pick_block;
}

void StageManager::pick_block(uint8_t line_readings)
{
    current_stage = "pick_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Implement picking logic
    motor.go_forward();
    is_red_block = color_sensor->is_red_while_approaching(distance_sensor);
    motor.stop();
    // Flash LED
    if (is_red_block)
    {
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, LOW);
        delay(6000);
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
    }
    else
    {
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, HIGH);
        delay(6000);
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
    }
    // Engage the claw and lift arm
    servo_manager->close_grabber();
    servo_manager->lift_arm();

    // Transition to next stage when block has been picked up
}

void StageManager::turning_at_block(uint8_t line_readings)
{
    current_stage = "turning_at_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Turn 180 degrees
    this->motor.turn_180();
    stage = &block_to_ramp_2;
    // Transition when turned
}

void StageManager::block_to_ramp_2(uint8_t line_readings)
{
    current_stage = "block_to_ramp_2";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Line following until junction
    if (!this->motor.Line_following(line_readings, false))
    {
        // Transition to next stage when it reaches the third junction
        if (line_readings == 0b00000110 || line_readings == 0b00000111 || line_readings == 0b00000011 || line_readings == 0b00000101)
        {
            // Move forward slightly to prevent double detection of junction before transition
            motor.go_forward(250);
            stage = &ramp_2;
        }
    }
}

void StageManager::ramp_2(uint8_t line_readings)
{
    current_stage = "ramp_2";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Line following
    if (!this->motor.Line_following(line_readings, false))
    {
        // Transition to next stage when it reaches the third junction
        if (line_readings == 0b00000110 || line_readings == 0b00000111 || line_readings == 0b00000011 || line_readings == 0b00000101)
        {
            // Go forward slightly
            this->motor.go_forward(1000);
            stage = &zone_to_home;
        }
    }
    // Detect junction, then go forward slightly
    // Depending on colour of block, turn left or right
    // Transition when turn is complete
}

void StageManager::drive_to_zone(uint8_t line_readings)
{
    // Then go forward (timed) to position block in drop off zone
    // Drop off block
    // Transition when block has been dropped off
}

void StageManager::zone_to_home(uint8_t line_readings)
{
    current_stage = "zone_to_home";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Drive back (timed)
    // Rotation left/ right depending on block's colour
    // Go forward (timed)
    Serial.print("Finish!!");
    // Stop and finish
}

void StageManager::loop(uint8_t line_readings)
{
    // This will call the function stored in the function pointer stage
    (this->*stage)(line_readings);
}