#include "bin_lib.h"

//Constructor button
button::button(int pin) {
  //Set modes
  pinMode(pin, INPUT);      // Sets the buttonPin as Input

  //initialize members
  _pin = pin;
  buttonReading = LOW;
  lastButtonReading = LOW;
  delayAmount = 500;
}

//Destructor button
button::~button() {
}

//Functions button
bool button::buttonReadingFunction() {
  lastButtonReading = digitalRead(_pin);   // Read if the pushbutton is being pressed
  delay(delayAmount);
  buttonReading = digitalRead(_pin);
  if (buttonReading == lastButtonReading) {
    oldButtonState = buttonReading;
    return (buttonReading);
  }
  else {
    return (oldButtonState);
  }
}

sensor::sensor(int pin) {
  //set pinmode to input
  pinMode(pin, INPUT);       // Sets the pwPin as an Output

  //initialize members
  numReadings = 50;
  _pin = pin;
  total = 0;
  average_distance = 0;
  maxVal = 0;
  minVal = 100;
}

sensor::~sensor() {
}

int sensor::sensorReading() {

  //average meeting
  maxVal = 0;
  minVal = 100;

  for (int i = 0; i <= (numReadings - 1); i++) {

    inch = pulseIn(_pin, HIGH);
    distance = inch / 58;
    total = total + distance;            // add value to total

    if (distance > maxVal) {
      maxVal = distance;
    }
    if (distance < minVal) {
      minVal = distance;
    }
  }

  total = total - maxVal - minVal;
  average_distance = total / (numReadings - 2);
  total = 0;
  //Serial.print("Distance: ");          // Prints the text "distance: " on the Serial Monitor
  //Serial.println(average_distance);           // Prints the distance on the Serial Montior and starts a new line
  return (average_distance);

}
