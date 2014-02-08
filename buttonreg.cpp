#include "buttonreg.h"

ButtonReg::ButtonReg(DriverStation *ds)
{
    this->ds = ds;

    sticks[0] = Joystick::GetStickForPort(1);
    sticks[1] = Joystick::GetStickForPort(2);
    sticks[2] = Joystick::GetStickForPort(3);
    sticks[3] = Joystick::GetStickForPort(4);
    sticks[4] = Joystick::GetStickForPort(5);
    sticks[5] = Joystick::GetStickForPort(6);
}
