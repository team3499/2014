#ifndef __TEST_LED_SUBSYSTEM_H__
#define __TEST_LED_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class TestLedSubsystem : public Subsystem {

  private:
    DigitalOutput * digitalOutput;
    bool            state;

  public:
    TestLedSubsystem();

    void Set(bool state);
    bool Get();
};

#endif /* __TEST_LED_SUBSYSTEM_H__ */
