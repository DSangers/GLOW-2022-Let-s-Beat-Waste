//Project:  GLOW, Heart
//Module:   BeCreative Minor
//Author:   Dorieke Sangers
//Part:     Heart (Receiver)

//Hardware needed:
// - 1x RGB WS8012b LED strip
// - 1x Arduino (Mega was used, Uno is sufficient)
// - 1x 220 Ohm Resistors
// - 5x 10 kOhm Resistor
// - 5x Button
// - 1x HXT900 Servo
// - jumpers

//Connections:
// WS8012b
// Digital pin (blue)- 220 Ohm resistor - D7
// GND1 (black) -   GND arduino
// GND2 (black) - GND power supply
// +12V (red) - +12V power supply

// Button (5x)
// Side 1 - D (Arduino)
// Side 1 - 10 kOhm Resistor - Ground Arduino
// Side 2 - +5V (Arduino)

// HXT900
// Orange cable - D (Arduino)
// Red Cable - 5V (Arduino)
// Brown Cable - GND (Arduino)

// libraries
#include "Heart_lib.h"
#include <FastLED.h>
#include <Wire.h>

#define numLeds   150
#define ledPin    8

//pinout
int resetPin = 2;
int binPrevLevelPin = 3;
int binNextLevelPin = 4;
int binFullPin = 5;
int modePin = 6;
int s1Pin = 7;

//other variables
bool buttonReading1 = LOW;
int option = 0;
int distance = 0;
int distance1 = 0;
int distance2 = 0;
int mode = 0;
int maxOption = 4;

unsigned long lastReadingTime = 0;
unsigned long readingDelay = 250;

unsigned long lastModeTime = 0;
unsigned long modeDelay = 250;

//objects
servoClass servo1(s1Pin);

button resetB(resetPin);
button modeB(modePin);
button binFullB(binFullPin);
button binNextLevelB(binNextLevelPin);
button binPrevLevelB(binPrevLevelPin);

CRGB leds[numLeds];

int reading = 0;
int garbage = 0;

void setup() {
  Serial.begin(9600);             // Starts the serial communication
  FastLED.addLeds<WS2812, ledPin, GRB>(leds, numLeds);
  Wire.begin();
}

void loop() {
  Wire.requestFrom(8, 2);

  if(2 <= Wire.available()){
    reading = Wire.read();
    garbage = reading;
    reading = reading << 8;
    reading |= Wire.read();
    distance = reading - (garbage << 8);
    Serial.print("garbage thrown in: ");
    Serial.println(garbage);
    Serial.print("distance: ");
    Serial.println(reading);
  }

  
  bool modeBReading = modeB.buttonReadingFunction();
  if (modeBReading == HIGH) {
    Serial.println("I AM HIGH");
    if ((millis() - lastModeTime) > modeDelay) {
      bool modeBReading2 = modeB.buttonReadingFunction();
      if (modeBReading2 == modeBReading) {
        Serial.println("I AM STIL HIGH");
        if (mode == 0) {
          mode = 1;
        }
        else {
          mode = 0;
        }
      }
    }
  }

  if ((millis() - lastReadingTime) > readingDelay) {

    Serial.print("mode: ");
    Serial.println(mode);

    if (mode == 0) {   
     
      Serial.print("Average distance: ");         //Print to Serial monitor
      Serial.println(distance);                   //Print value to serial monitor

      //Check how full the bin is and switch on indication lights
      if (0 < distance && distance < 20) {
        option = maxOption;
      }
      else if (21 < distance && distance < 40) {
        option = 3;
      }
      else if (41 < distance  && distance < 60) {
        option = 2;
      }
      else {
        option = 1;                                 //Bin is empty
      }
    }


    if (mode == 1) {

      //bool resetBReading = resetB.buttonReadingFunction();
      // reset code

      bool binFullReading = binFullB.buttonReadingFunction();
      if (binFullReading == HIGH) {
        option = maxOption;
      }

      bool binNextLevelReading = binNextLevelB.buttonReadingFunction();
      if ((binNextLevelReading == HIGH) and (option < maxOption)) {
        option = option + 1;
      }

      bool binPrevLevelReding = binPrevLevelB.buttonReadingFunction();
      if ((binPrevLevelReding == HIGH) and (option > 1)) {
        option = option - 1;
      }

      Serial.print("Option: ");
      Serial.println(option);

    }
    servo1.servoFunction(option);
    lastReadingTime = millis();
  }

  if (garbage == 0) {
    //garbage thrown in
    Serial.println("Garbage thrown in");
    ledsFunction(option);
  }
 
}

void ledsFunction(int option) {
  for (int i = 0; i <= 59; i++) {
    leds[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(20);
  }

  if (option == 1) {

    for (int i = 39; i >= 5; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(100);
    }
  }
  else if (option == 2) {
    for (int i = 89; i >= 59; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(100);
    }
  }
  else if (option == 3) {
    for (int i = 119; i >= 89; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(100);
    }
  }
  else if (option == maxOption) {
    for (int i = 149; i >= 119; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(100);
    }
  }
}
//prullenbak = vol -> luiken = open
