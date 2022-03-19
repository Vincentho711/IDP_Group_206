// Include the servo library:
#include <Arduino.h>
#include <Servo.h>
// Create a new servo object:
Servo myservo;
// Define the servo pin:
#define servoPin 9
// Create a variable to store the servo position:
int angle = 10;
int openCount = 0;
int closeCount = 0;
void setup()
{
  // Attach the Servo variable to a pin:
  myservo.attach(servoPin);
  Serial.begin(9600);
}
void loop()
{
  /*
    // Tell the servo to go to a particular angle:
    myservo.write(90);
    delay(1000);
    myservo.write(180);
    delay(1000);
    myservo.write(0);
    delay(1000);
  */
  /*
  // Sweep from 0 to 120 degrees:
  for (angle = 50; angle <= 105; angle += 1) {
    myservo.write(angle);
    Serial.println(angle);
    delay(50);
  }
  openCount++;
  // And back from 120 to 0 degrees:
  for (angle = 105; angle >= 50; angle -= 1) {
    myservo.write(angle);
    Serial.println(angle);
    delay(50);
  }
  closeCount++;
  Serial.print("Opened: ");
  Serial.println(openCount);
  Serial.print("Closed: ");
  Serial.println(closeCount);
  delay(200);
  */

  Serial.print("Lifting arm. /n");
  // Sweep from down to up angle
  for (int angle = 60; angle <= 125; angle += 1)
  {
    myservo.write(angle);
    delay(10);
  }

  delay(3000);
  Serial.print("Lowering arm. /n");
  // Sweep from up to down angle
  for (int angle = 125; angle >= 60; angle -= 1)
  {
      myservo.write(angle);
      delay(10);
  }
  delay(3000);
}