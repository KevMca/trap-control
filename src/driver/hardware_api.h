#ifndef HARDWARE_API_H
#define HARDWARE_API_H

#define FLOATING -1

#include "Arduino.h"

/** 
 * Sets up PWM frequency, resolution and alignment
 * - hardware specific
 * 
 * @param pinU pinU bldc driver
 * @param pinV pinV bldc driver
 * @param pinW pinW bldc driver
 */
void _setupPWM(const int pinU, const int pinV, const int pinW);

/** 
 * Sets the PWM duty cycle for the three phases
 * - hardware specific
 * 
 * @param dutyU  phase U duty [0,1] or FLOATING
 * @param dutyV  phase V duty [0,1] or FLOATING
 * @param dutyW  phase W duty [0,1] or FLOATING
 * @param pinU  phase U hardware pin number
 * @param pinV  phase V hardware pin number
 * @param pinW  phase W hardware pin number
 */ 
void _writeDutyPWM(float dutyU, float dutyV, float dutyW, int pinU, int pinV, int pinW, int shdown);

#endif
