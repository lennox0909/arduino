/*
  https://github.com/AndreaLombardo/L298N
  L298N_control_DC_Motors

*/

// For single motor instance
#include <L298N.h>
// For two motors instance at once
//#include <L298NX2.h>


// Pin definition
const unsigned int IN1 = 4;
const unsigned int IN2 = 2;
const unsigned int EN = 3;

// Create one motor instance
L298N motor(EN, IN1, IN2);

int speedness = 0;
int speedAmount = 1;

void setup()
{
  // Used to display information
  Serial.begin(9600);

  // Wait for Serial Monitor to be opened
  while (!Serial)
  {
    //do nothing
  }
}

void loop()
{
  // Apply faded speed to both motors
  //  motor.setSpeed(speedness);

  // Tell motor A to go forward (may depend by your wiring)
  //    motor.forward();
  //  motor.backward();

  // Alternative method:
  // motor.run(L298N::FORWARD);

  //print the motor status in the serial monitor
  //  printSomeInfo();

  // Change the "speedness" for next time through the loop:
  //  speedness = speedness + speedAmount;
  for (speedness = 1; speedness < 255; speedness += speedAmount) {
    //    motor.forward();
    motor.setSpeed(speedness);
    //    if (speedness == 0 || speedness == 255)
    //    {
    //      speedAmount = -speedAmount;
    //    }
    motor.forward();
    printSomeInfo();
    delay(30);
  }

  for (speedness = 1; speedness < 255; speedness += speedAmount) {
    motor.setSpeed(speedness);
    //    if (speedness == 0 || speedness == 255)
    //    {
    //      speedAmount = -speedAmount;
    //    }
    motor.backward();
    printSomeInfo();
    delay(30);
  }


  // Reverse the direction of the fading at the ends of the fade:
  //  if (speedness <= 0 || speedness >= 255)
  //  {
  //    speedAmount = -speedAmount;
  //  }

  //  motor.stop();
  // Wait for 30 milliseconds to see the dimming effect
  //  delay(30);

}

/*
  Print some informations in Serial Monitor
*/
void printSomeInfo()
{
  Serial.print("Motor is moving = ");
  Serial.print(motor.isMoving() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motor.getSpeed());
}
