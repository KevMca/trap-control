#include "Sensorless.h"
#include "hardware_api.h"

Sensorless::Sensorless(int _pinU, int _pinV, int _pinW) {
  // hardware pins
  pinU = _pinU;
  pinV = _pinV;
  pinW = _pinW;

  // initialise lookup table comparator negative pins (AINneg)
  SENSORLESS_STEPS[0][0] = pinU;
  SENSORLESS_STEPS[0][1] = pinV;
  SENSORLESS_STEPS[0][2] = pinW;
  SENSORLESS_STEPS[0][3] = pinU;
  SENSORLESS_STEPS[0][4] = pinV;
  SENSORLESS_STEPS[0][5] = pinW;
  // initialise lookup table comparator events (mode)
  SENSORLESS_STEPS[1][0] = FALLING;
  SENSORLESS_STEPS[1][1] = RISING;
  SENSORLESS_STEPS[1][2] = FALLING;
  SENSORLESS_STEPS[1][3] = RISING;
  SENSORLESS_STEPS[1][4] = FALLING;
  SENSORLESS_STEPS[1][5] = RISING;
}

// initialise comparator pins
void Sensorless::init() {
  // Set comparator pins as inputs
  pinMode(pinU, INPUT);
  pinMode(pinV, INPUT);
  pinMode(pinW, INPUT);

  // assume that the motor starts at step 0
  electric_step = 0;
  compHandle();
}

// initialise comparator interrupt
void Sensorless::enableInterrupt(void (*intHandle)()) {
  _compEnableInterrupt(intHandle);
}

// Analog comparator handler called when an event occurs
void Sensorless::compHandle() {
  // BEMF debounce
  uint8_t mode = SENSORLESS_STEPS[1][electric_step];
  _debounce(mode, 10);
  
  electric_step = (electric_step>=5) ? 0 : ++electric_step;
  uint8_t new_AINneg = SENSORLESS_STEPS[0][electric_step];
  uint8_t new_mode   = SENSORLESS_STEPS[1][electric_step];
  _compEnable(AIN0, new_AINneg);
  _compMode(new_mode);
}
