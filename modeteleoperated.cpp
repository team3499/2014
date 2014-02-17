#include "modeteleoperated.h"

#include <Timer.h>
#include <Utility.h>

#include <sysLib.h>
#include <ctime>
#include <unistd.h>
#include <stdio.h>

#define a(x)    ((x > 0.0) ? x : -x)
#define max(x, y) ((a(x) > a(y)) ? a(x): a(y))

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
    //OUT("Teleop init 1");
    //use_proximity = SD_GB("PROXIMITY");
    use_proximity = false;
    //OUT("Teleop init 2");

    int runCount = 9000;
    
    FILE *file = fopen("/counter", "r");
    if(file == NULL){
    	printf("Could not open file!!!!!!!!!\n");
    } else {
        fscanf(file, "%d", &runCount);
        fclose(file);
    }
    
    std::fstream *fileNumber = new std::fstream("/counter", std::ios_base::out | std::ios_base::trunc);
    printf("fileNumber write is %d\n", fileNumber->is_open());
    fileNumber->seekg(0, std::ios_base::beg);
    runCount++;
    *fileNumber << runCount;
    printf("Number written is %d\n", runCount);
    fileNumber->flush();
    delete fileNumber;
    
    char buffer[50];
    sprintf(buffer, "/JAG_SPEED_%d.log", runCount);
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
	
	//OUT("Teleop 0");

//	SD_PN("LEFT STICK AXIS X", axii->ls_x);
//	SD_PN("LEFT STICK AXIS Y", axii->ls_y);
	
	float jx = axii->leftStick.x;
	float jy = axii->leftStick.y;
	
	float fr = jy - jx;
	float fl = jy + jx;
	float rr = jy - jx;
	float rl = jy + jx;

	float mx = max( 1.000, max(max(fr, fl), max(rr, rl)));
	
	fr /= mx;
	fl /= mx;
	rr /= mx;
	rl /= mx;
	
	fr = fr * fr * (fr > 0 ? 1 : -1);
	fl = fl * fl * (fl > 0 ? 1 : -1);
	rr = rr * rr * (rr > 0 ? 1 : -1);
	rl = rl * rl * (rl > 0 ? 1 : -1);
	
	jagFR->Set(fr * 600);
	jagFL->Set(fl * 600);
	jagRR->Set(rr * 600);
	jagRL->Set(rl * 600);
	
	if(logEh){
//        float rawsecs = (float)clock() / (float)CLOCKS_PER_SEC;
//        char buffer[20];
//        sprintf(buffer, "%d", (int)(rawsecs * (float)1000));
        *jaglog << GetTime() << " " << fr * 600 << " " << jagFR->GetSpeed() << " " << fl * 600 << " " << jagFL->GetSpeed() << " " << rr * 600 << " " << jagRR->GetSpeed() << " " << rl * 600 << " " << jagRL->GetSpeed() << std::endl;
        jaglog->flush();
	}
	
	uint32_t jagtime = GetFPGATime();
	
	//OUT("Teleop 1");
    
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
        
    //OUT("Teleop 2");

    if(btns->button3){
    	airsys->openArm();
    } else {
    	airsys->closeArm();
    }
    
    //OUT("Teleop 3");
    
//    SD_PN("Right Joystick Y", axii->rightStick.y);
    
    if(abs(axii->rightStick.y) > 0.1){
		handstilt->Set(axii->rightStick.y * axii->rightStick.y * (axii->rightStick.y < 0 ? 1 : -1));
    } else {
    	handstilt->Set(0);
    }
    
    //OUT("Teleop 4");
    
//    SD_PN("Proximity Sensor", psensor->Get());
//    proximityLight->Set(psensor->Get());
    
    //OUT("Teleop 5");
    //dsLCD->PrintfLine(DriverStationLCD::kUser_Line4, "IO %d", compressor->GetPressureSwitchValue());
    //OUT("Teleop 6");
    
    mainLights->setFlat();
    
    //OUT("Teleop 7");
    //Wait(0.005);
    
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
    
    OUT("Teleop End");
    m_ds->InOperatorControl(false);
}
