#include "RERRobot.h"
#include <SmartDashboard/SmartDashboard.h>

void RERRobot::modeTest(){
    compressor->Start();

    SD_PN("2P", 0.20);
    SD_PN("2I", 0.001);
    SD_PN("2D", 0.00);

    SD_PN("3P", 0.20);
    SD_PN("3I", 0.001);
    SD_PN("3D", 0.00);

    SD_PN("4P", 0.20);
    SD_PN("4I", 0.001);
    SD_PN("4D", 0.00);

    SD_PN("5P", 0.20);
    SD_PN("5I", 0.001);
    SD_PN("5D", 0.00);

    SD_PN("3 SetSpeed", 50);
    SD_PN("4 SetSpeed", 50);
    SD_PN("2 SetSpeed", 50);
    SD_PN("5 SetSpeed", 50);

    while(IsTest() && IsEnabled()){
        SD_PB("LED eh ", false);
        iotest->Set(0);
        Wait(1);
        SD_PB("LED eh ", true);
        iotest->Set(1);
        Wait(0.5);
    }

    compressor->Stop();
}
