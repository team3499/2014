#include "modeautonomous.h"

#include <Timer.h>

ModeAutonomous::ModeAutonomous(){
	
}
ModeAutonomous::~ModeAutonomous(){
	
}

void ModeAutonomous::start(){
    printf("$$FRC3499$$ - Autonomous Init\n");
    compressor->Start();
}
void ModeAutonomous::run(){
    Wait(0.005);
}
void ModeAutonomous::end(){
    compressor->Stop();
}
