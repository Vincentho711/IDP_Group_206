#include <HCSR04.h>

int triggerPin = 11;
int echoPin = 3;

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  double distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);
  delay(500);
  
}