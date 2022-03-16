#include "stage_manager.hpp"

StageManager::StageManager(Motor &motor, Line_sensor *line_sensor, Color_sensor *color_sensor, Distance_sensor *distance_sensor) : motor(motor), line_sensor(line_sensor), color_sensor(color_sensor),
                                                                                                                                                                distance_sensor(distance_sensor)
{
    // Initialise first state
    stage = &start_to_home;
    is_red_block = false;
    block_colour = 'w';
    // stage = &ramp_2;
    current_stage = "start_to_home";
    keep_line_following = true;
    // stage = &ramp_2;
    // current_stage = "ramp_2";
};

void StageManager::attach_servos(Servo &vertServo, Servo &horiServo)
{
    vert_servo = vertServo;
    hori_servo = horiServo;
}

void StageManager::open_grabber()
{
    Serial.print("Opening grabber. \n");
    // Sweep from close to open grabber
    for (int angle = GRABBER_CLOSE_ANGLE; angle <= GRABBER_OPEN_ANGLE; angle += 1)
    {
        hori_servo.write(angle);
        delay(10);
    }
}

void StageManager::close_grabber()
{
    Serial.print("Closing grabber. \n");
    // And back from open to close grabber
    for (int angle = GRABBER_OPEN_ANGLE; angle >= GRABBER_CLOSE_ANGLE; angle -= 1)
    {
        hori_servo.write(angle);
        delay(10);
    }
}

void StageManager::lift_arm()
{
    Serial.print("Lifting arm. /n");
    // Sweep from down to up angle
    for (int angle = LIFTER_DOWN_ANGLE; angle <= LIFTER_UP_ANGLE; angle += 1)
    {
        vert_servo.write(angle);
        delay(10);
    }
}

void StageManager::lower_arm(int down_angle = LIFTER_DOWN_ANGLE)
{
    Serial.print("Lowering arm. /n");
    // Sweep from up to down angle
    for (int angle = LIFTER_UP_ANGLE; angle >= down_angle; angle -= 1)
    {
        {
            vert_servo.write(angle);
            delay(10);
        }
    }
}

void StageManager::test_servo()
{
    open_grabber();
    delay(1000);
    close_grabber();
    delay(1000);
    lift_arm();
    delay(1000);
    lower_arm();
    delay(1000);
}
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
            Serial.println("IN ramp_1 if ......");
            // Move forward slightly to prevent double detection of junction before transition
            motor.go_forward(250);
            // Stop for 2 seconds to signify we have reached the 2nd junction
            motor.stop();
            delay(2000);
            // Lower arm and open grabber
            open_grabber();
            delay(1000);
            lower_arm(30);
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
    if (keep_line_following)
    {
        motor.Line_following(line_readings, false, 200);
        if (distance_sensor->get_distance() < 5.0)
        {
            keep_line_following = false;
        }
    }
    else
    {
        motor.stop();
        // Transition to next stage when 3000ms has passed
        // Update the starting time for the next stage
        current_stage_start_time = millis();
        stage = &stop_and_open_grabber;
    }
    /*
    if (millis() - current_stage_start_time <= 1950)
    {
        this->motor.Line_following(line_readings, false);
        distance_sensor->get_distance();
    }
    else
    {
        motor.stop();
        // Transition to next stage when 3000ms has passed
        // Update the starting time for the next stage
        current_stage_start_time = millis();
        stage = &stop_and_open_grabber;
    }
    */
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
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    // Transition to next stage when grabber has been opened
    stage = &pick_block;
    // servo_manager->open_grabber();
    // servo_manager->lower_arm();
}

void StageManager::pick_block()
{
    current_stage = "pick_block";
    Serial.print("Mode: ");
    Serial.print(this->current_stage + "\n");

    lift_arm();
    delay(1000);
    lower_arm();
    // delay(1000);
    // servo_manager->open_grabber();
    delay(500);
    motor.go_forward(200);
    motor.stop();
    delay(500);
    close_grabber();
    delay(1000);
    lift_arm();
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
    // Go forward slightly
    this->motor.go_forward(200);
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
            motor.stop();
            delay(1000);
            // Turn left or right
            if (is_red_block)
            {
                this->motor.go_forward(1500);
                motor.stop();
                delay(1000);
                this->motor.pivot_right_turn_90(1000);
                block_colour = 'r';
                motor.stop();
                delay(1000);
            }
            else
            {
                this->motor.go_forward(1500);
                motor.stop();
                delay(1000);
                this->motor.pivot_left_turn_90(1300);
                block_colour = 'b';
                motor.stop();
                delay(1000);
            }
            delay(2000);
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
    int forward_duration;
    if (is_red_block){
        forward_duration = 2000;
    }
    else {
        forward_duration = 2300;
    }
    if (millis() - current_stage_start_time <= forward_duration)
    {
        this->motor.Line_following(line_readings, false, 110, 0.7);
    }
    if (millis() - current_stage_start_time >= forward_duration+1)
    {
        // Stop and drop box
        motor.stop();
        delay(1000);
        lower_arm();
        delay(1000);
        open_grabber();
        delay(1000);
        lift_arm();
        delay(1000);

        // Update the starting time for the next stage
        current_stage_start_time = millis();
        // Transition when block has been dropped off
        stage = &zone_to_home;
    }
    /*
    // Then go forward (timed) to position block in drop off zone
    this->motor.go_forward(1500);
    // Drop off block
    servo_manager->lower_arm();
    servo_manager->open_grabber();
    */
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
    this->motor.go_forward(1500);
    // Update the starting time for the next stage
    current_stage_start_time = millis();
    stage = &finish;
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
    line_readings = line_sensor->get_line_readings(block_colour);
    // This will call the function stored in the function pointer stage
    (this->*stage)();
}