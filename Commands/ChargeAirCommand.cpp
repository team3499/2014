#include "ChargeAirCommand.h"

ChargeAirCommand::ChargeAirCommand() {
    Requires(compressorSubsystem);
}

void ChargeAirCommand::Initialize() {
    compressorSubsystem->Start();
}

void ChargeAirCommand::Execute() {

}

bool ChargeAirCommand::IsFinished() {
    return false;
}

void ChargeAirCommand::End() {
    compressorSubsystem->Stop();
}

void ChargeAirCommand::Interrupted() {
    End();
}
