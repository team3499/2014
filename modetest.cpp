#include "modetest.h"

#include <Timer.h>

#include <sysLib.h>
#include <ctime>
#include <unistd.h>

ModeTest::ModeTest(){
	
}
ModeTest::~ModeTest(){
	
}

void ModeTest::start(){
    printf("$$FRC3499$$ - Test Init\n");
    compressor->Start();
    
    test_mode = (int)SD_GN("TEST_MODE");
    
    switch(test_mode){
    case 3:
    	jaglog = new std::ofstream("/jaguar_speed.log");
    	break;
    }
}
void ModeTest::run(){
    switch(test_mode){
    case 1:
        proximityLight->Set(0);
        sleep(1);
        SD_PB("LED eh ", true);
        proximityLight->Set(1);
        sleep(2);
        break;

    case 2:
        SD_PN("3 Speed", jagFR->GetSpeed());
        SD_PN("4 Speed", jagFL->GetSpeed());
        SD_PN("2 Speed", jagRR->GetSpeed());
        SD_PN("5 Speed", jagRL->GetSpeed());

        jagFR->SetPID(SD_GN("3P"), SD_GN("3I"), SD_GN("3D"));
        jagFL->SetPID(SD_GN("4P"), SD_GN("4I"), SD_GN("4D"));
        jagRR->SetPID(SD_GN("2P"), SD_GN("2I"), SD_GN("2D"));
        jagRL->SetPID(SD_GN("5P"), SD_GN("5I"), SD_GN("5D"));

        jagFR->Set(SD_GN("3 SetSpeed"));
        jagFL->Set(SD_GN("4 SetSpeed"));
        jagRR->Set(SD_GN("2 SetSpeed"));
        jagRL->Set(SD_GN("5 SetSpeed"));
        break;
    case 3:
    {
    	float speed = 10.0;
    	jagFR->Set(speed);
    	jagFL->Set(speed);
    	jagRR->Set(speed);
    	jagRL->Set(speed);
    	
        double rawsecs = (double)clock() / (double)CLOCKS_PER_SEC;
        char buffer[20];
        sprintf(buffer, "%d", (int)(rawsecs * 1000));
    	*jaglog << buffer << " Set-" << speed << " FR-" << jagFR->GetSpeed() << " FL-" << jagFL->GetSpeed() << " RR-" << jagRR->GetSpeed() << " RL-" << jagRL->GetSpeed() << std::endl;
    	jaglog->flush();
    }
    	break;
    }
}
void ModeTest::end(){
    switch(test_mode){
    case 3:
    	jaglog->close();
    	delete jaglog;
    	break;
    }
    compressor->Stop();
}
