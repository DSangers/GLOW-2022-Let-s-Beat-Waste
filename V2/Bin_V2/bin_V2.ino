//Project:  GLOW, Heart
//Module:   BeCreative Minor
//Author:   Dorieke Sangers
//Part:     Bin (Sender)

//Hardware needed:
// - 2x SR-04 echo sensor
// - 1x Arduino (Uno was used, Nano is sufficient)
// - 1x 10 kOhm resistor
// - button

//Connections:
// Button
// Side 1 - D (Arduino)
// Side 1 - 10 kOhm Resistor - Ground Arduino
// Side 2 - +5V (Arduino)

// SR-04 (2x)
// 5V   -   5V
// PW+  -   D
// GND  -   GND

// libraries
#include "bin_lib.h"
#include <Wire.h>

//pinout
int binGarbageThrownInPin = 2;
int pwPin1 = 3;
int pwPin2 = 4;

//other variables
int distance = 0;
int distance1 = 0;
int distance2 = 0;
int garbage = 0;

unsigned long lastReadingTime = 0;
unsigned long readingDelay = 500;

unsigned long lastButtonTime = 0;
unsigned long buttonDelay = 100;

sensor sensor1(pwPin1);
sensor sensor2(pwPin2);
button binGarbageThrownIn(binGarbageThrownInPin);

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void loop() {

  bool buttonReading1 = binGarbageThrownIn.buttonReadingFunction();
  if (buttonReading1 == LOW) {
    //Garbage is thrown in
    if ((millis() - lastButtonTime) > buttonDelay) {
      bool buttonReading2 = binGarbageThrownIn.buttonReadingFunction();
      if (buttonReading2 == buttonReading1) {
        //Garbage is really thrown in
        garbage = 1;
      }
      else {
        garbage = 0;
      }
    }
  }
  else {
    //Garbage is not thrown in
    garbage = 0;
  }

  if ((millis() - lastReadingTime) > readingDelay) {
    distance1 = sensor1.sensorReading();        //Reading Sensor one
    distance2 = sensor2.sensorReading();        //Reading Sensor two
    distance = (distance1 + distance2) / 2;     //Average of both sensors
    lastReadingTime = millis();
  }
}

void requestEvent() {
  Wire.write(byte(garbage));
  Wire.write(byte(distance));
}
