#include <TrapControl.h>

//  BLDCDriver( pin_pwmU, pin_pwmV, pin_pwmW, pin_shutdown )
BLDCDriver driver = BLDCDriver(9, 10, 11, 12);

// Sensorless(pin_u, pin_V, pin_W)
Sensorless sensor = Sensorless(18, 7, 19);
// Interrupt handler
void intHandle(){sensor.compHandle();}

//  Trapezoidal()
Trapezoidal controller = Trapezoidal();

void setup() {
  // Initialise serial
  Serial.begin(9600);
  
  // initialise the comparator pins
  sensor.init();
  // link the controller to the sensor
  controller.linkSensor(&sensor);

  // initialise the driver object
  driver.init();
  // link the controller to the driver
  controller.linkDriver(&driver);

  // initialize controller
  controller.init();
  // set motor controller type
  controller.type = MotionControlType::duty;
  // choose controller duty cycle
  controller.setTarget(0.5);

  // Speed up open loop controller up to
  controller.openLoopRamp(500, 1500, 5);

  // enable comparator interrupt
  sensor.enableInterrupt(intHandle);

  Serial.println("Initialised");
}

void loop() {

  // Trapezoidal algorithm function
  controller.loop();

}
