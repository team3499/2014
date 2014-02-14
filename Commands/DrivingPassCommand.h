#ifndef __DRIVING_PASS_COMMAND_H__
#define __DRIVING_PASS_COMMAND_H__

#include "CommandBase.h"

class DrivingPassCommand : public CommandBase {

  private:
    Timer * timer;

    typedef enum {
        PENDING,
        OPENING,
        STARTING,
        PASSING,
        STOPPING,
        FINISHED
    } State;

    State state;

  public:
    DrivingPassCommand();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif /* __DRIVING_PASS_COMMAND_H__ */
