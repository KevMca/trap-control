#ifndef BLDCDriver_h
#define BLDCDriver_h

#include "hardware_api.h"

/**
    BLDC driver class
*/
class BLDCDriver{
  public:
    /**
      BLDCDriver class constructor
      @param _pwmU U phase pwm pin
      @param _pwmV V phase pwm pin
      @param _pwmW W phase pwm pin
      @param _shdown shutdown pin
    */
    BLDCDriver(int _pwmU,int _pwmV,int _pwmW, int _shdown);
    
    /** Initialisation function */
  	void init();
    /** Driver disable function */
  	void disable();
    /** Driver enable function */
    void enable();

    // pin variables
  	int pwmU; // phase U pwm pin number
  	int pwmV; // phase V pwm pin number
  	int pwmW; // phase W pwm pin number
    int shdown; // shutdown pin number

    /** 
     * Set phase PWM duty
     * 
     * @param Ud - phase U duty [0,1] or FLOATING
     * @param Vd - phase V duty [0,1] or FLOATING
     * @param Wd - phase W duty [0,1] or FLOATING
    */
    void setPwm(float Ud, float Vd, float Wd);
  private:
        
};


#endif
