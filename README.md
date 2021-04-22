# Arduino Trapezoidal Library

This library acts as a simple trapezoidal control library that can be implemented using Arduino. It is written in such a way that the library
should be easily adapted to different microcontrollers that can be used with Arduino. The hardware_api.h files outline all hardware specific
files that can be rewritten for different platforms.

The original intention behind this project was to function as part of my submission to the ET4224 module at the University of Limerick and
also to create a simple controller for a 2nd Generation Toyota Prius inverter.

This library was heavily inspired by the Simple FOC Arduino library which can be found at <a href="https://github.com/simplefoc/Arduino-FOC">

##### Sensors
- Latching hall effect sensors
- Single analog comparator sensorless sensing

##### Driver
- 3 PWM signals (specifically designed for 2nd Generation Toyota Prius inverter)

## Future improvements
- Ability to change directions
- FOC capability
- Support for the STM Nucleo board and other boards
- Support for more sensors and encoders

## Getting Started
This library is only installable through the terminal

#### Using terminal
- Open terminal and run
```sh  
cd #Arduino libraries folder
git clone https://https://github.com/KevMca/trap-control.git
```
- Reopen Arduino IDE and you should have the library examples in `File > Examples > Trap Control`.

## Arduino code example
This is a simple Arduino code example implementing the hall sensor commutation option.

```cpp
#include <TrapControl.h>

//  BLDCDriver( pin_pwmU, pin_pwmV, pin_pwmW, pin_shutdown )
BLDCDriver driver = BLDCDriver(9, 10, 11, 12);

// HallSensor(pin_A, pin_B, pin_B, pullup)
HallSensor hall = HallSensor(3, 4, 5, Pullup::INTERN);
// Interrupt handlers
void doA(){hall.handleA();}
void doB(){hall.handleB();}
void doC(){hall.handleC();}

//  Trapezoidal()
Trapezoidal controller = Trapezoidal();

void setup() {
  // Initialise serial
  Serial.begin(9600);
  
  // initialise the hall sensor pins
  hall.init();
  // enable hall sensor interrupts
  hall.enableInterrupts(doA, doB, doC);
  // link the controller to the sensor
  controller.linkSensor(&hall);

  // initialise the driver object
  driver.init();
  // link the controller to the driver
  controller.linkDriver(&driver);

  // initialize controller
  controller.init();
  // set motor controller type
  controller.type = MotionControlType::duty;
  // initialize controller
  controller.setTarget(0.5);

  Serial.println("Initialised");
}

void loop() {

  // Trapezoidal algorithm function
  controller.loop();

}
```

## Documentation
For more information about the Prius inverter go to <a href="https://www.mcand.ru/prius">
