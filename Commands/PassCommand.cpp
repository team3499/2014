#include "PassCommand.h"

PassCommand::PassCommand() {
    timer = new Timer();
    Requires(gripperSubsystem);
    Requires(shooterSubsystem);
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
        if (timer->HasPeriodPassed(0.25)) { state = STARTING; }
        break;
    case STARTING:
        shooterSubsystem->ExtendCenter();
        state = PASSING;
    case PASSING:
        // Allow 0.5 seconds to perform pass
        if (timer->HasPeriodPassed(0.5)) { state = STOPPING; }
        break;
    case STOPPING:
        shooterSubsystem->Retract();
        state = FINISHING;
        break;
    case FINISHING:
        // Allow 0.5 seconds to retract
        if (timer->HasPeriodPassed(0.5)) { state = FINISHED; }
        break;
    default:
        state = FINISHED;
        break;
    }
}

bool PassCommand::IsFinished() {
    return state == FINISHED;
}

void PassCommand::End() {
    if (gripperSubsystem->IsClosed()) { gripperSubsystem->Open(); }
    if (!shooterSubsystem->IsCenterExtended()) { shooterSubsystem->Retract(); }
}

void PassCommand::Interrupted() {
    state = FINISHED;
    End();
}
