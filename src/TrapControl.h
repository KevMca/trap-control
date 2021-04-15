/*!
 * @file TrapControl.h
 *
 * @section Introduction
 *
 * This library outlines a simple trapezoidal controller for Brushless DC (BLDC) motors, with support for:
 * - Arduino Uno microcontroller
 * - Sensorless control
 * - Latched hall effect sensored control
 * - Prius Gen 2 inverter
 *
 * This library is based off the structure of the SimpleFOC Arduino Library
 *
 * @section Features
 * 
 * - Designed to be easily modified for different platforms
 * - Most BLDC motors are relatively standard, so they should work with this library
 * - Ability to use both sensored or sensorless operation
 * 
 * @section Example code
 * @code
 * @endcode 
 *
 * @section License
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */

#ifndef TRAPCONTROL_H
#define TRAPCONTROL_H

#include "driver/BLDCDriver.h"
#include "sensors/HallSensor.h"
#include "sensors/Sensorless.h"

#endif
