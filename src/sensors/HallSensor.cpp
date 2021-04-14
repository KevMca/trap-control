#include "HallSensor.h"
#include "hardware_api.h"

HallSensor::HallSensor(int _pinA, int _pinB, int _pinC, Pullup _pullup){
  // hardware pins
  pinA = _pinA;
  pinB = _pinB;
  pinC = _pinC;

  // extern pullup as default
  pullup = _pullup;
}

// initialise pwm pins
void HallSensor::init() {
  // HallSensor - check if internal pullup needed for the HallSensor
  if(pullup == Pullup::INTERN){
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    pinMode(pinC, INPUT_PULLUP);
  } else {
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    pinMode(pinC, INPUT);
  }

  // init hall_state
  A_state= digitalRead(pinA);
  B_state = digitalRead(pinB);
  C_state = digitalRead(pinC);
  updateState();
}

// function enabling hardware interrupts for the callback provided
// if callback is not provided then the interrupt is not enabled
void HallSensor::enableInterrupts(void (*doA)(), void(*doB)(), void(*doC)()){
  // attach interrupt using a hardware specific function
  _enablePinChangeInterrupt(doA, pinA);
  _enablePinChangeInterrupt(doB, pinB);
  _enablePinChangeInterrupt(doC, pinC);
}

//  HallSensor interrupt callback functions
// A channel
void HallSensor::handleA() {
  A_state= digitalRead(pinA);
  updateState();
}
// B channel
void HallSensor::handleB() {
  B_state = digitalRead(pinB);
  updateState();
}
// C channel
void HallSensor::handleC() {
  C_state = digitalRead(pinC);
  updateState();
}

//Updates the state and step following an interrupt
void HallSensor::updateState() {
  hall_state = C_state + (B_state << 1) + (A_state << 2); // Update 3 bit state
  int8_t new_electric_step = ELECTRIC_STEPS[hall_state]; // Determine electric step using lookup table
  direction = (new_electric_step > electric_step)? Direction::CW : Direction::CCW; // Determine direction for state change
  electric_step = new_electric_step;
}