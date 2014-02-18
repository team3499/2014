#include "modeautonomous.h"

#include <Timer.h>

ModeAutonomous::ModeAutonomous(DriverStation *ds) : ModeBase(ds){
	OUT("Autonomous Construct");
}
ModeAutonomous::~ModeAutonomous(){
	OUT("Autonomous Destroy");
}

void ModeAutonomous::begin(){
	m_ds->InAutonomous(true);
    OUT("Autonomous Init");
    compressor->Start();
}
void ModeAutonomous::run(){
    Wait(0.005);
}
void ModeAutonomous::end(){
    compressor->Stop();
    OUT("Autonomous End");
    m_ds->InAutonomous(false);
}

const char *ModeAutonomous::typeString(){
	return "Autonomous";
}
