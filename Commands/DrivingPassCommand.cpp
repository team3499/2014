#include "DrivingPassCommand.h"

DrivingPassCommand::DrivingPassCommand() {
    timer = new Timer();
    Requires(gripperSubsystem);
    // TODO: Requires(driveSubsystem);
}

void DrivingPassCommand::Initialize() {
    timer->Start();
    timer->Reset();
    state = PENDING;
}

void DrivingPassCommand::Execute() {
    switch (state) {
    case PENDING:
        gripperSubsystem->Open();
        state = OPENING;
        break;
    case OPENING:
        // Open the gripper for 0.25 seconds before passing
        if (timer->HasPeriodPassed(0.25)) { state == STARTING; }
        break;
    case STARTING:
        // TODO: driveSubsystem->DriveForward();
        state = PASSING;
    case PASSING:
        // Drive for 0.5 seconds to perform pass
        if (timer->HasPeriodPassed(0.5)) { state == STOPPING; }
        break;
    case STOPPING:
        // TODO: driveSubsystem->Stop();
        state = FINISHED;
        break;
    default:
        state = PENDING;
        break;
    }
}

bool DrivingPassCommand::IsFinished() {
    return state == FINISHED;
}

void DrivingPassCommand::End() {
    gripperSubsystem->Open();
    // TODO: driveSubsystem->Stop();
}

void DrivingPassCommand::Interrupted() {
    state = FINISHED;
    End();
}
