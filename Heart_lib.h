#ifndef Heart_lib_h
#define Heart_lib_h

#include <Servo.h>
#include <arduino.h>

class servoClass {
  public:
    servoClass(int pin); //constructor
    ~servoClass(); //destructor
    //put functions here
    void servoFunction(int option);

  private:
    Servo myServo;
    int s_angle;
    int previousAngle;
    int pos;
    int _pin;
};

class button {
  public:
    button(int pin);   //constructor
    ~button();  //destructor

    //put functions here
    bool buttonReadingFunction();

  private:
    bool buttonReading;
    bool lastButtonReading;
    bool oldButtonState;
    int _pin;
    int delayAmount;
};

class indicationLight {
  public:
    indicationLight(int pin1, int pin2, int pin3); //constructor
    ~indicationLight(); //Destructor

    //put functions here
    void indicationLightFunction(int option);

  private:
    int _redPin;
    int _yellowPin;
    int _greenPin;
};

class sensor {
  public:
    sensor(int pin); //constructor
    ~sensor(); //Destructor

    //put functions here
    int sensorReading();

  private:
    //Pinout
    int _pin;

    //Variables measurements
    int distance;
    long inch;

    //Variables for reliable measurements
    int numReadings;
    long total;
    long average_distance;
    int maxVal;
    int minVal;

};

class heartBeating {
  public:
    heartBeating(int pin);
    ~heartBeating();

    //put functions here
    void heartBeatingFunction(bool buttonReading);

  private:
    int _pin;

};
#endif
