#include "modeteleoperated.h"

#include <Timer.h>
#include <Utility.h>

#include <sysLib.h>
#include <ctime>
#include <unistd.h>

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
    
    time_t raw;
    time(&raw);
    struct tm *time;
    time = localtime(&raw);
    int mon = time->tm_mon + 1;
    int day = time->tm_mday;
    int yr = time->tm_year - 100;
    int hr = time->tm_hour;
    int min = time->tm_min;
    int sec = time->tm_sec;
    char buffer[50];
    sprintf(buffer, "/jaguar_speed_%02d/%02d/%02d_%02d:%02d:%02d.log", mon, day, yr, hr, min, sec);
    jaglog = new std::ofstream(buffer);
}
void ModeTeleoperated::run(){
	uint32_t starttime = GetFPGATime();
	
	op->jsBaseTick();
	op->jsBaseTickAxis();
	
	uint32_t inputtime = GetFPGATime();
	
	//OUT("Teleop 0");
	
	JsBase::JsAxis *axis = op->getAxisInstance();
	
	float jx = axis->leftStick.y * -1;
	float jy = axis->leftStick.x;
	
	float fr = jy - jx;
	float fl = jy + jx;
	float rr = jy - jx;
	float rl = jy + jx;
	
	fr = fr * fr * (fr > 0 ? 1 : -1);
	fl = fl * fl * (fl > 0 ? 1 : -1);
	rr = rr * rr * (rr > 0 ? 1 : -1);
	rl = rl * rl * (rl > 0 ? 1 : -1);
	
	jagFR->Set(fr);
	jagFL->Set(fl);
	jagRR->Set(rr);
	jagRL->Set(rl);
	
    float rawsecs = (float)clock() / (float)CLOCKS_PER_SEC;
    char buffer[20];
    sprintf(buffer, "%d", (int)(rawsecs * (float)1000));
	*jaglog << buffer << " " << fr << " " << jagFR->GetSpeed() << " " << fl << " " << jagFL->GetSpeed() << " " << rr << " " << jagRR->GetSpeed() << " " << rl << " " << jagRL->GetSpeed() << std::endl;
	jaglog->flush();
	
	uint32_t jagtime = GetFPGATime();
	
	//OUT("Teleop 1");
    
	JsBase::JsButtons *btns = op->getButtonsInstance();
	if(axis->trigger >= 0.5){
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
    
    SD_PN("Right Joystick Y", axis->rightStick.y);
    
    if(abs(axis->rightStick.y) > 0.1){
		handstilt->Set(axis->rightStick.y * axis->rightStick.y * (axis->rightStick.y < 0 ? 1 : -1));
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
    if(diff1 > 100 || diff2 > 30000 || diff3 > 1000){
    	printf("Run lag %d %d %d\n", diff1, diff2, diff3);
    }
    
}
void ModeTeleoperated::end(){
	jaglog->close();
	delete jaglog;
    compressor->Stop();
    OUT("Teleop End");
    m_ds->InOperatorControl(false);
}
