#include <Arduino.h>
#define leftIR A0

void setup() {
  // put your setup code here, to run once:
  pinMode(leftIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("\nLeft:");
  Serial.print(analogRead(leftIR));
  delay(1000);
}