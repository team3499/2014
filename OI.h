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

    typedef struct {
        bool      state;
        bool      cancelOnRelease;
        double    threshold;
        Command * command;
    } TriggerInfo;

    ButtonInfo button[4];
    TriggerInfo trigger[2];

    void ProcessButton(int n);
    void ProcessStick(int n);
    void ProcessTrigger(int n);

  public:
    OI();

    void Process();
    void AssignCommandToButton(Command * command, int n, bool cancelOnRelease = true);
    void AssignCommandToTrigger(Command * command, int n, double threshold = 0.5, bool cancelOnRelease = true);
};

#endif /* __OI_H__ */
