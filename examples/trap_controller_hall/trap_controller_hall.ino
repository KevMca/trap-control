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
