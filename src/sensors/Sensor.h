#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

/**
 *  Direction structure
 */
enum Direction{
    CW      = 1,  //clockwise
    CCW     = -1, // counter clockwise
    UNKNOWN = 0   //not yet known or invalid state
};

/**
 *  Pullup configuration structure
 */
enum Pullup{
    INTERN, // Use internal pullups (turn on microcontroller pullups)
    EXTERN  // Use external pullups (the user has their own pullups outside the microcontroller)
};

/**
  Sensor class
*/
class Sensor {
  public:

    // State variables
    volatile int8_t electric_step;  // the current step of the sensor (from 1 to 6)

  private:

};

#endif