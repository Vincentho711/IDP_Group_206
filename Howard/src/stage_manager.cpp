#include "stage_manager.hpp"

StageManager::StageManager(Motor &motor) : motor(motor)
{
    // Initialise first state
    stage = &home_to_ramp_1;
    current_stage = "home_to_ramp";
};

void StageManager::home_to_ramp_1(uint8_t line_readings)
{
    // Execute Line following until it returns False
    /*
    this->motor.go_forward();
    delay(5000);
    stage = &ramp_1;
    */

    if (!(this->motor.Line_following(line_readings)))
    {
        // Transition to ramp_1 stage
        stage = &ramp_1;
        current_stage = "ramp_1";
    }
}

void StageManager::ramp_1(uint8_t line_readings)
{
    // Do someting
}

void StageManager::loop(uint8_t line_readings)
{
    // This will call the function stored in the function pointer stage
    (this->*stage)(line_readings);
}