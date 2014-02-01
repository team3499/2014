#include "RERRobot.h"
#include <SmartDashboard/SmartDashboard.h>

void RERRobot::modeAutonomous(){
    compressor->Start();

    while(IsAutonomous() && IsEnabled()){
        Wait(0.005);
    }

    compressor->Stop();
}
