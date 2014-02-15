#include "OI.h"
#include "Robotmap.h"

OI::OI() {
    pad       = new Gamepad(DRIVE_GAMEPAD_PORT);

    button[0] = (ButtonInfo){false, false, NULL};
    button[1] = (ButtonInfo){false, false, NULL};
    button[2] = (ButtonInfo){false, false, NULL};
    button[3] = (ButtonInfo){false, false, NULL};
}

void OI::Process() {
    ProcessStick(0);
    ProcessStick(1);
    ProcessButton(0);
    ProcessButton(1);
    ProcessButton(2);
    ProcessButton(3);
    ProcessTrigger(0);
    ProcessTrigger(1);
}

void OI::ProcessButton(int n) {
    if (pad->GetNumberedButton(n+1) && !button[n].state) {
        button[n].state = !(button[n].state);
        printf("Button %d: Pressed\n", n);
        if (button[n].command != NULL) {
            button[n].command->Start();
        }
    } else if (!pad->GetNumberedButton(n+1) && button[n].state) {
        button[n].state = !(button[n].state);
        printf("Button %d: Released\n", n);
        if (button[n].command != NULL && button[n].cancelOnRelease) {
            button[n].command->Cancel();
        }
    }
}

void OI::ProcessStick(int n) {

}

void OI::ProcessTrigger(int n) {

}

void OI::AssignCommandToButton(Command * command, int n, bool cancelOnRelease) {
    button[n].command         = command;
    button[n].cancelOnRelease = cancelOnRelease;
}

