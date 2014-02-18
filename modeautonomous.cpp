#include "modeautonomous.h"

#include <Timer.h>

ModeAutonomous::ModeAutonomous(DriverStation *ds) : ModeBase(ds){
	OUT("Autonomous Construct");
	//dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Autonomous Mode");
}
ModeAutonomous::~ModeAutonomous(){
	OUT("Autonomous Destroy");
}

void ModeAutonomous::begin(){
	m_ds->InAutonomous(true);
	//dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "ENABLED");
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
