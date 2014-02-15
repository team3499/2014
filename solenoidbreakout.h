#ifndef SOLENOIDBREAKOUT_H
#define SOLENOIDBREAKOUT_H

#include <Solenoid.h>

class SolenoidBreakout
{
public:
    SolenoidBreakout();
    ~SolenoidBreakout();

    // Shooter
    void shootBall();
    void shootCenter();
    void unShootBall();
    bool isBallShot();

    // Arm
    void openArm();
    void closeArm();
    bool isArmOpen();

private:
    Solenoid *s1;
    Solenoid *s2;
    Solenoid *s3;
    Solenoid *s4;
    Solenoid *s5;
    Solenoid *s6;
    Solenoid *s7;
    Solenoid *s8;
};

#endif // SOLENOIDBREAKOUT_H
