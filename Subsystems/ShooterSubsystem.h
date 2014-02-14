#ifndef __SHOOTER_SUBSYSTEM_H__
#define __SHOOTER_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ShooterSubsystem : public Subsystem {

  private:
    Solenoid * solenoid[5];

  public:
    ShooterSubsystem();

    void Extend();
    void Retract();

    bool IsExtended();
};

#endif /* __SHOOTER_SUBSYSTEM_H__ */
