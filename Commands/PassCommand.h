#ifndef __PASS_COMMAND_H__
#define __PASS_COMMAND_H__

#include "CommandBase.h"

class PassCommand : public CommandBase {

  private:
    Timer * timer;

    typedef enum {
        PENDING,
        OPENING,
        STARTING,
        PASSING,
        STOPPING,
        FINISHING,
        FINISHED
    } State;

    State state;

  public:
    PassCommand();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif /* __PASS_COMMAND_H__ */
