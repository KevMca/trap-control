#include "BLDCDriver.h"

BLDCDriver::BLDCDriver(int _pwmU,int _pwmV,int _pwmW,int _shdown){
  // pin initialization
  pwmU = _pwmU;
  pwmV = _pwmV;
  pwmW = _pwmW;

  // enable_pin pin
  shdown = _shdown;
}

// enable motor driver
void  BLDCDriver::enable(){
    // turn off the shutdown pin
    digitalWrite(shdown, LOW);
    // set FLOATING to PWM
    setPwm(FLOATING,FLOATING,FLOATING);
}

// disable motor driver
void BLDCDriver::disable()
{
    // turn on the shutdown pin
    digitalWrite(shdown, HIGH);
    // set FLOATING to PWM
    setPwm(FLOATING,FLOATING,FLOATING);
}

// initialise pwm pins
void BLDCDriver::init() {
  // PWM pins
  pinMode(pwmU, OUTPUT);
  pinMode(pwmV, OUTPUT);
  pinMode(pwmW, OUTPUT);
  pinMode(shdown, OUTPUT);

  // Set the pwm frequency of the pwm outputs
  // hardware specific function - depending on driver and mcu
  _setupPWM(pwmU, pwmV, pwmW);
}


// Set duty to the pwm pin
void BLDCDriver::setPwm(float Ud, float Vd, float Wd) {
  // limited in [0,1] or FLOATING
  Ud = (Ud==FLOATING) ? FLOATING : ((Ud<0) ? 0 : ((Ud>1) ? 1 : Ud));
  Vd = (Vd==FLOATING) ? FLOATING : ((Vd<0) ? 0 : ((Vd>1) ? 1 : Vd));
  Wd = (Wd==FLOATING) ? FLOATING : ((Wd<0) ? 0 : ((Wd>1) ? 1 : Wd));

  // write pwm duty cycle to individual phases
  // hardware specific function - depending on driver and mcu
  _writeDutyPWM(Ud, Vd, Wd, pwmU, pwmV, pwmW, shdown);
}