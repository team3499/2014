#ifndef ARDUINO_H
#define ARDUINO_H

#include "const.h"
#include "ports.h"
#include <PWM.h>

class ArduinoControl : private PWM{
public:
    enum TeamColor {
        Blue = 0, Red = 1
    };
    enum LightsMode {
        Off = 0,
        Default = 1,
        Disabled = 2,
        Teleop = 3,
        Autonomous = 4,
        Test = 5,
        
        WaitCatch = 6,
        HasBall = 7
    };
    
    ArduinoControl(unsigned int pwmport, unsigned int colorport) : PWM(MAIN_SIDECAR, pwmport), mode(Default), color(false){
        PWM::SetBounds(20.0, 10.0, 10.0, 10.0, 0.0);
        PWM::SetPeriodMultiplier(PWM::kPeriodMultiplier_4X);
        PWM::SetRaw(PWM::m_centerPwm);
        
        colorchannel = new DigitalOutput(MAIN_SIDECAR, colorport);
        
        update();
    }
    
    ~ArduinoControl(){
        //delete modechannel;
        delete colorchannel;
    }

    void setMode(LightsMode newmode){
        float oldmode = mode;
        switch(newmode){
        case Off:
        case Default:
        case Disabled:
            mode = 0;
            break;
        case Teleop:
            mode = 0.2;
            break;
        case Autonomous:
        case Test:
            mode = 0.4;
            break;
        case WaitCatch:
            mode = -0.2;
            break;
        case HasBall:
            mode = -0.4;
            break;
        }
        if(oldmode != mode){
            printf("Mode changed from %f to %f\n", oldmode, mode);
        }
    }
    
    void setTeamColor(TeamColor newcolor){
        color = (bool)newcolor;
    }
    
    void update(){
        PWM::SetSpeed(mode);
        colorchannel->Set(color);
    }
    
//    void setFlat(){
//        //modechannel->SetRaw(PWM::m_centerPwm);
//    }
    
private:
    //PWM *modechannel;
    DigitalOutput *colorchannel;
    
    float mode;
    bool color;
    
};


#endif // ARDUINO_H
