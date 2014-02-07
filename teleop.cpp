#include "RERRobot.h"

void RERRobot::modeTeleoperated(){
    compressor->Start();
    //SetSafetyEnabled(false); //on a dev board

    int i = 0;

    SD_PB("Testing i eh", false);
    SD_PN("Testing i eh?", 0.0);

    SD_PN("IsOperatorControl eh?", IsOperatorControl());
    SD_PN("IsEnabled eh?", IsEnabled());

    while(IsOperatorControl() && IsEnabled()){

        SD_PN("3 Speed", jagFR->GetSpeed());
        SD_PN("4 Speed", jagFL->GetSpeed());
        SD_PN("2 Speed", jagRR->GetSpeed());
        SD_PN("5 Speed", jagRL->GetSpeed());

        jagFR->SetPID(SD_GN("3P"), SD_GN("3I"), SD_GN("3D"));
        jagFL->SetPID(SD_GN("4P"), SD_GN("4I"), SD_GN("4D"));
        jagRR->SetPID(SD_GN("2P"), SD_GN("2I"), SD_GN("2D"));
        jagRL->SetPID(SD_GN("5P"), SD_GN("5I"), SD_GN("5D"));

        jagFR->Set(SD_GN("3 SetSpeed"));
        jagFL->Set(SD_GN("4 SetSpeed"));
        jagRR->Set(SD_GN("2 SetSpeed"));
        jagRL->Set(SD_GN("5 SetSpeed"));

        iotest->Set(i < 50);

        testjag->Set((float)(i-50)/100.0);

        ++i;
        if(i == 100){
            SD_PB("Testing i eh", true);
            SD_PN("Testing i eh?", 1.0);
        } else if (i == 50){
            SD_PB("Testing i eh", false);
            SD_PN("Testing i eh?", 0.0);
        }
        i %= 100;

        Wait(0.005);
    }

    compressor->Stop();
}
