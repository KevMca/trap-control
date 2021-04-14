#include <TrapControl.h>

// HallSensor(pin_A, pin_B, pin_B, pullup)
HallSensor hall = HallSensor(3, 4, 5, Pullup::INTERN);

// Interrupt handlers
void doA(){hall.handleA();}
void doB(){hall.handleB();}
void doC(){hall.handleC();}

// Previous step
int electric_step_prev = 0;

void setup() {
  // Initialise serial
  Serial.begin(9600);
  
  // initialise the hall sensor pins
  hall.init();
  
  // initialise test variable
  electric_step_prev = hall.electric_step;
  
  // enable hall sensor interrupts
  hall.enableInterrupts(doA, doB, doC);
}

void loop() {
  if(hall.electric_step != electric_step_prev) {
    // print new step and direction
    /*Serial.print(hall.hall_state);
    Serial.print(", ");
    Serial.println(hall.direction);*/

    // reset electric step
    electric_step_prev = hall.electric_step;
  }
}
