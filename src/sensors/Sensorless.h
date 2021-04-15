#ifndef SENSORLESS_H
#define SENSORLESS_H

#include "Sensor.h"
#include "Arduino.h"

/**
  Sensorless class
*/
class Sensorless {
  public:
    /**
      Sensorless class constructor
      @param _pinU hardware pin U
      @param _pinV hardware pin V
      @param _pinW hardware pin W
    */
    Sensorless(int _pinU, int _pinV, int _pinW);

    /** Initialisation function */
  	void init();
    /** Enable interrupts */
  	void enableInterrupt(void (*intHandle)());

    //  Sensorless interrupt callback function
    /** Comparator callback function */
    void compHandle();

    // pins U, V and W
    uint8_t pinU; // hardware pin U
    uint8_t pinV; // hardware pin V
    uint8_t pinW; // hardware pin W

    // Lookup for comparator negative pin and mode for each step
    uint8_t SENSORLESS_STEPS[2][6];

    // Sensorless state variables
    volatile int8_t electric_step; // the current step of the sensor (from 1 to 6)
    Direction direction = Direction::CW;           // whether last step was CW (+1) or CCW (-1).

  private:

};

#endif