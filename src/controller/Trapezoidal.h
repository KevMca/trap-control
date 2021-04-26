#ifndef TRAPEZOIDAL_H
#define TRAPEZOIDAL_H

#include "../driver/BLDCDriver.h"
#include "../sensors/Sensor.h"

#define U 0
#define V 1
#define W 2

/**
 *  Motiron control type
 */
enum MotionControlType{
  duty,     // Torque control
  openloop
};

// seq 1 > 5 > 4 > 6 > 2 > 3 > 1      0          1         2         3         4         5
const int8_t TRAP_STEPS[3][6] =   {{ FLOATING,  HIGH,     HIGH,     FLOATING, LOW,      LOW },     // Phase U
                                    { LOW,       LOW,      FLOATING, HIGH,     HIGH,     FLOATING },// Phase V
                                    { HIGH,      FLOATING, LOW,      LOW,      FLOATING, HIGH }};   // Phase W

/**
  Trapezoidal controller class
*/
class Trapezoidal {
  public:
    /**
      Trapezoidal controller constructor
    */
    Trapezoidal();

    /**  Controller hardware init function */
  	void init();
    /** Controller disable function */
  	void disable();
    /** Controller enable function */
    void enable();

    /**
     * Function linking a controller and a driver 
     *
     * @param driver BLDCDriver class implementing all the hardware specific functions necessary for PWM setting
     */
    void linkDriver(BLDCDriver* driver);
    /**
     * Function linking a controller and a sensor 
     * 
     * @param sensor Sensor class wrapper for the trapezoidal algorihtm to read the motor angle
     */
    void linkSensor(Sensor* sensor);
    
    /** BLDCDriver link */
    BLDCDriver* driver; 
    /** BLDCDriver link */
    Sensor* sensor; 

    /**
     * Function running the trapezoidal algorithm in real-time
     * it powers the motor by sensing the current step of the motor
     * - the faster you can run it the better Arduino UNO ~1ms
     */ 
    void loop();

    /**
     * Sets the target for the controller
     * 
     * @param target duty cycle setting until more complicated control is implemented
     */
    void setTarget(float _target);

    /**
     * Spin up the motor using timers instead of any sensing
     * 
     * @param incRPM the RPM at the beginning of the ramp
     * @param endRPM the RPM at the end of the ramp
     * @param rampTime the amount of time that it takes for the ramp to complete
     */
    void openLoopRamp(float startRPM, float endRPM, float rampTime);


    // Controller state variables
    MotionControlType type; // parameter determining the control loop to be used
    volatile int8_t electric_step = 0; // the current step of the sensor (from 1 to 6)
    float maxDuty = 0; // maximum duty cycle to be used to power the motor
    float target = 0; // current target value - depends on type of the controller
    int8_t enabled = 0; // enabled or disabled motor flag

  private:

    /**
     * Return the phase voltages for a given step 
     * 
     * @param phase the phase number to use in the lookup
     * @param _electric_step the electric step to use in the lookup
     */
    float stepToPhase(uint8_t phase, uint8_t _electric_step);
};

#endif
