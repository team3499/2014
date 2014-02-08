#ifndef BUTTONREG_H
#define BUTTONREG_H

#include <DriverStation.h>
#include <Joystick.h>
#include <stdlib.h>

class ButtonReg
{
public:
    ButtonReg(DriverStation *ds);


    void regAction(unsigned int jsPort, unsigned int button, OnInput *action);
private:
    Joystick *sticks;
    char *thing;

    DriverStation *ds;

};

#endif // BUTTONREG_H
