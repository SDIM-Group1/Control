#include <Servo.h>
#define joyX A0

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int angle = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  angle = analogRead(joyX);
  angle = map(angle, 0, 1023, 0, 179);  //scaling the value to legal angle value

  myservo.write(angle);
  delay(5);
}
