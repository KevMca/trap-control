#include <TrapControl.h>

//  BLDCDriver( pin_pwmU, pin_pwmV, pin_pwmW, pin_shutdown )
BLDCDriver driver = BLDCDriver(9, 10, 11, 12);

//  Trapezoidal()
Trapezoidal controller = Trapezoidal();

void setup() {
  // Initialise serial
  Serial.begin(9600);
  
  // initialise the driver object
  driver.init();
  // link the controller to the driver
  controller.linkDriver(&driver);

  // initialize controller
  controller.init();
  // set motor controller type
  controller.type = MotionControlType::openloop;
  // set duty cycle for open loop control
  controller.maxDuty = 0.5;
  // initialize controller
  controller.setTarget(1000);

  Serial.println("Initialised");
}

void loop() {

  // Trapezoidal algorithm function
  controller.loop();

}
