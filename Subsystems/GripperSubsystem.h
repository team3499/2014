#ifndef __GRIPPER_SUBSYSTEM_H__
#define __GRIPPER_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class GripperSubsystem : public Subsystem {

  private:
    Solenoid  * openSolenoid;
    Solenoid  * closeSolenoid;
    CANJaguar * jaguar;

  public:
    GripperSubsystem();

    void Initialize();

    void Open();
    void Close();
    void TiltUp();
    void TiltDown();
    void TiltStop();

    bool IsOpen();
    bool IsClosed();
    bool IsTiltedUp();
    bool IsTiltedDown();
};

#endif /* __GRIPPER_SUBSYSTEM_H__ */
