#include "ShooterSubsystem.h"
#include "Robotmap.h"

ShooterSubsystem::ShooterSubsystem() : Subsystem("ShooterSubsystem") {
    solenoid[0] = new Solenoid(SHOOTER_UPPER_LEFT_CHANNEL);
    solenoid[1] = new Solenoid(SHOOTER_UPPER_RIGHT_CHANNEL);
    solenoid[2] = new Solenoid(SHOOTER_CENTER_CHANNEL);
    solenoid[3] = new Solenoid(SHOOTER_LOWER_LEFT_CHANNEL);
    solenoid[4] = new Solenoid(SHOOTER_LOWER_RIGHT_CHANNEL);
}

void ShooterSubsystem::Extend() {
    solenoid[2]->Set(true);
    solenoid[0]->Set(true);
    solenoid[4]->Set(true);
    solenoid[1]->Set(true);
    solenoid[3]->Set(true);
}

void ShooterSubsystem::Retract() {
    solenoid[2]->Set(false);
    solenoid[0]->Set(false);
    solenoid[4]->Set(false);
    solenoid[1]->Set(false);
    solenoid[3]->Set(false);
}

bool ShooterSubsystem::IsExtended() {
    return solenoid[2]->Get();
}
