/*
  Adjustable distance alarm
  Ultrasonic Sensor tigger Buzzer by Variable Resistance controlling distance threshold
  Ultrasonic Sensor: HC-SR04
  Variable Resistance: B10K
  Buzzer: ZK-1205S
*/

// Pin & Variable Setting
const int TRIG_PIN = 12;
const int ECHO_PIN = 8;
const int BUZZER_PIN = 4;

int sensorPin = A5;    // Analog input pin
int sensorValue = 0;  // Analog input value (0 - 1023)

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;


void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  //Set Echo pin as input to measure the duration of
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);

  // Set serial monitor to view the output
  Serial.begin(9600);

}

void loop() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  sensorValue = analogRead(sensorPin);   // Read analog input value (0 - 1023)
  sensorValue = map(sensorValue, 0, 1023, 0, 100); // Transform analog input value into 0 - 100

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  cm = pulse_width / 58.0;

  if ( pulse_width < MAX_DIST ) {
    Serial.print("thre_dist: ");
    Serial.print(sensorValue);
    Serial.print(" cm\t Sensor_dist: ");
    Serial.print(cm);
    Serial.println(" cm");
    if ( cm < sensorValue ) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  delay(5);
}
