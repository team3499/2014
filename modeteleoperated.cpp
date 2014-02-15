#include "modeteleoperated.h"

#include <Timer.h>

ModeTeleoperated::ModeTeleoperated(){
	
}
ModeTeleoperated::~ModeTeleoperated(){
	
}

void ModeTeleoperated::start(){
    printf("$$FRC3499$$ - Teleop Init\n");
    compressor->Start();
    use_proximity = SD_GB("PROXIMITY");
//    SetSafetyEnabled(false); //on a dev board
}
void ModeTeleoperated::run(){
    // Shooter Pistons
    if(teststick->GetTrigger()){
        airsys->shootBall();
    } else {
    	if(teststick->GetRawButton(2)){
    		airsys->shootCenter();
    	} else {
    		airsys->unShootBall();
    	}
    }
    
    // Arm Control
    if(teststick->GetRawButton(3) || (use_proximity && psensor->Get())){
    	airsys->closeArm();
    } else {
    	airsys->openArm();
    }

//    if(teststick->GetRawButton(10))
//        compressor->SetRelayValue(Relay::kOn);
//    else
//        compressor->SetRelayValue(Relay::kOff);

    SD_PN("Joystick Y", teststick->GetAxis(Joystick::kYAxis));
    if(abs(teststick->GetAxis(Joystick::kYAxis)) > 0.01){
        handstilt->Set(teststick->GetAxis(Joystick::kYAxis) * 30);
    }

//    SD_PN("Joystick Y", teststick->GetAxis(Joystick::kYAxis));
//    if(abs(teststick->GetAxis(Joystick::kYAxis)) > 0.01){
//        handstilt->Set(teststick->GetAxis(Joystick::kYAxis) * 100);
//    }

    SD_PN("Proximity Sensor", psensor->Get());
    proximityLight->Set(psensor->Get());

    dsLCD->PrintfLine(DriverStationLCD::kUser_Line4, "IO %d", compressor->GetPressureSwitchValue());

    mainLights->setFlat();
    
    Wait(0.005);
}
void ModeTeleoperated::end(){
    compressor->Stop();
    // Turn everything off.
}
