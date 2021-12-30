/*
  https://github.com/AndreaLombardo/L298N
  ----------------------------
  Vcc <=> Arduino Nano 3V3
  I2C slave sender on port 8 (Arduino Nano pin: A4 = SDA; A5 = SCL)
  ----------------------------
  <I2C Slave> Arduino Nano is powered by Jetson Nano: pin 5V <=> 5v ; GND <=> GND
  ----------------------------
  <I2C Master> Raspberry Pi 3B+
*/

#include <Wire.h>

// For single motor instance
//#include <L298N.h>
// For two motors instance at once
#include <L298NX2.h>

// Pin definition
const unsigned int IN1 = 4;
const unsigned int IN2 = 2;
const unsigned int EN1 = 3;
const unsigned int IN3 = 7;
const unsigned int IN4 = 8;
const unsigned int EN2 = 6;


// Create one motor instance
L298NX2 motor(EN1, IN1, IN2, EN2, IN3, IN4);

void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  // Call receiveEvent when data received
  Wire.onReceive(receiveEvent);

  // Used to display information
  Serial.begin(9600);
}

void loop() {
}


// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    int s = Wire.read(); // receive byte as int
    switch (s) {

      case 1:
        motor.forwardA();
        motor.forwardB();
        Serial.println("Direction: Forward");
        Serial.println();

        break;
      case 2:
        motor.backwardA();
        motor.backwardB();
        Serial.println("Direction: Backward");
        Serial.println();
        break;
      case 3:
        motor.forwardA();
        motor.backwardB();
        Serial.println("Direction: Left");
        Serial.println();
        break;
      case 4:
        motor.backwardA();
        motor.forwardB();
        Serial.println("Direction: Right");
        Serial.println();
        break;
      case 0:
        motor.stop();
        Serial.println("STOP");
        Serial.println();
        break;


      default:
        motor.setSpeedA(s);
        motor.setSpeedB(s);
        Serial.print("Speed: ");
        Serial.println(s);

        if (motor.getDirectionA() == 0) {
          motor.forwardA();
          if (motor.getDirectionB() == 0) {
            motor.forwardB();
            Serial.println("Direction: Forward");
            Serial.println();
          }
          if (motor.getDirectionB() == 1) {
            motor.backwardB();
            Serial.println("Direction: Left");
            Serial.println();
          }
        }

        if (motor.getDirectionA() == 1) {
          motor.backwardA();
          if (motor.getDirectionB() == 0) {
            motor.forwardB();
            Serial.println("Direction: Right");
            Serial.println();
          }
          if (motor.getDirectionB() == 1) {
            motor.backwardB();
            Serial.println("Direction: Backward");
            Serial.println();
          }
        }



        //        switch (motor.getDirectionA()) {
        //          case 0:
        //            motor.forwardA();
        //            break;
        //          case 1:
        //            motor.backwardA();
        //            break;
        //        }
        //        switch (motor.getDirectionB()) {
        //          case 0:
        //            motor.forwardB();
        //            break;
        //          case 1:
        //            motor.backwardB();
        //            break;
        //        }
    }
  }

}
