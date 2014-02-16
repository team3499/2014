#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/PassCommand.h"
#include "Commands/CatchCommand.h"
#include "Commands/TestLedCommand.h"
#include "Gamepad/Gamepad.h"
#include "CommandBase.h"
#include "Robotmap.h"

class Robot2014 : public IterativeRobot {

  private:
    LiveWindow * lw;
    Gamepad *    drivePad;
    Gamepad *    accessoryPad;

    PassCommand *    passCommand;
    CatchCommand *   catchCommand;
    TestLedCommand * testLedCommand;

    bool leftTriggerState;
    bool rightTriggerState;

    virtual void RobotInit() {
        CommandBase::init();
        lw = LiveWindow::GetInstance();

        drivePad       = new Gamepad(DRIVE_GAMEPAD_PORT);
        accessoryPad   = new Gamepad(ACCESSORY_GAMEPAD_PORT);
        passCommand    = new PassCommand();
        catchCommand   = new CatchCommand();
        testLedCommand = new TestLedCommand();

        CommandBase::oi->AssignCommandToTrigger(passCommand, 0);
        CommandBase::oi->AssignCommandToTrigger(catchCommand, 1);
        CommandBase::oi->AssignCommandToButton(testLedCommand, 1);
    }

    virtual void AutonomousInit() {

    }

    virtual void AutonomousPeriodic() {
        Scheduler::GetInstance()->Run();
    }

    virtual void TeleopInit() {
        leftTriggerState = drivePad->GetNumberedButton(1);
        //rightTriggerState = false;
        testLedCommand->Start();
    }

    virtual void TeleopPeriodic() {
        Scheduler::GetInstance()->Run();

        CommandBase::oi->Process();
    }

    virtual void TestPeriodic() {
        lw->Run();
    }
};

START_ROBOT_CLASS(Robot2014);

