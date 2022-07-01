#ifndef bin_lib_h
#define bin_lib_h

#include <arduino.h>

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

#endif
