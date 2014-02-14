#ifndef __COMMAND_BASE_H__
#define __COMMAND_BASE_H__

#include "Commands/Command.h"
#include "Subsystems/BallDetectorSubsystem.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Subsystems/GripperSubsystem.h"
#include "Subsystems/ShooterSubsystem.h"
#include "OI.h"


class CommandBase : public Command {

  public:
    CommandBase(const char *name);
    CommandBase();

    static void init();

    static BallDetectorSubsystem * ballDetectorSubsystem;
    static CompressorSubsystem *   compressorSubsystem;
    static GripperSubsystem *      gripperSubsystem;
    static ShooterSubsystem *      shooterSubsystem;
    static OI *                    oi;
};

#endif /* __COMMAND_BASE_H__ */
