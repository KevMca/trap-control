#include "Trapezoidal.h"

Trapezoidal::Trapezoidal()
{
  // default target value
  target = 0;
  //driver
  driver = nullptr;
  //sensor 
  sensor = nullptr;
}

/**
	Initialise the trapezoidal controller
*/
void Trapezoidal::init() {
    enable();
}

/**
	Disable the driver and the controller
*/
void Trapezoidal::disable() {
  driver->disable();  // disable the driver
  enabled = 0;        // motor status update
}

/**
	Enable the driver and the controller
*/
void Trapezoidal::enable() {
  driver->enable(); // enable the driver
  enabled = 1;      // motor status update
}

/**
	Link the driver which controls the motor
*/
void Trapezoidal::linkDriver(BLDCDriver* _driver) {
  driver = _driver;
}

/**
	Sensor linking method
*/
void Trapezoidal::linkSensor(Sensor* _sensor) {
  sensor = _sensor;
}

/**
	Function running the trapezoidal algorithm in real-time
  Reads the sensor value and powers the motor accordingly
*/
void Trapezoidal::loop() {
  // if disabled do nothing
  if(!enabled) return;

  // if open-loop do nothing
  switch (type) {
    case MotionControlType::openloop: {
      delay(1000/(target/10));
      float Ud = stepToPhase(U, electric_step);
      float Vd = stepToPhase(V, electric_step);
      float Wd = stepToPhase(W, electric_step);
      driver->setPwm(Ud, Vd, Wd);
      electric_step++;
      electric_step %= 6;
      break;
    }
    case MotionControlType::duty: {
      // check if the step has changed
      if(sensor->electric_step != electric_step) {
        electric_step = sensor->electric_step;
        float Ud = stepToPhase(U, electric_step);
        float Vd = stepToPhase(V, electric_step);
        float Wd = stepToPhase(W, electric_step);
        driver->setPwm(Ud, Vd, Wd);
      }
      break;
    }
  }
}

/**
	Set the target
    - This method can be upgraded later in order to add different target types
*/
void Trapezoidal::setTarget(float _target) {
  switch (type) {
    case MotionControlType::openloop:
      target = _target;
      break;
    case MotionControlType::duty:
      target = _target;
      maxDuty = _target;
      break;
  }
}

/**
	Spin up the motor using timers
*/
void Trapezoidal::openLoopRamp(float startRPM, float endRPM, float rampTime) {
  float endDelay = 1/(endRPM/10);             // end delay in seconds
  float currDelay = 1/(startRPM/10);          // start delay in seconds
  int m = (-currDelay-endDelay+2*rampTime)/(currDelay+endDelay); // number of increments
  float incDelay = (currDelay-endDelay)/m;    // the increment amount

  int8_t step = 0;
  while(currDelay > endDelay) {
    delay(currDelay*1000);
    float Ud = stepToPhase(U, step);
    float Vd = stepToPhase(V, step); 
    float Wd = stepToPhase(W, step);
    driver->setPwm(Ud, Vd, Wd);

    // increment step
    step++;
    step %= 6;
    currDelay -= incDelay;
  }
}

/**
	Return the phase voltages for a given step 
*/
float Trapezoidal::stepToPhase(uint8_t phase, uint8_t _electric_step) {
  switch(TRAP_STEPS[phase][_electric_step]) {
    case LOW:
      return LOW;
      break;
    case HIGH:
      return maxDuty;
      break;
    case FLOATING:
      return FLOATING;
      break;
    default:
      return FLOATING;
      break;
  }
}