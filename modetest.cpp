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
    OUT("Test Begin");
    compressor->Start();
    drivesys->checkDead();
    
    test_mode = (int)SD_GN("TEST_MODE");
    
    switch(test_mode){
    case 4:
        arm_step = 0;
        arm_count = 0;
        armtime = new Timer();
        armtime->Start();
        jaglog = new JagLog("armtest_01down_noball");
        OUT("starting noball test");
        armspeed = -0.8;
        break;
    }
}
void ModeTest::run(){
    switch(test_mode){
    case 1:
        switch((int)SD_GN("TEST_SUB_MODE")){
        case 0:
            mainLights->setModeTeleop();
            break;
        case 1:
            mainLights->setModeDisabled();
            break;
        case 2:
            mainLights->setModeAutonomous();
            break;
        case 3:
            mainLights->setModeWaitCatch();
            break;
        case 4:
            mainLights->setModeBallHere();
            break;
        default:
            mainLights->setModeDisabled();
            break;
        }
        break;
    case 4:
        switch(arm_step){
        case 0:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_02up_noball");
                armspeed = armspeed * -1;
            }
            break;
        case 1:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_03down_noball");
                armspeed = armspeed * -1;
            }
            break;
        case 2:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_04up_noball");
                armspeed = armspeed * -1;
            }
            break;
        case 3:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_05down_noball");
                armspeed = armspeed * -1;
            }
            break;
        case 4:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_06up_noball");
                armspeed = armspeed * -1;
            }
            break;
        case 5:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                OUT("noball done, put ball in arm...");
                armspeed = armspeed * -1;
            }
            break;
        case 6:
            if(armtime->HasPeriodPassed(10)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_07down_ball");
                OUT("starting ball test");
                armspeed = armspeed * -1;
            }
            break;
        case 7:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_08up_ball");
                armspeed = armspeed * -1;
            }
            break;
        case 8:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_09down_ball");
                armspeed = armspeed * -1;
            }
            break;
        case 9:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_10up_ball");
                armspeed = armspeed * -1;
            }
            break;
        case 10:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_11down_ball");
                armspeed = armspeed * -1;
            }
            break;
        case 11:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                delete jaglog;
                jaglog = new JagLog("armtest_12up_ball");
                armspeed = armspeed * -1;
            }
            break;
        case 12:
            if(armtime->HasPeriodPassed(2)){
                armtime->Reset();
                ++arm_step;
                armspeed = 0;
                OUT("ball done");
            }
            break;
        }
        break;
    }
    
    handstilt->Set(armspeed);
    
    if(arm_step < 13){
        jaglog->logArm(armspeed, handstilt->GetOutputCurrent());
    }
}
void ModeTest::end(){
    switch(test_mode){
    case 4:
        delete armtime;
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
