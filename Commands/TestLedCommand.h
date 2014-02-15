#ifndef __TEST_LED_COMMAND_H__
#define __TEST_LED_COMMAND_H__

#include "CommandBase.h"

class TestLedCommand : public CommandBase {

  public:
    TestLedCommand();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif /* __TEST_LED_COMMAND_H__ */
