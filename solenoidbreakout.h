#ifndef SOLENOIDBREAKOUT_H
#define SOLENOIDBREAKOUT_H

#include <Solenoid.h>

class SolenoidBreakout
{
public:
    SolenoidBreakout();

    void shootBall();
    void unShootBall();
    bool isBallShot();

private:
    Solenoid **s;
};

#endif // SOLENOIDBREAKOUT_H
