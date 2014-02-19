#include "modeteleoperated.h"

#include <Timer.h>
#include <Utility.h>

#include <sysLib.h>
#include <ctime>
#include <unistd.h>
#include <stdio.h>

#define abs(x)    ((x > 0.0) ? x : -x)
#define max(x, y) ((abs(x) > abs(y)) ? abs(x): abs(y))

ModeTeleoperated::ModeTeleoperated(DriverStation *ds) : ModeBase(ds){
	OUT("Teleop Construct");
}
ModeTeleoperated::~ModeTeleoperated(){
	OUT("Teleop Destroy");
}

void ModeTeleoperated::begin(){
	m_ds->InOperatorControl(true);
    OUT("Teleop Init");
    compressor->Start();
    
    axii = op->getAxisInstance();
}
void ModeTeleoperated::run(){
	uint32_t starttime = GetFPGATime();
	
	op->jsBaseTick();
	op->jsBaseTickAxis();
	
	uint32_t inputtime = GetFPGATime();
	
	drivesys->vroomvrum();
	
	uint32_t jagtime = GetFPGATime();
	
	JsBase::JsButtons *btns = op->getButtonsInstance();
	if(axii->trigger >= 0.5){
		airsys->shootBall();
	} else {
		if(btns->button2){
			airsys->shootCenter();
		} else {
			airsys->unShootBall();
		}
	}
    if(btns->button3){
    	airsys->openArm();
    } else {
    	airsys->closeArm();
    }
    
    if(abs(axii->rightStick.y) > 0.1){
		handstilt->Set(axii->rightStick.y * axii->rightStick.y * (axii->rightStick.y < 0 ? 1 : -1));
    } else {
    	handstilt->Set(0);
    }
    
    SD_PN("Proximity Sensor", psensor->Get());
    
    mainLights->setFlat();

    int pretcptime = GetFPGATime();
//    char *tcpdata;
//    sprintf(tcpdata, "Run lag %d %d %d\n", inputtime - starttime, jagtime - inputtime, pretcptime - jagtime);
//    tcpc->send(tcpdata, strlen(tcpdata));
    // This will crash the robot code.
    
    int diff1 = inputtime - starttime;
    int diff2 = jagtime - inputtime;
    int diff3 = pretcptime - jagtime;
    int diff4 = GetFPGATime() - pretcptime;
//    if(diff1 > 55 || diff2 > 20000 || diff3 > 600){ // These are the low cutoffs
//    if(diff1 > 200 || diff2 > 25000 || diff3 > 3700){ // These are the medium cutoffs aka the 'more than one other task have been scheduled during this time mark, or something went wrong...'
    if(diff1 > 200 || diff2 > 25000 || diff3 > 3700 || diff4 > 0){
    	printf("Run lag %d %d %d %d\n", diff1, diff2, diff3, diff4);
    }
    
}
void ModeTeleoperated::end(){
	delete jaglog;
    compressor->Stop();
    
    // clear output to other things
    drivesys->tchunk();
    
    handstilt->Set(0.0);
    
    OUT("Teleop End");
    m_ds->InOperatorControl(false);
}

const char *ModeTeleoperated::typeString(){
	return "Teleoperated";
}
