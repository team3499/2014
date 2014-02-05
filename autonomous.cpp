#include "RERRobot.h"

void RERRobot::modeAutonomous(){
    compressor->Start();

    while(IsAutonomous() && IsEnabled()){
        Wait(0.005);
    }

    compressor->Stop();
}
