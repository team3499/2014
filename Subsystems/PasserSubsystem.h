#ifndef __PASSER_SUBSYSTEM_H__
#define __PASSER_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class PasserSubsystem : public Subsystem {

  private:
    Solenoid * solenoid;

  public:
    PasserSubsystem();

    void Extend();
    void Retract();

    bool IsExtended();
};

#endif /* __PASSER_SUBSYSTEM_H__ */
