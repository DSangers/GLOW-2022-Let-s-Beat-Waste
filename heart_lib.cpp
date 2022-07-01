#include "Heart_lib.h"

//Constructor Servo
servoClass::servoClass(int pin) {
  //initialize members
  Servo myServo;
  _pin = pin;
  s_angle = 0;
  previousAngle = 0;
  pos = 0;
}

//Destructor Servo
servoClass::~servoClass() {
}

//Functions Servo
void servoClass::servoFunction(int option) {
  myServo.attach(_pin);

  if (option == 1) {
    s_angle = 10;
  }
  else if (option == 2) {
    s_angle = 75;
  }
  else if (option == 3) {
    s_angle = 150;
  }
  else if (option == 4) {
    s_angle = 200;
  }

  if (s_angle < previousAngle) {
    Serial.println("smaller");
    for (int i = previousAngle; i >= s_angle; i--) {
      myServo.write(i);
      delay(15);
    }
    Serial.println("Reached position");
  }
  else if (s_angle == previousAngle) {
    delay(15);
  }
  else if (s_angle > previousAngle) {
    Serial.println("Bigger");
    for (int i = previousAngle; i <= s_angle; i++) {
      myServo.write(i);
      delay(15);
    }
    Serial.println("Reached position");
  }
  previousAngle = s_angle;
}

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

//Constructor Indication Light
indicationLight::indicationLight(int pin1, int pin2, int pin3) {

  //set pinMode to output
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  //initialize members
  _redPin = pin1;
  _yellowPin = pin2;
  _greenPin = pin3;
}

//Destructor indication light
indicationLight::~indicationLight() {
}

void indicationLight::indicationLightFunction(int option) {
  if (option == 1) {
    digitalWrite(_greenPin, HIGH);
    digitalWrite(_yellowPin, HIGH);
    digitalWrite(_redPin, HIGH);
  }
  else if (option == 2) {
    digitalWrite(_greenPin, HIGH);
    digitalWrite(_yellowPin, HIGH);
    digitalWrite(_redPin, LOW);
  }
  else if (option == 3) {
    digitalWrite(_greenPin, HIGH);
    digitalWrite(_yellowPin, LOW);
    digitalWrite(_redPin, LOW);
  }
  else {
    digitalWrite(_greenPin, LOW);
    digitalWrite(_yellowPin, LOW);
    digitalWrite(_redPin, LOW);
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

//Constructor heartBeating
heartBeating::heartBeating(int pin) {
  //Set modes
  pinMode(pin, OUTPUT);

  //Initialize members
  _pin = pin;

  //initaliaze
  digitalWrite(_pin, LOW);
}

//Destructor button
heartBeating::~heartBeating() {
}

void heartBeating::heartBeatingFunction(bool buttonReading) {
  if (buttonReading == HIGH) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(_pin, HIGH);
      delay(200);
      digitalWrite(_pin, LOW);
      delay(200);
    }
  }
  else {
    digitalWrite(_pin, LOW);
  }
}
