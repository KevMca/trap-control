#ifndef HARDWARE_API_sens_H
#define HARDWARE_API_sens_H

#include "Arduino.h"

/** 
 * Sets up a pin change interrupt for the given pin
 * - hardware specific
 * 
 * @param doA interrupt handler
 * @param pinA hardware pin 
 */
void _enablePinChangeInterrupt(void (*PCHandle)(), int PCPin);

#endif
