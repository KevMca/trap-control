#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include "Sensor.h"
#include "Arduino.h"

// seq 1 > 5 > 4 > 6 > 2 > 3 > 1   000 001 010 011 100 101 110 111
const int8_t ELECTRIC_STEPS[8] = { -1,  0,  4,  5,  2,  1,  3 , -1 };

/**
    Hall sensor class
*/
class HallSensor{
  public:
    /**
      Hall sensor class constructor
      @param _pinA hardware pin A
      @param _pinB hardware pin B
      @param _pinC hardware pin C
      @param _pullup select micro's internal pullups or external pullups
    */
    HallSensor(int _pinA, int _pinB, int _pinC, Pullup _pullup);

    /** Initialisation function */
  	void init();
    /** Enable interrupts */
  	void enableInterrupts(void (*doA)(), void(*doB)(), void(*doC)());

    //  HallSensor interrupt callback functions
    /** Pin A callback function */
    void handleA();
    /** Pin B callback function */
    void handleB();
    /** Pin C callback function */
    void handleC();
    
    // pins A and B
    int pinA; // hardware pin A
    int pinB; // hardware pin B
    int pinC; // hardware pin C

    // HallSensor configuration
    Pullup pullup; // Internal or external pullups
    
    // HallSensor state variables
    volatile int8_t hall_state;    // the current 3bit state of the hall sensors
    volatile int8_t electric_step; // the current step of the sensor (from 1 to 6)
    Direction direction;           // whether last step was CW (+1) or CCW (-1).

  private:

    void updateState(); // Updates the state and step following an interrupt

    volatile int A_state; // current state of pin A
    volatile int B_state; // current state of pin B
    volatile int C_state; // current state of pin C

};

#endif
