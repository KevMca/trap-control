#ifndef HARDWARE_API_sens_H
#define HARDWARE_API_sens_H

#include "Arduino.h"

/** 
 * Sets up a pin change interrupt for the given pin
 * - hardware specific
 * 
 * @param PCHandle interrupt handler
 * @param PCPin hardware pin 
 */
void _enablePinChangeInterrupt(void (*PCHandle)(), int PCPin);

#define AIN0 6
#define INTERNAL_REFERENCE 1
#define AIN1 7

/** 
 * Enables the comparator and sets the positive and negative pins
 * - hardware specific
 * 
 * @param AINpos positive comparator hardware pin
 * @param AINneg negative comparator hardware pin
 */
void _compEnable(uint8_t AINpos, uint8_t AINneg);

/** 
 * Disables the comparator
 * - hardware specific
 */
void _compDisable(void);

/** 
 * Sets the interrupt event for the comparator
 * - hardware specific
 */
void _compMode(uint8_t mode);

/** 
 *  Enables the comparator interrupt and sets the interrupt service routine
 * - hardware specific
 *
 * @param compHandle interrupt handler to be run during an ISR
 */
void _compEnableInterrupt(void (*compHandle)());

/** 
 *  Disables the comparator interrupt
 * - hardware specific
 */
void _compDisableInterrupt(void);

#endif
