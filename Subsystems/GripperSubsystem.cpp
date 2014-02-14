#include "GripperSubsystem.h"
#include "Robotmap.h"

GripperSubsystem::GripperSubsystem() : Subsystem("GripperSubsystem") {
    openSolenoid  = new Solenoid(GRIPPER_OPEN_CHANNEL);
    closeSolenoid = new Solenoid(GRIPPER_CLOSE_CHANNEL);
    jaguar        = new CANJaguar(GRIPPER_TILT_CAN_ID);
}

void GripperSubsystem::Initialize() {
    openSolenoid->Set(false);
    closeSolenoid->Set(false);

    jaguar->DisableControl();
    jaguar->ChangeControlMode(CANJaguar::kPercentVbus);
    jaguar->SetPID(0.4, 0.005, 0.0);
    jaguar->Set(0.0);
    jaguar->EnableControl();
}

void GripperSubsystem::Open() {
    closeSolenoid->Set(false);
    openSolenoid->Set(true);
}

void GripperSubsystem::Close() {
    openSolenoid->Set(false);
    closeSolenoid->Set(true);
}

void GripperSubsystem::TiltUp() {
    jaguar->Set(1.0);
}

void GripperSubsystem::TiltDown() {
    jaguar->Set(-1.0);
}

void GripperSubsystem::TiltStop() {
    jaguar->Set(0.0);
}

bool GripperSubsystem::IsOpen() {
    return openSolenoid->Get();
}

bool GripperSubsystem::IsClosed() {
    return closeSolenoid->Get();
}

bool GripperSubsystem::IsTiltedUp() {
    return !jaguar->GetForwardLimitOK();
}

bool GripperSubsystem::IsTiltedDown() {
    return !jaguar->GetReverseLimitOK();
}
