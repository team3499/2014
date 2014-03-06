#ifndef RERROBOT_H
#define RERROBOT_H

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
        unknown = 0,
        test = 1,
        teleop = 2,
        autonomous = 3
    } mode_type;

public:
    RERRobot();
    ~RERRobot();
    void setup();
    void StartCompetition(); // The entry point
    void setupSmartDashboard();

private:
    bool disabled;
    mode_type mode;

    ModeBase *enabledMode;
    ModeBase *disabledMode;
    
    int cyclecounter;
    double lastcycle;
    double compound;
};

#endif // RERROBOT_H
