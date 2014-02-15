#include "outputcommon.h"
#include "modebase.h"
#include "modedisabled.h"
#include "modeteleoperated.h"
#include "modeautonomous.h"
#include "modetest.h"

#include "arduino.h"
#include "input/jsbase.h"
#include "solenoidbreakout.h"

#include <RobotBase.h>


#ifndef BUILDING
    #include "generated.h"
#else
    #include "gen_out.h"
#endif

class RERRobot : public RobotBase, public OutputCommon {
private:
    typedef enum {
        test = 2,
        teleop = 3,
        autonomous = 4
    } mode_type;

public:
    RERRobot();
    ~RERRobot();
    void StartCompetition(); // The entry point

    //void init();
    bool modeChange(mode_type newmode);

    void initDisabled();
    void modeDisabled();
    void endDisabled();

    void initTest();
    void modeTest();
    void endTest();

    void initTeleoperated();
    void modeTeleoperated();
    void endTeleoperated();

    void initAutonomous();
    void modeAutonomous();
    void endAutonomous();

    void setupSmartDashboard();

private:
    bool disabled;
    mode_type mode;

    ModeBase *modeCode;
};
