#ifndef BUTTONREG_H
#define BUTTONREG_H

#include <DriverStation.h>
#include <Joystick.h>
#include <stdlib.h>

#include "../action.h"

class ButtonReg
{
public:
    ButtonReg();

    void regAction(unsigned int jsPort, unsigned int button, Action *action);
private:

    Action **actions;
};

#endif // BUTTONREG_H
