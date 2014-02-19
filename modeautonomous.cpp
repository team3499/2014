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
    step = 0;
    drivetime = new Timer();
    drivetime->Start();
    drivesys->setOutputs(-400.0, 400.0, 400.0, -400.0);
	OUT("Autonomous start");
}
void ModeAutonomous::run(){
	switch(step){
	case 0:
		if(drivetime->HasPeriodPassed(1.0)){
			OUT("Autonomous step 0 done");
		    drivesys->setOutputs(0, 0, 0, 0);
			++step;
			drivetime->Reset();
			drivetime->Start();
		}
		break;
	case 1:
		OUT("Autonomous done");
		++step;
		break;
	}
}
void ModeAutonomous::end(){
    compressor->Stop();
    OUT("Autonomous End");
    m_ds->InAutonomous(false);
}

const char *ModeAutonomous::typeString(){
	return "Autonomous";
}
