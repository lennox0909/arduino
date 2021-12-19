/*
  Joystick_Controls_Servo
*/

#include <Servo.h>
Servo xservo;
Servo yservo;

int XServoPin = 9;
int YServoPin = 3;
int X_Angle = 90;
int Y_Angle = 90;

int Joy_X_Pin = A1;
int Joy_Y_Pin = A0;
int Joy_X_Value;
int Joy_Y_Value;
int Joy_Press_Pin = 7; // Press to set Servo angle at 90 Degree


void setup() {
  pinMode(Joy_Press_Pin, INPUT);
  xservo.attach(XServoPin);
  yservo.attach(YServoPin);
  //  Serial.begin(9600);

}

void loop () {

  Joy_X_Value = analogRead(Joy_X_Pin);
  Joy_Y_Value = analogRead(Joy_Y_Pin);


  //  char buf[100];
  //  sprintf(buf, "Joy_X_Value=%d, Joy_Y_Value=%d, X_Angle=%d, Y_Angle=%d", Joy_X_Value, Joy_Y_Value, X_Angle, Y_Angle);
  //  Serial.println(buf);

  if (digitalRead(Joy_Press_Pin) == HIGH) {
    X_Angle = 90;
    Y_Angle = 90;
    xservo.write(X_Angle);
    yservo.write(Y_Angle);
  }

  if (Joy_X_Value > 572 && X_Angle < 180) {
    X_Angle += 1;
    xservo.write(X_Angle);
  }

  if (Joy_X_Value < 452 && X_Angle > 0) {
    X_Angle -= 1;
    xservo.write(X_Angle);
  }

  if (Joy_Y_Value > 572 && Y_Angle < 180) {
    Y_Angle += 1;
    yservo.write(Y_Angle);
  }

  if (Joy_Y_Value < 452 && Y_Angle > 0) {
    Y_Angle -= 1;
    yservo.write(Y_Angle);
  }

  delay(10);
}
