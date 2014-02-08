#include "buttonreg.h"

ButtonReg::ButtonReg(DriverStation *ds)
{
    this->ds = ds;

    sticks[0] = joysticks[0];
    sticks[1] = joysticks[1];
    sticks[2] = joysticks[2];
    sticks[3] = joysticks[3];
    sticks[4] = joysticks[4];
    sticks[5] = joysticks[5];
}
