#ifndef __BALL_DETECTOR_SUBSYSTEM_H__
#define __BALL_DETECTOR_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class BallDetectorSubsystem : public Subsystem {

  private:
    DigitalInput * digitalInput;

  public:
    BallDetectorSubsystem();

    bool IsDetecting();
};

#endif /* __BALL_DETECTOR_SUBSYSTEM_H__ */
