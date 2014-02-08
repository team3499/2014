#include "solenoidbreakout.h"

SolenoidBreakout::SolenoidBreakout()
{
    // Ball shooter
    s[0] = new Solenoid(1);
    s[1] = new Solenoid(2);
    s[2] = new Solenoid(3);
    s[3] = new Solenoid(4);
    s[4] = new Solenoid(5);

    // Open/Close arm
    s[5] = new Solenoid(6);

    // Unused so far
    s[6] = new Solenoid(7);
    s[7] = new Solenoid(8);
}
SolenoidBreakout::~SolenoidBreakout(){
    delete[] s;
}

void SolenoidBreakout::openArm(){
    s[5]->Set(true);
}

void SolenoidBreakout::closeArm(){
    s[5]->Set(false);
}

bool SolenoidBreakout::isArmOpen(){
    return s[5]->Get();
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
