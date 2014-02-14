#include "CommandBase.h"

CommandBase::CommandBase(const char *name) : Command(name) {

}

CommandBase::CommandBase() : Command() {

}

BallDetectorSubsystem * CommandBase::ballDetectorSubsystem = NULL;
CompressorSubsystem *   CommandBase::compressorSubsystem   = NULL;
GripperSubsystem *      CommandBase::gripperSubsystem      = NULL;
PasserSubsystem *       CommandBase::passerSubsystem       = NULL;
ShooterSubsystem *      CommandBase::shooterSubsystem      = NULL;
OI *                    CommandBase::oi                    = NULL;

void CommandBase::init() {
    ballDetectorSubsystem = new BallDetectorSubsystem();
    compressorSubsystem   = new CompressorSubsystem();
    gripperSubsystem      = new GripperSubsystem();
    passerSubsystem       = new PasserSubsystem();
    shooterSubsystem      = new ShooterSubsystem();
    oi                    = new OI();
}
