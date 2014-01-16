#include "RERRobot.h"

void RERRobot::modeTeleoperated(){
	compressor->Start();
	while(IsOperatorControl()){
		Wait(0.005);
	}
}
