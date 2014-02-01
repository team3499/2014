#include "RERRobot.h"

void RERRobot::modeDisabled(){
    compressor->Stop();

    while(IsDisabled()){
        Wait(0.005);
    }

}
