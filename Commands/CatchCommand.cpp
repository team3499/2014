#include "CatchCommand.h"

CatchCommand::CatchCommand() {
    Requires(gripperSubsystem);
    Requires(ballDetectorSubsystem);
}

void CatchCommand::Initialize() {
    gripperSubsystem->Open();
}

void CatchCommand::Execute() {
    if (ballDetectorSubsystem->IsDetecting()) {
        gripperSubsystem->Close();
    }
}

bool CatchCommand::IsFinished() {
    return false;
}

void CatchCommand::End() {
    gripperSubsystem->Open();
}

void CatchCommand::Interrupted() {
    End();
}
