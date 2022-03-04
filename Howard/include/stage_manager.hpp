#ifndef STAGE_MANAGER_H
#define STAGE_MANAGER_H

#include "constants.hpp"
#include "motor.hpp"

class StageManager
{
public:
    // Constructor
    StageManager(Motor &motor);
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
    // Store motor instance
    Motor motor;

    
};
#endif