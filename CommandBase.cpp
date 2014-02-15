#include "CommandBase.h"

CommandBase::CommandBase(const char *name) : Command(name) {

}

CommandBase::CommandBase() : Command() {

}

BallDetectorSubsystem * CommandBase::ballDetectorSubsystem = NULL;
CompressorSubsystem *   CommandBase::compressorSubsystem   = NULL;
GripperSubsystem *      CommandBase::gripperSubsystem      = NULL;
ShooterSubsystem *      CommandBase::shooterSubsystem      = NULL;
TestLedSubsystem *      CommandBase::testLedSubsystem      = NULL;
OI *                    CommandBase::oi                    = NULL;

void CommandBase::init() {
    ballDetectorSubsystem = new BallDetectorSubsystem();
    compressorSubsystem   = new CompressorSubsystem();
    gripperSubsystem      = new GripperSubsystem();
    shooterSubsystem      = new ShooterSubsystem();
    testLedSubsystem      = new TestLedSubsystem();
    oi                    = new OI();
}
