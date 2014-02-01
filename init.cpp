#include "RERRobot.h"

#ifndef BUILDING
    #include "generated.h"
#else
    #include "gen_out.h"
#endif

void RERRobot::init(){

    dsLCD->Clear();
    dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "Running 2014 Code: "BUILD_DATE);
    dsLCD->UpdateLCD();

    compressor->Stop();
}
