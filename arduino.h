#ifndef ARDUINO_H
#define ARDUINO_H

#include <PWM.h>

class ArduinoControl : public PWM {
public:
    enum TeamColor {
        Blue = 0, Red = 1
    };
    
    ArduinoControl(unsigned int pwmport) : PWM(pwmport){
        SetBounds(20.0, 10.0, 10.0, 10.0, 0.0);
        SetPeriodMultiplier(kPeriodMultiplier_4X);
        SetRaw(m_centerPwm);
        this->SetSpeed(0);
        
        teamcolor = new DigitalOutput(4);
        setColorEh = 0;
    }
    
    ~ArduinoControl(){}

    void setModeTeleop(){ this->SetSpeed(.2);}
    void setModeAutonomous(){ this->SetSpeed(.4);}
    void setModeDisabled(){ this->SetSpeed(0);}
    
    void setModeWaitCatch(){ this->SetSpeed(-0.2);}
    void setModeBallHere(){ this->SetSpeed(-0.4);}
    
    void unsetMode(){}
    
    void setFlat(){
        SetRaw(m_centerPwm);
    }
    
    void setTeamColor(TeamColor color){
//        if(!setColorEh++) // v1
            teamcolor->Set((bool)color);
//        if(!setColorEh && !(++setColorEh)) // v2
//            teamcolor->Set((bool)color);
    }
    
private:
    int setColorEh;
    
    int mode;
    int modeStack;
    DigitalOutput *teamcolor;
};


#endif // ARDUINO_H
