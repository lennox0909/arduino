/*
Hard Ware
----------------
Arduino Nano
Relay
Photosenser
Potentiometer
Dual-polar xmas tree led string
*/

int led1 = 3;           // the PWM pin the LED is attached to
int led3 = 6;

int led2 = 9;           // the PWM pin the LED is attached to
int led4 = 11;
int brightness = 0;
int fadeAmount = 1;    // how many points to fade the LED by
int relay_pin = 7;
int Photosenser_value;
int Potentiometer_value;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  //  Serial.begin(9600);

}

void loop() {
  Photosenser_value = analogRead(A0);
  Potentiometer_value = analogRead(A5);

  //  Serial.print("Photosenser_value: ");
  //  Serial.print(Photosenser_value);
  //  Serial.print("\tPotentiometer_value: ");
  //  Serial.println(Potentiometer_value);
  if (Photosenser_value <= Potentiometer_value) {
    digitalWrite(relay_pin, HIGH);
    allfade();
    //    alter();
    //    all();

  } else if (Photosenser_value - 100 > Potentiometer_value) {
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    digitalWrite(relay_pin, LOW);
  }
  delay(4);


}

void alter() {
  analogWrite(led1, 255);
  analogWrite(led2, 0);
  delay(1000);
  analogWrite(led1, 0);
  analogWrite(led2, 255);
  delay(1000);
}

void all() {
  analogWrite(led1, 255);
  analogWrite(led2, 0);
  delay(1);
  analogWrite(led1, 0);
  analogWrite(led2, 255);
  delay(1);
}

void allfade() {
  int _delay = 4;

  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  alterfade1(_delay, brightness);

}

void alterfade1(int _delay, int brightness) {
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);
  analogWrite(led1, brightness);
  analogWrite(led3, brightness);
  delay(_delay);

  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  analogWrite(led2, brightness);
  analogWrite(led4, brightness);
  delay(_delay);
}

//void alterfade2(int _delay, int brightness) {
//  digitalWrite(led1, LOW);
//  //  digitalWrite(led3, LOW);
//  analogWrite(led2, brightness);
//  //  analogWrite(led4, brightness);
//  delay(_delay);
//}
