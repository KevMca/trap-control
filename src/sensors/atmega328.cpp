#include "hardware_api.h"

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) 

// a function that does nothing
static void nothing(void) {
}

typedef void (*voidFuncPtr)(void);
static volatile voidFuncPtr PCINT2Func[8] = { nothing, nothing, nothing, nothing, nothing, nothing, nothing, nothing, };
static volatile voidFuncPtr PCINT1Func[8] = { nothing, nothing, nothing, nothing, nothing, nothing, nothing, nothing, };
static volatile voidFuncPtr PCINT0Func[8] = { nothing, nothing, nothing, nothing, nothing, nothing, nothing, nothing, };
static volatile voidFuncPtr compFunc = nothing;

#define PCINT2_CALLBACK(bit) \
if (PCINT2Func[bit] != nothing) \
if (changedbits & (1 << bit)) \
  PCINT2Func[bit] ();

#define PCINT1_CALLBACK(bit) \
if (PCINT1Func[bit] != nothing) \
if (changedbits & (1 << bit)) \
  PCINT1Func[bit] ();

#define PCINT0_CALLBACK(bit) \
if (PCINT0Func[bit] != nothing) \
if (changedbits & (1 << bit)) \
  PCINT0Func[bit] ();

// variables for storing old state in order to detect changes
uint8_t PINDOld;
uint8_t PINCOld;
uint8_t PINBOld;

void attachPCINT(uint8_t PCPin, void (*userFunc)(void), int mode) {
  if(PCPin >= 0 && PCPin <= 7)
    PCINT2Func[PCPin] = userFunc;
  if(PCPin >= 14 && PCPin <= 19)
    PCINT1Func[PCPin - 14] = userFunc;
  if(PCPin >= 8 && PCPin <= 13)
    PCINT0Func[PCPin - 8] = userFunc;
}

// Sets up a pin change interrupt for the given pin
// The ATMEGA328p has two pins that can use hardware interrupts (pins 2 and 3)
// If the pin is not pin 2 or 3, a pin change interrupt is used instead
void _enablePinChangeInterrupt(void (*PCHandle)(), int PCPin) {
  // If hardware interrupt is available, use it
  if(PCPin == 2 || PCPin == 3) {
    if(PCHandle != nullptr) attachInterrupt(digitalPinToInterrupt(PCPin), PCHandle, CHANGE);
    Serial.println("Hardware");
  } 
  // Otherwise use pin change interrupts
  else if(PCPin >= 0 && PCPin <= 7){
    PCICR  |= bit(PCIE2);       // Interrupt 2 enabled (pcint 16 to 23)
    PCMSK2 |= 1 << PCPin;       // Enable appropriate mask bit
    PINDOld = PIND;             // Store current pin state for PCINT2
    attachPCINT(PCPin, PCHandle, CHANGE);
    Serial.println("Software 2");
  }
  else if(PCPin >= 14 && PCPin <= 19){
    PCICR  |= bit(PCIE1);       // Interrupt 1 enabled (pcint 8 to 14)
    PCMSK1 |= 1 << (PCPin - 14);// Enable appropriate mask bit
    PINCOld = PINC;             // Store current pin state for PCINT2
    attachPCINT(PCPin, PCHandle, CHANGE);
    Serial.println("Software 1");
  }
  else if(PCPin >= 8 && PCPin <= 13){
    PCICR  |= bit(PCIE0);       // Interrupt 0 enabled (pcint 0 to 7)
    PCMSK0 |= 1 << (PCPin - 8); // Enable appropriate mask bit
    PINBOld = PINB;             // Store current pin state for PCINT2
    attachPCINT(PCPin, PCHandle, CHANGE);
    Serial.println("Software 0");
  }
}

// Comparator enable function
void _compEnable(uint8_t AINpos, uint8_t AINneg) {
  // enable the AC
  ACSR &= ~(1<<ACD);  // switch on the AC
  //Serial.println(AINpos);
  //Serial.println(AINneg);

  // choose the input for positive input
  if (AINpos == INTERNAL_REFERENCE) {
    ACSR |= (1<<ACBG);  // set Internal Voltage Reference (1V1)
  } else {
    ACSR &= ~(1<<ACBG); // set pin to AIN0
  }

  // choose the input for negative input
  if ((AINneg >= A0) && (AINneg <= A5)) {
    ADCSRA &= ~(1<<ADEN);  // turn off the ADC
    ADMUX &= ~0x1F;        // reset the first 5 bits
    ADMUX |= AINneg-A0;    // choose the ADC channel
    ADCSRB |= (1<<ACME);   // select the ADC multiplexer as AC input
  } else {
    ADCSRB &= ~(1<<ACME);  //set pin AIN1
  }
}

// Comparator disable function
void _compDisable(void) {
  // disable the AC
  _compDisableInterrupt(); // disable interrupts on AC
  ACSR |= (1<<ACD);        // switch off the AC
}

void _compMode(uint8_t mode) {
  // set interrupt mode 
  if (mode == CHANGE) {
    ACSR &= ~((1<<ACIS1) | (1<<ACIS0));
  } else if (mode == FALLING) {
    ACSR &= ~(1<<ACIS0);
    ACSR |= (1<<ACIS1);
  } else { //default is RISING
    ACSR |= ((1<<ACIS1) | (1<<ACIS0));
  }
}

// Comparator interrupt enable function
void _compEnableInterrupt(void (*compHandle)()) {
  _compDisableInterrupt();        // disable AC interrupt
  compFunc = compHandle; //set the interrupt handler

  //enable interrupts
  ACSR |= (1<<ACIE);
  SREG |= (1<<SREG_I);
}

// Comparator interrupt disable function
void _compDisableInterrupt(void) {
  ACSR &= ~(1<<ACIE);
}

/**
  * Pin change ISRs
  */
ISR(PCINT2_vect) {
  // check what pins have changed
  uint8_t changedbits = PIND ^ PINDOld;
  PINDOld = PIND;

  // run the correct callback function
  PCINT2_CALLBACK(0)
  PCINT2_CALLBACK(1)
  PCINT2_CALLBACK(2)
  PCINT2_CALLBACK(3)
  PCINT2_CALLBACK(4)
  PCINT2_CALLBACK(5)
  PCINT2_CALLBACK(6)
  PCINT2_CALLBACK(7)
}

ISR(PCINT1_vect) {
  // check what pins have changed
  uint8_t changedbits = PINC ^ PINCOld;
  PINCOld = PINC;

  // run the correct callback function
  PCINT1_CALLBACK(0)
  PCINT1_CALLBACK(1)
  PCINT1_CALLBACK(2)
  PCINT1_CALLBACK(3)
  PCINT1_CALLBACK(4)
  PCINT1_CALLBACK(5)
  PCINT1_CALLBACK(6)
  PCINT1_CALLBACK(7)
}

ISR(PCINT0_vect) {
  // check what pins have changed
  uint8_t changedbits = PINB ^ PINBOld;
  PINBOld = PINB;

  // run the correct callback function
  PCINT0_CALLBACK(0)
  PCINT0_CALLBACK(1)
  PCINT0_CALLBACK(2)
  PCINT0_CALLBACK(3)
  PCINT0_CALLBACK(4)
  PCINT0_CALLBACK(5)
  PCINT0_CALLBACK(6)
  PCINT0_CALLBACK(7)
}

/**
  * Analog comparator ISR
  */
ISR(ANALOG_COMP_vect) {
  compFunc(); //call the user function
}

#endif
