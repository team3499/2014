#ifndef ARDUINO_CNTL_H
#define ARDUINO_CNTL_H

#include <PWM.h>

class ArduinoControl : public PWM {
public:
    ArduinoControl(unsigned int pwmport):
        PWM(pwmport)
    {
        SetBounds(20.0, 10.0, 10.0, 10.0, 0.0);
        SetPeriodMultiplier(kPeriodMultiplier_1X);
        SetRaw(m_centerPwm);
    }
    
    ~ArduinoControl(){}

    void setModeTeleop(){}
    void setModeAutonomous(){}
    void setModeDisabled(){}
    
    void setModeWaitCatch(){}
    void setModeBallHere(){}
    
    void unsetMode(){}
    
    void setFlat(){
        SetRaw(m_centerPwm);
    }
    
private:
    int mode;
    int modeStack;
};


#endif // #ifndef ARDUINO_CNTL_H
