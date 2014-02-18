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

void ModeTeleoperated::init(){
	m_ds->InOperatorControl(true);
    OUT("Teleop Init");
    compressor->Start();

    int runCount = 9000;

    FILE *file = fopen("/counter", "r");
    if(file == NULL){
    	OUT("Could not open file!!!!!!!!!");
    } else {
        fscanf(file, "%d", &runCount);
        fclose(file);
    }

    std::fstream *fileNumber = new std::fstream("/counter", std::ios_base::out | std::ios_base::trunc);
    if(fileNumber == NULL){
    	OUT("COULD NOT OPEN /counter TO WRITE");
    } else {
    	fileNumber->seekg(0, std::ios_base::beg);
    	runCount++;
    	*fileNumber << runCount;
    	fileNumber->flush();
    	delete fileNumber;
    }
    
    char buffer[50];
    std::string name;
    try { name = SD_GS("JAG SPEED LOG EXT"); }
    catch(std::exception e) { OUT("THE SMART DASHBOARD FIELD \"JAG SPEED LOG EXT\" DOES NOT EXIST"); OUT("CREATE IT NOW!!!"); }

    sprintf(buffer, "/JAG_SPEED_%s_%d.log",name.c_str() , runCount);
    printf("WRITING TO FILE: \"%s\"\n", buffer);
    jaglog = new std::ofstream(buffer);
    
    if(jaglog->bad()){
    	OUT("OPENING OF THE JAGUAR LOGGING FILE !!FAILED!!");
    	logEh = false;
    } else {
    	logEh = true;
    }
    
    axii = op->getAxisInstance();
}
void ModeTeleoperated::run(){
	uint32_t starttime = GetFPGATime();
	
	op->jsBaseTick();
	op->jsBaseTickAxis();
	
	uint32_t inputtime = GetFPGATime();
	
	float jx = axii->leftStick.x;
	float jy = axii->leftStick.y;
	float dx = axii->dpad_x;
	float dy = axii->dpad_y;
	
	float fr = jy - jx - dx + dy;
	float fl = jy + jx + dx + dy;
	float rr = jy - jx + dx + dy;
	float rl = jy + jx - dx + dy;

	float mx = max( 1.000, max(max(fr, fl), max(rr, rl)));
	
	fr /= mx;
	fl /= mx;
	rr /= mx;
	rl /= mx;
	
	fr = fr * fr * (fr > 0 ? 1 : -1);
	fl = fl * fl * (fl > 0 ? 1 : -1);
	rr = rr * rr * (rr > 0 ? 1 : -1);
	rl = rl * rl * (rl > 0 ? 1 : -1);

	fr *= 600; // multiply by wheel constant
	fl *= 600; // multiply by wheel constant
	rr *= 600; // multiply by wheel constant
	rl *= 600; // multiply by wheel constant

	fr = (abs(fr) > 30 ? fr : 0.0);
	fl = (abs(fl) > 30 ? fl : 0.0);
	rr = (abs(rr) > 30 ? rr : 0.0);
	rl = (abs(rl) > 30 ? rl : 0.0);
	
	if(fr != 0.0) jagFR->Set(fr);
	if(fl != 0.0) jagFL->Set(fl);
	if(rr != 0.0) jagRR->Set(rr);
	if(rl != 0.0) jagRL->Set(rl);
	
	if(logEh){
        *jaglog << GetTime() << " " << fr << " " << jagFR->GetSpeed() << " " << fl << " " << jagFL->GetSpeed() << " " << rr << " " << jagRR->GetSpeed() << " " << rl << " " << jagRL->GetSpeed() << std::endl;
        jaglog->flush();
	}
	
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
    proximityLight->Set(psensor->Get());
    
    mainLights->setFlat();

    int diff1 = inputtime - starttime;
    int diff2 = jagtime - inputtime;
    int diff3 = GetFPGATime() - jagtime;
//    if(diff1 > 55 || diff2 > 20000 || diff3 > 600){ // These are the low cutoffs
//    if(diff1 > 200 || diff2 > 25000 || diff3 > 3700){ // These are the medium cutoffs aka the 'more than one other task have been scheduled during this time mark, or something went wrong...'
    if(diff1 > 200 || diff2 > 25000 || diff3 > 3700){
    	printf("Run lag %d %d %d\n", diff1, diff2, diff3);
    }
    
}
void ModeTeleoperated::end(){
	jaglog->close();
	delete jaglog;
    compressor->Stop();
    
    // clear output to other things
    jagFR->Set(0.0);
    jagFL->Set(0.0);
    jagRR->Set(0.0);
    jagRL->Set(0.0);
    
    handstilt->Set(0.0);
    
    OUT("Teleop End");
    m_ds->InOperatorControl(false);
}
