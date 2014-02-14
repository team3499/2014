#include "PasserSubsystem.h"
#include "Robotmap.h"

PasserSubsystem::PasserSubsystem() : Subsystem("PasserSubsystem") {
    solenoid = new Solenoid(PASSER_CHANNEL);
}

void PasserSubsystem::Extend() {
    solenoid->Set(true);
}

void PasserSubsystem::Retract() {
    solenoid->Set(false);
}

bool PasserSubsystem::IsExtended() {
    solenoid->Get();
}
