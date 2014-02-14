#include "PassCommand.h"

PassCommand::PassCommand() {
    timer = new Timer();
    Requires(gripperSubsystem);
    // TODO: Requires(driveSubsystem);
}

void PassCommand::Initialize() {
    timer->Start();
    timer->Reset();
    state = PENDING;
}

void PassCommand::Execute() {
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

bool PassCommand::IsFinished() {
    return state == FINISHED;
}

void PassCommand::End() {
    gripperSubsystem->Open();
    // TODO: driveSubsystem->Stop();
}

void PassCommand::Interrupted() {
    state = FINISHED;
    End();
}
