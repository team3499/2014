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
    jaglog = new JagLog("auto");
    step = 0;
    drivetime = new Timer();
    drivetime->Start();
    fr = -400;
    fl = 400;
    rr = -400;
    rl = 400;
	jagFR->Set(fr);
	jagFL->Set(fl);
	jagRR->Set(rr);
	jagRL->Set(rl);
	OUT("Autonomous start");
}
void ModeAutonomous::run(){
	switch(step){
	case 0:
		if(drivetime->HasPeriodPassed(1.0)){
			OUT("Autonomous step 0 done");
		    fr = 0;
		    fl = 0;
		    rr = 0;
		    rl = 0;
			jagFR->Set(fr);
			jagFL->Set(fl);
			jagRR->Set(rr);
			jagRL->Set(rl);
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
	if(step < 2)
		jaglog->log(fr, jagFR->GetSpeed(), fl, jagFL->GetSpeed(), rr, jagRR->GetSpeed(), rl, jagRL->GetSpeed());
}
void ModeAutonomous::end(){
    compressor->Stop();
    OUT("Autonomous End");
    m_ds->InAutonomous(false);
}

const char *ModeAutonomous::typeString(){
	return "Autonomous";
}
