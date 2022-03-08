#ifndef STAGE_MANAGER_H
#define STAGE_MANAGER_H

#include "constants.hpp"
#include "motor.hpp"
#include "sensors.hpp"

class StageManager
{
public:
    // Constructor
    StageManager(Motor &motor, Color_sensor *color_sensor, ServoManager &ServoManager);
    // Function pointer of class StageManager for state machine that takes in line readings
    void (StageManager::*stage)(uint8_t);
    // States
    void home_to_ramp_1(uint8_t line_readings);
    void ramp_1(uint8_t line_readings);
    void ramp_1_to_block(uint8_t line_readings);
    void pick_block(uint8_t line_readings);
    void turning_at_block(uint8_t line_readings);
    void block_to_ramp_2(uint8_t line_readings);
    void ramp_2(uint8_t line_readings);
    void drive_to_zone(uint8_t line_readings);
    void zone_to_home(uint8_t line_readings);
    void loop(uint8_t line_readings);
  
private:
    // Keep track of the current stage
    String current_stage;
    // Keep track of the colour of the block
    bool is_red_block;
    // Store motor instance
    Motor motor;
    // Store color sensor instance
    Color_sensor color_sensor;
    // Store servoManager instance
    ServoManager servo_manager;


    
};
#endif