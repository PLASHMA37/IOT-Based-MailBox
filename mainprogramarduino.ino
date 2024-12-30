#include <Servo.h>
#include "HX711.h"

bool currentState = false;
bool previousState = false;

HX711 scale;
Servo s1;
void lidOn();
void lidOff();
const float letterThreshold = 100.0;
const float packageThreshold = 500.0; 

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT_PULLUP); //mention ir sensor
  s1.attach(5); //mention servo pin
  s1.write(0);

  scale.begin(10, 11); //mention dout and iot pin hx711
  scale.set_scale();
  scale.tare();    
}

void loop() {
  currentState = digitalRead(3); //mention ir sensor pin
  if (currentState != previousState) {
    if (currentState == LOW) { 
      lidOn();
      Serial.println("IR DETECTED");
    } else {
      lidOff();
      Serial.println("IR NOT DETECTED");
    }
    previousState = currentState;
  }

  float weight = scale.get_units(10);  // Read the weight (average of 10 readings)
  if (weight > packageThreshold) {
    Serial.println("NEW PACKAGE");
  } else if (weight > letterThreshold) {
    Serial.println("NEW LETTER");
  }
}

void lidOn() {
  s1.write(90);
}

void lidOff() {
  s1.write(0);
}

