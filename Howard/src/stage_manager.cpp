#include "stage_manager.hpp"

StageManager::StageManager(Motor &motor, Line_sensor *line_sensor, Color_sensor *color_sensor, ServoManager *servo_manager, Distance_sensor *distance_sensor) : motor(motor), line_sensor(line_sensor), color_sensor(color_sensor),
                                                                                                                                                                servo_manager(servo_manager), distance_sensor(distance_sensor)
{
    // Initialise first state
    stage = &start_to_home;
    current_stage = "start_to_home";
    // stage = &ramp_2;
    // current_stage = "ramp_2";
};

void StageManager::start_to_home()
{
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Move forward slightly to get out of the starting box
    motor.go_forward(1000);
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    // Transition to next stage after moving forward
    stage = &home_to_ramp_1;
}
void StageManager::home_to_ramp_1()
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
            // Stop for 2 seconds to signify we have reached the 1st junction
            motor.stop();
            delay(2000);
            // Update the starting time for the next stage
            current_stage_start_time = millis();
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

void StageManager::ramp_1()
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
            // Stop for 2 seconds to signify we have reached the 2nd junction
            motor.stop();
            delay(2000);
            // Lower arm and open grabber
            servo_manager->open_grabber();
            servo_manager->lower_arm(40);
            // Line follow for 1750ms
            color_init = color_sensor->get_reading();
            Serial.print("Before colour: ");
            Serial.println(color_init);
            // Update the starting time for the next stage
            current_stage_start_time = millis();
            stage = &ramp_1_to_block;
        }
    }
}

void StageManager::ramp_1_to_block()
{
    current_stage = "ramp_1_to_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    if (millis() - current_stage_start_time <= 1750)
    {
        this->motor.Line_following(line_readings, false);
    }
    else
    {
        // Transition to next stage when 3000ms has passed
        // Update the starting time for the next stage
        current_stage_start_time = millis();
        stage = &stop_and_open_grabber;
    }
    /*
    if (!this->motor.Line_following(line_readings, false))
    {

        float distance = distance_sensor->get_distance();
        // Transition to next stage when distance sensor is 10cm away from block
        if (distance < 10)
        {
            stage = &stop_and_open_grabber;
        }

        if (line_readings == 0b00000110 || line_readings == 0b00000111 || line_readings == 0b00000011 || line_readings == 0b00000101)
        {
            // Update the starting time for the next stage
            current_stage_start_time = millis();
            stage = &stop_and_open_grabber;
        }
    }
    */
    // this->motor.turn_180();
    // delay(10000);
}

void StageManager::stop_and_open_grabber()
{
    current_stage = "stop_and_open_grabber";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    if (millis() - current_stage_start_time <= 3200)
    {
        int color_after = color_sensor->get_reading();
        Serial.print("After color: ");
        Serial.println(color_after);
        if (color_after > color_init + 25)
        {
            is_red_block = true;
            // Flash red
            digitalWrite(RED_LED_PIN, HIGH);
            digitalWrite(GREEN_LED_PIN, LOW);
            delay(6000);
            digitalWrite(RED_LED_PIN, LOW);
            digitalWrite(GREEN_LED_PIN, LOW);
        }
        else
        {
            is_red_block = false;
            // Flash green
            digitalWrite(RED_LED_PIN, LOW);
            digitalWrite(GREEN_LED_PIN, HIGH);
            delay(6000);
            digitalWrite(RED_LED_PIN, LOW);
            digitalWrite(GREEN_LED_PIN, LOW);
        }
    }
    else
    {
        // Update the starting time for the next stage
        current_stage_start_time = millis();
        // Transition to next stage when grabber has been opened
        stage = &pick_block;
    }
    // servo_manager->open_grabber();
    // servo_manager->lower_arm();
}

void StageManager::pick_block()
{
    current_stage = "pick_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");

    servo_manager->lift_arm();
    delay(1000);
    servo_manager->lower_arm();
    // delay(1000);
    // servo_manager->open_grabber();
    delay(1000);
    servo_manager->close_grabber();
    delay(1000);
    servo_manager->lift_arm();
    /*
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
    */
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    // Transition to next stage when block has been picked up
    stage = &turning_at_block;
}

void StageManager::turning_at_block()
{
    current_stage = "turning_at_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Turn 180 degrees
    this->motor.turn_180();
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    stage = &ramp_2;
    // Transition when turned
}

void StageManager::block_to_ramp_2()
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
            // Update the starting time for the next stage
            current_stage_start_time = millis();
            stage = &ramp_2;
        }
    }
}

void StageManager::ramp_2()
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
            this->motor.go_forward(1200);

            // Turn left or right
            if (is_red_block)
            {
                this->motor.turn_right_90();
                motor.go_forward(1000);
            }
            else
            {
                this->motor.turn_left_90();
                motor.go_forward(1000);
            }
            // Update the starting time for the next stage
            current_stage_start_time = millis();
            stage = &drive_to_zone;

            // stage = &finish;
        }
    }
    // Detect junction, then go forward slightly
    // Depending on colour of block, turn left or right
    // Transition when turn is complete
}

void StageManager::drive_to_zone()
{
    current_stage = "drive_to_zone";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Line following for x seconds
    if (millis() - current_stage_start_time <= 1500)
    {
        this->motor.Line_following(line_readings, false);
    }
    if (millis() - current_stage_start_time >= 1501)
    {
        // Stop and drop box
        motor.stop();
        delay(1000);
        servo_manager->lower_arm();
        delay(1000);
        servo_manager->open_grabber();
        delay(1000);
        servo_manager->lift_arm();
        delay(1000);
    }
    /*
    // Then go forward (timed) to position block in drop off zone
    this->motor.go_forward(1500);
    // Drop off block
    servo_manager->lower_arm();
    servo_manager->open_grabber();
    */
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    // Transition when block has been dropped off
    stage = &zone_to_home;
}

void StageManager::zone_to_home()
{
    current_stage = "zone_to_home";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    // Drive back (timed)
    this->motor.go_backward(1600);
    // Rotation left/ right depending on block's colour
    if (is_red_block)
    {
        this->motor.turn_left_90();
    }
    else
    {
        this->motor.turn_right_90();
    }
    // Go forward (timed)
    this->motor.go_forward(2500);
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    Serial.print("Finish!!");
    // Stop and finish
}

void StageManager::finish()
{
    current_stage = "finish";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");
    motor.stop();
    digitalWrite(MOVING_LED_PIN, LOW); // Set the moving LED off
    Serial.print("Finish!!");
}

void StageManager::loop()
{
    // Read from line sensors
    line_readings = line_sensor->get_line_readings();
    // This will call the function stored in the function pointer stage
    (this->*stage)();
}