#ifndef ARDUINO_H
#define ARDUINO_H

#include <PWM.h>
#include <DigitalOutput.h>

class ArduinoControl : private PWM {
public:

    enum TeamColor {
        TeamBlue = 0, TeamRed = 1
    };

    ArduinoControl(unsigned int pwmport) : PWM(pwmport){
        SetBounds(20.0, 10.0, 10.0, 10.0, 0.0);
        SetPeriodMultiplier(kPeriodMultiplier_4X);
        SetRaw(m_centerPwm);
        this->SetSpeed(0);

        do = new DigitalOutput(8);
    }
    
    ~ArduinoControl(){
        delete do;
    }

    void setModeTeleop(){
    	this->SetSpeed(.2);
    }
    void setModeAutonomous(){
    	this->SetSpeed(.4);
    }
    void setModeDisabled(){
    	this->SetSpeed(0);
    }
    
    void setModeWaitCatch(){
    	this->SetSpeed(-0.2);
    }
    void setModeBallHere(){
    	this->SetSpeed(-0.4);
    }
    
    void setFlat(){
        SetRaw(m_centerPwm);
    }

    void setTeamColor(TeamColor color){
        do->set((bool) color);
    }

    
private:
    DigitalOutput *do;
};


#endif // ARDUINO_H
