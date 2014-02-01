#include "RERRobot.h"
#include <SmartDashboard/SmartDashboard.h>

void RERRobot::modeTeleoperated(){
    compressor->Start();
    //SetSafetyEnabled(false); //on a dev board

    while(IsOperatorControl() && IsEnabled()){

        SmartDashboard::PutNumber("3 Speed", jagFR->GetSpeed());
        SmartDashboard::PutNumber("4 Speed", jagFL->GetSpeed());
        SmartDashboard::PutNumber("2 Speed", jagRR->GetSpeed());
        SmartDashboard::PutNumber("5 Speed", jagRL->GetSpeed());

        jagFR->SetPID(SmartDashboard::GetNumber("3P"), SmartDashboard::GetNumber("3I"), SmartDashboard::GetNumber("3D"));
        jagFL->SetPID(SmartDashboard::GetNumber("4P"), SmartDashboard::GetNumber("4I"), SmartDashboard::GetNumber("4D"));
        jagRR->SetPID(SmartDashboard::GetNumber("2P"), SmartDashboard::GetNumber("2I"), SmartDashboard::GetNumber("2D"));
        jagRL->SetPID(SmartDashboard::GetNumber("5P"), SmartDashboard::GetNumber("5I"), SmartDashboard::GetNumber("5D"));

        jagFR->Set(SmartDashboard::GetNumber("3 SetSpeed"));
        jagFL->Set(SmartDashboard::GetNumber("4 SetSpeed"));
        jagRR->Set(SmartDashboard::GetNumber("2 SetSpeed"));
        jagRL->Set(SmartDashboard::GetNumber("5 SetSpeed"));

        Wait(0.005);
    }

    compressor->Stop();
}
