#include "OI.h"
#include "Robotmap.h"

OI::OI() {
    // Process operator interface input here.
    drivePad     = new Gamepad(DRIVE_GAMEPAD_PORT);
    accessoryPad = new Gamepad(ACCESSORY_GAMEPAD_PORT);
}
