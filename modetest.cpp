#include "modetest.h"

#include <Timer.h>

#include <sysLib.h>
#include <ctime>
#include <unistd.h>

ModeTest::ModeTest(DriverStation *ds) : ModeBase(ds){
	OUT("Test Construct");
}
ModeTest::~ModeTest(){
	OUT("Test Destroy");
}

void ModeTest::begin(){
	m_ds->InTest(true);
    OUT("Test Init");
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
        //proximityLight->Set(0);
        sleep(1);
        SD_PB("LED eh ", true);
        //proximityLight->Set(1);
        sleep(2);
        break;

    case 2:

        break;
    case 3:
    {
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
    OUT("Test End");
    m_ds->InTest(false);
}

const char *ModeTest::typeString(){
	return "Test";
}
