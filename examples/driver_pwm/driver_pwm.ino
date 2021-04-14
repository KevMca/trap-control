#include <TrapControl.h>

//  BLDCDriver( pin_pwmU, pin_pwmV, pin_pwmW, pin_shutdown )
BLDCDriver driver = BLDCDriver(9, 10, 11, 12);

void setup() {
  // setup serial
  Serial.begin(9600);
  // initialise the driver object
  driver.init();
  // test the pwm output of the driver object
  driver.setPwm(FLOATING, 0, 0.5);
}

void loop() {

}
