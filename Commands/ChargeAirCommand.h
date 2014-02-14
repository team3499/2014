#ifndef __CHARGE_AIR_COMMAND_H__
#define __CHARGE_AIR_COMMAND_H__

#include "CommandBase.h"

class ChargeAirCommand : public CommandBase {

  public:
    ChargeAirCommand();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif /* __CHARGE_AIR_COMMAND_H__ */
