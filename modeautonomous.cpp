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
    OUT("Autonomous Begin");
    compressor->Start();
    
    mainLights->setModeAutonomous();
    
    step = 0;
    drivetime = new Timer();
    
    drivesys->checkDead();
    drivesys->setPID(0.200, 0.001, 0.002);
}
void ModeAutonomous::run(){
    // clear
    airsys->unShootBall();
    
    switch(step){
    case 0:
        OUT("Autonomous steps start");
        drivesys->setOutputs(350.0, 350.0, 350.0, 350.0);
        drivetime->Start();
        ++step;
        break;
    case 1:
        if(drivetime->HasPeriodPassed(1.0)){
            OUT("Autonomous step 0 done");
            drivesys->tchunk();
            drivetime->Stop();
            ++step;
        } else {
            drivesys->setOutputs(350.0, 350.0, 350.0, 350.0);
        }
        break;
    case 2:
        OUT("Autonomous steps done");
        ++step;
        break;
    }
}
void ModeAutonomous::end(){
    compressor->Stop();
    OUT("Autonomous End");
    m_ds->InAutonomous(false);
    
    drivesys->tchunk(); // this should already be done... but just in case...
    drivesys->resetPID();
}

const char *ModeAutonomous::typeString(){
    return "Autonomous";
}
