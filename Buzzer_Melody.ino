#include "notes.h"

int buzzerPin=9;
int littleStarNote[]={C5, C5, G5, G5, A5, A5, G5, 0, F5, F5, E5, E5, D5, D5, C5, 0,
                      G5, G5, F5, F5, E5, E5, D5, 0, G5, G5, F5, F5, E5, E5, D5, 0,
                      C5, C5, G5, G5, A5, A5, G5, 0, F5, F5, E5, E5, D5, D5, C5, 0};
int littleStarDuration[]={4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                          4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                          4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int littleBeeNote[]={G5, E5, E5, 0, F5, D5, D5, 0, C5, D5, E5, F5, G5, G5, G5, 0,
                     G5, E5, E5, 0, F5, D5, D5, 0, C5, E5, G5, G5, E5, 0, 0, 0,
                     D5, D5, D5, D5, D5, E5, F5, 0, E5, E5, E5, E5, E5, F5, G5, 0,
                     G5, E5, E5, 0, F5, D5, D5, 0, C5, E5, G5, G5, C5, 0, 0, 0};
int littleBeeDuration[]={4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

const byte swPin=2;  //switch pin for interrupt
volatile int swValue=0;  //initial swValue:0=silent
int debounceDelay=200; //debounce delay (ms)

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP); //enable pull-up resistor of input pin
  attachInterrupt(0, int0, LOW); //assign int0
  }

void loop() {
  switch (swValue) {
    case 1 :
      playLittleBee(buzzerPin, sizeof(littleBeeNote)/sizeof(int));
      break;
    case 2 :
      playLittleStar(buzzerPin, sizeof(littleStarNote)/sizeof(int));
      break;
    default :
      noTone(buzzerPin);  //silent buzzer
      break;  
    }
  }

void playLittleBee(int pin, int count) {
  for (int i=0; i<count; i++) {
    int d=1000/littleBeeDuration[i];
    tone(pin, littleBeeNote[i], d);
    int p=d * 1.3;
    delay(p);
    noTone(pin);
    }
  delay(2000);
  }

void playLittleStar(int pin, int count) {
  for (int i=0; i<count; i++) {
    int d=1000/littleStarDuration[i];
    tone(pin, littleStarNote[i], d);
    int p=d * 1.3;
    delay(p);
    noTone(pin);
    }
  delay(2000);
  }

void int0() { //interrupt handler
  if (debounced()) { //debounced:
    ++swValue; //increment swValue
    if (swValue > 2) {swValue=0;} //reset swValue
    }
  }

boolean debounced() { //check if debounced
  static unsigned long lastMillis=0; //record last millis
  unsigned long currentMillis=millis(); //get current elapsed time
  if ((currentMillis-lastMillis) > debounceDelay) {
    lastMillis=currentMillis; //update lastMillis with currentMillis
    return true; //debounced
    }
  else {return false;} //not debounced

  }
