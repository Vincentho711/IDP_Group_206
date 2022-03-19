#include <Arduino.h>

int reading;
int last_reading;

void setup() {
  // put your setup code here, to run once:
  pinMode(A4, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(A4);
  delay(1000);
  if (reading>last_reading+15 && last_reading!=0) {
    Serial.println("Red detected");
  }
  last_reading = reading;
  Serial.println(reading);
  Serial.println(last_reading);
}