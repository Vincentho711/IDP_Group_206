#ifndef STAGE_MANAGER_H
#define STAGE_MANAGER_H

#include "constants.hpp"
#include "motor.hpp"
#include "sensors.hpp"

class StageManager
{
public:
    // Constructor
    StageManager(Motor &motor, Line_sensor *line_sensor, Color_sensor *color_sensor, ServoManager *ServoManager, Distance_sensor *distance_sensor);
    // Function pointer of class StageManager for state machine that takes in line readings
    void (StageManager::*stage)();
    // States
    void start_to_home();
    void home_to_ramp_1();
    void ramp_1();
    void ramp_1_to_block();
    void stop_and_open_grabber();
    void pick_block();
    void turning_at_block();
    void block_to_ramp_2();
    void ramp_2();
    void drive_to_zone();
    void zone_to_home();
    void finish();
    void loop();

private:
    // Keep track of the current stage
    String current_stage;
    // Keep track of starting time of the current stage
    unsigned long current_stage_start_time;
    // Keep track of line readings
    uint8_t line_readings;
    // Keep track of the colour of the block
    bool is_red_block;
    // Store motor instance
    Motor motor;
    // Store line sensor instance
    Line_sensor *line_sensor;
    // Store color sensor instance
    Color_sensor *color_sensor;
    // Store servoManager instance
    ServoManager *servo_manager;
    // Store distance sensor instance
    Distance_sensor *distance_sensor;
    // Store initial color sensor reading
    int color_init;
    // For distance sensing while line following
    bool keep_line_following;
    // Store the char of the colour of the block
    char block_colour;
};
#endif