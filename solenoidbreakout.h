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
    void unShootBall();
    bool isBallShot();

    // Arm
    void openArm();
    void closeArm();
    bool isArmOpen();

private:
    Solenoid **s;
};

#endif // SOLENOIDBREAKOUT_H
