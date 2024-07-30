#include <Servo.h>
#include <math.h>

// Define constants
const int servoPin1 = 6;
const int servoPin2 = 5;
const int servoPin3 = 4;
const int armLength2 = 12; 
const int armLength3 = 4; 
const int h = 6;

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  // Attach servo to its pin
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  Serial.begin(9600);
}

void loop() {
  // Read target coordinates from serial input
  if (Serial.available() > 1) {

    float x = Serial.parseFloat();
    float y = Serial.parseFloat();
    float z = Serial.parseFloat();
    float alpha = atan2(z-h, sqrt(pow(x, 2) + pow(y, 2)));

    float theta1 = atan2(y, x) * 180.0 / PI; 
    float theta2 = acos((pow(x, 2) + pow(y, 2) + pow(z-h, 2) + pow(armLength2, 2) - pow(armLength3, 2)) / (2 * armLength2 * sqrt(pow(x, 2) + pow(y, 2) + pow(z-h, 2)))) + alpha * 180.0 / PI; 
    float theta3 = acos((pow(x, 2) + pow(y, 2) + pow(z-h, 2) - pow(armLength2, 2) - pow(armLength3, 2)) / (2 * armLength2 * armLength3)) * 180.0 / PI;

    servo1.write(theta1);
    servo2.write(theta2);
    servo3.write(theta3);

    // Print angle for debugging
    Serial.print("Target Angle1: ");
    Serial.println(theta1);
    Serial.print("Target Angle2: ");
    Serial.println(theta2);
    Serial.print("Target Angle3: ");
    Serial.println(theta3);
  }

  // Delay for stability
  delay(1000);
}