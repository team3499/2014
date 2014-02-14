#ifndef __OI_H__
#define __OI_H__

#include "WPILib.h"
#include "Gamepad/Gamepad.h"

class OI {

  private:

  public:
    OI();

    Gamepad * drivePad;
    Gamepad * accessoryPad;
};

#endif /* __OI_H__ */
