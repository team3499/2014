#ifndef BUTTONREG_H
#define BUTTONREG_H

#include <DriverStation.h>
#include <Joystick.h>
#include <stdlib.h>

#include "../action.h"

class ButtonReg
{
public:
    struct JsButtons{
        ;
    };

    ButtonReg(DriverStation *ds);

    void regAction(unsigned int jsPort, unsigned int button, Action *action);
private:
    Joystick *sticks;
    char *thing;

    DriverStation *ds;

    Action **actions;
    ;

};

#endif // BUTTONREG_H
