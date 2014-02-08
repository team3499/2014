#include "solenoidbreakout.h"

SolenoidBreakout::SolenoidBreakout()
{
    // Ball shooter
    s1 = new Solenoid(1);
    s2 = new Solenoid(2);
    s3 = new Solenoid(3);
    s4 = new Solenoid(4);
    s5 = new Solenoid(5);

    // Open/Close arm
    s6 = new Solenoid(6);

    // Unused so far
    s7 = new Solenoid(7);
    s8 = new Solenoid(8);
}
SolenoidBreakout::~SolenoidBreakout(){
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
    delete s6;
    delete s7;
    delete s8;
}

void SolenoidBreakout::openArm(){
    s6->Set(true);
}

void SolenoidBreakout::closeArm(){
    s6->Set(false);
}

bool SolenoidBreakout::isArmOpen(){
    return s6->Get();
}

void SolenoidBreakout::shootBall(){
    s1->Set(true);
    s2->Set(true);
    s3->Set(true);
    s4->Set(true);
    s5->Set(true);
}

void SolenoidBreakout::unShootBall(){
    s1->Set(false);
    s2->Set(false);
    s3->Set(false);
    s4->Set(false);
    s5->Set(false);
}

bool SolenoidBreakout::isBallShot(){
    return s1->Get();
}
