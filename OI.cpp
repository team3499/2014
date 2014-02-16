#include "OI.h"
#include "Robotmap.h"

OI::OI() {
    pad       = new Gamepad(DRIVE_GAMEPAD_PORT);

    button[0] = (ButtonInfo){false, false, NULL};
    button[1] = (ButtonInfo){false, false, NULL};
    button[2] = (ButtonInfo){false, false, NULL};
    button[3] = (ButtonInfo){false, false, NULL};
    trigger[0] = (TriggerInfo){false, false, 0.5, NULL};
    trigger[1] = (TriggerInfo){false, false, 0.5, NULL};
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
        button[n].state = !button[n].state;
        printf("Button %d: Pressed\n", n);
        if (button[n].command != NULL) {
            button[n].command->Start();
        }
    } else if (!pad->GetNumberedButton(n+1) && button[n].state) {
        button[n].state = !button[n].state;
        printf("Button %d: Released\n", n);
        if (button[n].command != NULL && button[n].cancelOnRelease) {
            button[n].command->Cancel();
        }
    }
}

void OI::ProcessStick(int n) {

}

void OI::ProcessTrigger(int n) {
    double reading;

    if (n == 0) { reading = pad->GetLeftTrigger(); }
    else { reading = pad->GetRightTrigger(); }

    if (reading < 0.0) { reading = -reading; }

    if (reading > trigger[n].threshold && !trigger[n].state) {
        trigger[n].state = !trigger[n].state;
        printf("Trigger %d: Pressed (Reading %.2f)\n", n, reading);
        if (trigger[n].command != NULL) {
            trigger[n].command->Start();
        }
    } else if (reading < (.9*trigger[n].threshold) && trigger[n].state) {
        trigger[n].state = !trigger[n].state;
        printf("Trigger %d: Released (Reading %.2f)\n", n, reading);
        if (trigger[n].command != NULL && trigger[n].cancelOnRelease) {
            trigger[n].command->Cancel();
        }
    }
}

void OI::AssignCommandToButton(Command * command, int n, bool cancelOnRelease) {
    button[n].command         = command;
    button[n].cancelOnRelease = cancelOnRelease;
}

void OI::AssignCommandToTrigger(Command * command, int n, double threshold, bool cancelOnRelease) {
    trigger[n].command         = command;
    trigger[n].cancelOnRelease = cancelOnRelease;
    trigger[n].threshold       = threshold;
}

