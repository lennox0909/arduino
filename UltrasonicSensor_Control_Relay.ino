/*
  Two Ultrasonic Sensors control two Relays with Arduino
  Ultrasonic Sensor: HC-SR04
*/

// Pin Setting
const int TRIG_PIN1 = 2;
const int ECHO_PIN1 = 3;
const int TRIG_PIN2 = 4;
const int ECHO_PIN2 = 5;

const int RELAY_PIN1 = 8;
const int RELAY_PIN2 = 9;

float THRESHOLD_DIST = 12.0f; // threshold distance (cm) to trigger Relay reaction

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

//unsigned long start_time1 = 0;
//unsigned long start_time2 = 0;
//unsigned long end_time1 = 0;
//unsigned long end_time2 = 0;
unsigned long pulse_width1;
unsigned long pulse_width2;
float cm1;
float cm2;

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  digitalWrite(TRIG_PIN1, LOW);
  digitalWrite(TRIG_PIN2, LOW);

  pinMode(RELAY_PIN1, OUTPUT);
  digitalWrite(RELAY_PIN1, HIGH); // Relay1 off
  pinMode(RELAY_PIN2, OUTPUT);
  digitalWrite(RELAY_PIN2, HIGH); // Relay2 off

  //Set Echo pin as input to measure the duration of
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN1, INPUT);
  pinMode(ECHO_PIN2, INPUT);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);
}

void loop() {



  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);


  // Wait for pulse on echo pin
  //  while ( digitalRead(ECHO_PIN1) == 0 ) {
  //    // Measure how long the echo pin was held high (pulse width)
  //    // Note: the micros() counter will overflow after ~70 min
  //    start_time1 = micros();
  //  }
  //  while ( digitalRead(ECHO_PIN1) == 1) {
  //    end_time1 = micros();
  //  }
  //  pulse_width1 = end_time1 - start_time1;
  //  cm1 = pulse_width1 / 58.0; // assumed speed of sound in air at sea level (~340 m/s).

  // Reads the echoPin, returns the sound wave travel time in microseconds
  pulse_width1 = pulseIn(ECHO_PIN1, HIGH);
  // Calculating the distance
  cm1 = pulse_width1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)



  if ( pulse_width1 < MAX_DIST ) {
    if ( cm1 < THRESHOLD_DIST && cm1 > 1.5f) {
      if ( digitalRead(RELAY_PIN1) == LOW) {
        digitalWrite(RELAY_PIN1, HIGH);
      } else {
        digitalWrite(RELAY_PIN1, LOW);
      }
    }
  }

  Serial.print("Sensor1: \t");
  Serial.print(cm1);
  Serial.println(" cm \t");



  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);

  //  while ( digitalRead(ECHO_PIN2) == 0 ) {
  //    start_time2 = micros();
  //  }
  //  while ( digitalRead(ECHO_PIN2) == 1) {
  //    end_time2 = micros();
  //  }
  //  pulse_width2 = end_time2 - start_time2;
  //  cm2 = pulse_width2 / 58.0;

  // Reads the echoPin, returns the sound wave travel time in microseconds
  pulse_width2 = pulseIn(ECHO_PIN2, HIGH);
  // Calculating the distance
  cm2 = pulse_width2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.print("Sensor2: \t");
  Serial.print(cm2);
  Serial.println(" cm \t");



  if ( pulse_width2 < MAX_DIST  ) {
    if ( cm2 < THRESHOLD_DIST && cm2 > 1.5f) {
      if ( digitalRead(RELAY_PIN2) == LOW) {
        digitalWrite(RELAY_PIN2, HIGH);
      } else {
        digitalWrite(RELAY_PIN2, LOW);
      }
    }
  }
  // Delay for the next loop
  delay(500);
}
