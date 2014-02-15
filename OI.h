#ifndef __OI_H__
#define __OI_H__

#include "WPILib.h"
#include "Gamepad/Gamepad.h"
#include "Commands/Command.h"

class OI {

  private:
    Gamepad * pad;

    typedef struct {
        bool      state;
        bool      cancelOnRelease;
        Command * command;
    } ButtonInfo;

    ButtonInfo button[4];

    void ProcessButton(int n);
    void ProcessStick(int n);
    void ProcessTrigger(int n);

  public:
    OI();

    void Process();
    void AssignCommandToButton(Command * command, int n, bool cancelOnRelease = true);
};

#endif /* __OI_H__ */
