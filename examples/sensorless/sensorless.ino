#include <TrapControl.h>

// Sensorless(pin_u, pin_V, pin_W)
Sensorless sensor = Sensorless(18, 7, 19);

// Interrupt handler
void intHandle(){sensor.compHandle();}

// Previous step
int electric_step_prev = 0;

void setup() {
  // Initialise serial
  Serial.begin(9600);
  
  // initialise the comparator pins
  sensor.init();
  // initialise test variable
  electric_step_prev = sensor.electric_step;
  // enable comparator interrupt
  sensor.enableInterrupt(intHandle);
  sensor.direction = Direction::CCW;
}

void loop() {
  if(sensor.electric_step != electric_step_prev) {
    // print new step and direction
    Serial.println(sensor.electric_step);

    // reset electric step
    electric_step_prev = sensor.electric_step;
  }
}
