#include "sensors.hpp"

Line_sensor::Line_sensor()
{
    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_MIDDLE_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
    if (LINE_SENSOR_DEBUG)
    {
        Serial.print("Line sensors initiated.\n");
    }
}
uint8_t Line_sensor::get_line_readings(char colour = 'w')
{
    int left_threshold;
    int left_margin;
    int middle_threshold;
    int middle_margin;
    int right_threshold;
    int right_margin;
    switch (colour)
    {
    case 'w':
        left_threshold = LINE_SENSOR_LEFT_THRESHOLD;
        left_margin = LINE_SENSOR_LEFT_MARGIN;
        middle_threshold = LINE_SENSOR_MIDDLE_THRESHOLD;
        middle_margin = LINE_SENSOR_MIDDLE_MARGIN;
        right_threshold = LINE_SENSOR_RIGHT_THRESHOLD;
        right_margin = LINE_SENSOR_RIGHT_MARGIN;
        break;
    case 'r':
        left_threshold = LINE_SENSOR_RED_LEFT_THRESHOLD;
        left_margin = LINE_SENSOR_RED_LEFT_MARGIN;
        middle_threshold = LINE_SENSOR_RED_MIDDLE_THRESHOLD;
        middle_margin = LINE_SENSOR_RED_MIDDLE_MARGIN;
        right_threshold = LINE_SENSOR_RED_RIGHT_THRESHOLD;
        right_margin = LINE_SENSOR_RED_RIGHT_MARGIN;

    default:
        left_threshold = LINE_SENSOR_BLUE_LEFT_THRESHOLD;
        left_margin = LINE_SENSOR_BLUE_LEFT_MARGIN;
        middle_threshold = LINE_SENSOR_BLUE_MIDDLE_THRESHOLD;
        middle_margin = LINE_SENSOR_BLUE_MIDDLE_MARGIN;
        right_threshold = LINE_SENSOR_BLUE_RIGHT_THRESHOLD;
        right_margin = LINE_SENSOR_BLUE_RIGHT_MARGIN;
        break;
    }
    
    int anaLeft = analogRead(LINE_SENSOR_LEFT_PIN);
    int anaMiddle = analogRead(LINE_SENSOR_MIDDLE_PIN);
    int anaRight = analogRead(LINE_SENSOR_RIGHT_PIN);

    bool digLeft = 0;
    bool digMiddle = 0;
    bool digRight = 0;

    // Schmitt Trigger
    if (anaLeft >= (left_threshold + left_margin))
    {
        digLeft = 1;
    }
    if (anaLeft <= (left_threshold - left_margin))
    {
        digLeft = 0;
    }

    if (anaMiddle >= (middle_threshold + middle_margin))
    {
        digMiddle = 1;
    }
    if (anaMiddle <= (middle_threshold - middle_margin))
    {
        digMiddle = 0;
    }

    if (anaRight >= (right_threshold + right_margin))
    {
        digRight = 1;
    }
    if (anaRight <= (right_threshold - right_margin))
    {
        digRight = 0;
    }

    // Parse onto line_reading
    uint8_t line_reading = 0x00;
    // Set bit 2 to digLeft
    line_reading |= digLeft << 2;
    // Set bit 1 to digMiddle
    line_reading |= digMiddle << 1;
    // Set bit 0 to digRight
    line_reading |= digRight << 0;

    if (LINE_SENSOR_DEBUG)
    {
        Serial.print("Ana:");
        Serial.print(anaLeft);
        Serial.print("\t");
        Serial.print(anaMiddle);
        Serial.print("\t");
        Serial.print(anaRight);
        Serial.print("\n");

        Serial.print("Dig:");
        Serial.print(digLeft);
        Serial.print(digMiddle);
        Serial.print(digRight);
        Serial.print("\n");

        Serial.print("-----------------");
        Serial.print("\n");

        // little delay so we can read the output
        delay(200);
    }

    if (LINE_SENSOR_DEBUG)
    {
        Serial.println(line_reading);
        delay(100);
    }
    return line_reading;
}


Color_sensor::Color_sensor()
{
    pinMode(COLOR_SENSOR_PIN, INPUT);
}

int Color_sensor::get_reading()
{
    return analogRead(COLOR_SENSOR_PIN);
}

bool Color_sensor::is_red()
{
    int reading;
    int last_reading = 0;

    int count = 0;
    while(count<10) // Check for 10 seconds
    {
        reading = analogRead(COLOR_SENSOR_PIN);
        Serial.println("...");
        delay(1000);
        if (reading>last_reading+15 && last_reading!=0) {
            Serial.println("Red detected");
            return true;
        }
        last_reading = reading;
        count ++;
    }
    Serial.println("Red not detected");
    return false;

}

bool Color_sensor::is_red_while_approaching(Distance_sensor *distance_sensor) {
    int reading;
    int last_reading = 0;
    float distance = distance_sensor->get_distance();
    bool is_red;
    int count = 0;
    while(distance > 30)
    {
        distance = distance_sensor->get_distance();
        reading = analogRead(COLOR_SENSOR_PIN);
        Serial.println("...");
        delay(1000);
        if (reading>last_reading+15 && last_reading!=0) {
            Serial.println("Red detected");
            is_red = true;
        }
        last_reading = reading;
        count ++;
    }
    Serial.println("Red not detected");
    is_red = false;
    return is_red;

}

Distance_sensor::Distance_sensor() {
    initialised_distance_sensor = true;
}

float Distance_sensor::get_distance() {

    long duration;
    float distance;

    // Clears the trigPin condition
    digitalWrite(DISTANCE_SENSOR_TRIG_PIN, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(DISTANCE_SENSOR_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(DISTANCE_SENSOR_TRIG_PIN, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(DISTANCE_SENSOR_ECHO_PIN, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm \n");

    return distance;
}