#ifndef SENSORS_H
#define SENSORS_H

#include "constants.hpp"

class Line_sensor{
    public:
        // Constructor
        Line_sensor();
        uint8_t get_line_readings();
        
    private:

};

class Distance_sensor{
    public:
        Distance_sensor();
        float get_distance();
    private:
        bool initialised_distance_sensor;
};

class Color_sensor{
    public:
        Color_sensor();
        int get_reading();
        bool is_red();
        bool is_red_while_approaching(Distance_sensor *distance_sensor);
    private:
};

#endif
