#include "RERRobot.h"
#include <SmartDashboard/SmartDashboard.h>

void RERRobot::modeTest(){
    compressor->Start();

    SmartDashboard::PutNumber("2P", 0.20);
    SmartDashboard::PutNumber("2I", 0.001);
    SmartDashboard::PutNumber("2D", 0.00);

    SmartDashboard::PutNumber("3P", 0.20);
    SmartDashboard::PutNumber("3I", 0.001);
    SmartDashboard::PutNumber("3D", 0.00);

    SmartDashboard::PutNumber("4P", 0.20);
    SmartDashboard::PutNumber("4I", 0.001);
    SmartDashboard::PutNumber("4D", 0.00);

    SmartDashboard::PutNumber("5P", 0.20);
    SmartDashboard::PutNumber("5I", 0.001);
    SmartDashboard::PutNumber("5D", 0.00);

    SmartDashboard::PutNumber("3 SetSpeed", 50);
    SmartDashboard::PutNumber("4 SetSpeed", 50);
    SmartDashboard::PutNumber("2 SetSpeed", 50);
    SmartDashboard::PutNumber("5 SetSpeed", 50);

    while(IsTest() && IsEnabled()){
        iotest->Set(0);
        Wait(1);
        iotest->Set(1);
        Wait(0.5);
    }

    compressor->Stop();
}
