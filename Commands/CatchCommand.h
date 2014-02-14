#ifndef __CATCH_COMMAND_H__
#define __CATCH_COMMAND_H__

#include "CommandBase.h"

class CatchCommand : public CommandBase {

  public:
    CatchCommand();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif /* __CATCH_COMMAND_H__ */
