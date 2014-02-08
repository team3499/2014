#include "solenoidbreakout.h"

SolenoidBreakout::SolenoidBreakout()
{
    s[0] = new Solenoid(1, 1);
    s[1] = new Solenoid(1, 2);
    s[2] = new Solenoid(1, 3);
    s[3] = new Solenoid(1, 4);
    s[4] = new Solenoid(1, 5);
    s[5] = new Solenoid(1, 6);
    s[6] = new Solenoid(1, 7);
    s[7] = new Solenoid(1, 8);
}


void SolenoidBreakout::shootBall(){
    s[0]->Set(true);
    s[1]->Set(true);
    s[2]->Set(true);
    s[3]->Set(true);
    s[4]->Set(true);
}

void SolenoidBreakout::unShootBall(){
    s[0]->Set(false);
    s[1]->Set(false);
    s[2]->Set(false);
    s[3]->Set(false);
    s[4]->Set(false);
}

bool SolenoidBreakout::isBallShot(){
    return s[0]->Get();
}
