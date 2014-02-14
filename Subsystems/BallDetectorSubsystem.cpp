#include "BallDetectorSubsystem.h"
#include "Robotmap.h"

BallDetectorSubsystem::BallDetectorSubsystem() : Subsystem("BallDetectorSubsystem") {
    digitalInput = new DigitalInput(BALL_DETECTOR_CHANNEL);
}

bool BallDetectorSubsystem::IsDetecting() {
    return digitalInput->Get() == 0;
}
