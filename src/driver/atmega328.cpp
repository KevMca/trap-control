#include "hardware_api.h"

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) 

// set pwm frequency to 32KHz
void _pinHighFrequency(const int pin){
  if (pin == 5 || pin == 6  ) {
    TCCR0A = bit(WGM00); // configure the pwm phase-corrected mode
    TCCR0B = bit(CS00); // set prescaler to 1 and 0xFF as TOP
  }
  if (pin == 9 || pin == 10 ) {
    TCCR1A = bit(WGM10); // configure the pwm phase-corrected mode
    TCCR1B = bit(CS10); // set prescaler to 1 and 0xFF as TOP
  }
  if (pin == 3 || pin == 11) 
    TCCR2A = bit(WGM20); // configure the pwm phase-corrected mode
    TCCR2B = bit(CS20); // set prescaler to 1 and 0xFF as TOP
}

// sets up PWM frequency, resolution and alignment
// - hardware specific
void _setupPWM(const int pinU, const int pinV, const int pinW) {
   //  set each of the pwm pin settings
  _pinHighFrequency(pinU);
  _pinHighFrequency(pinV);
  _pinHighFrequency(pinW);
}

// write the pwm duty cycle to the three phase pins
// - hardware specific
void _writeDutyPWM(float dutyU, float dutyV, float dutyW, int pinU, int pinV, int pinW, int shdown){
  // if any pins are set to high impedance, the shutdown pin must be pulsed
  if (dutyU == FLOATING || dutyV == FLOATING || dutyW == FLOATING) {
    digitalWrite(shdown, HIGH);
    digitalWrite(shdown, LOW);
    delayMicroseconds(30); // 30 microsecond settling time
  }

  // if pin is floating, disable PWM
  if (dutyU == FLOATING)
    analogWrite(pinU, 0);
  if (dutyV == FLOATING)
    analogWrite(pinV, 0);
  if (dutyW == FLOATING)
    analogWrite(pinW, 0);

  // if pin is low, pulse the pwm pin to set low
  if (dutyU == 0) {
    digitalWrite(pinU, HIGH);
    digitalWrite(pinU, LOW);
  }
  if (dutyV == 0) {
    digitalWrite(pinV, HIGH);
    digitalWrite(pinV, LOW);
  }
  if (dutyW == 0) {
    digitalWrite(pinW, HIGH);
    digitalWrite(pinW, LOW);
  }

  // if pin is high, set pwm 
  if (dutyU > 0)
    analogWrite(pinU, 255.0*dutyU);
  if (dutyV > 0)
    analogWrite(pinV, 255.0*dutyV);
  if (dutyW > 0)
    analogWrite(pinW, 255.0*dutyW);
}

#endif
