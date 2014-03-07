#include "modeteleoperated.h"

#include <Timer.h>
#include <Utility.h>

#include <sysLib.h>
#include <ctime>
#include <unistd.h>
#include <stdio.h>

ModeTeleoperated::ModeTeleoperated(DriverStation *ds) : ModeBase(ds), lockarms(false), showlag(false){
    OUT("Teleop Construct");
}
ModeTeleoperated::~ModeTeleoperated(){
    OUT("Teleop Destroy");
}

void ModeTeleoperated::begin(){
    m_ds->InOperatorControl(true);    
    OUT("Teleop Begin");
    compressor->Start();
    
    mainLights->setMode(ArduinoControl::Teleop);
    
    lockarms = false;
    //holdlights = false;
    shootball = false;
    passball = false;
    
    drivesys->checkDead();
    
    showlag = SD_GB("SHOW_LAG_OUTPUT");
    shooter_delay = SD_GN("SHOOTER_DELAY");
    timeout_started = false;
    
    axii = op->getAxisInstance();
    btns = op->getButtonsInstance();
    
    airsys->unShootBall();
}

void ModeTeleoperated::run(){
    uint32_t starttime = GetFPGATime();
    
    op->jsBaseTick();
    op->jsBaseTickAxis();
    
    uint32_t inputtime = GetFPGATime();
    
    // Drive
    drivesys->vroomvrum();
    
    uint32_t jagtime = GetFPGATime();
    
    mainLights->setMode(ArduinoControl::Teleop);
    
    // Arm open/close/latch
    if(btns->button5){
        openarms = true;
        lockarms = false;
    } else {
        if(btns->button3){
            if(lockarms || psensor->Get() == 0){
                openarms = false;
                lockarms = true;
                mainLights->setMode(ArduinoControl::HasBall);
            } else {
                openarms = true;
                mainLights->setMode(ArduinoControl::WaitCatch);
            }
        } else {
            openarms = false;
            lockarms = false;
        }
    }
    
    // Piston shoot/pass/delay
    if(btns->button4){
        shootball = true;
        passball = false;
        
        // cancel any timeout
        shooter_timeout.Stop();
        timeout_started = false;
    } else if(btns->button6){
        passball = true;
        shootball = false;
        
        shooter_timeout.Stop();
        timeout_started = false;
    } else {
        
        // Shooter timeout logic
        if(axii->trigger >= 0.5){
            openarms = true;
            // Check if timeout has started
            if(timeout_started){
                // Check if timeout has passed
                if(shooter_timeout.HasPeriodPassed(shooter_delay)){
                    OUT("Shoot!");
                    // Shoot ball
                    shootball = true;
                    passball = false;
                }
            } else {
                OUT("Wait to shoot...");
                // Start timeout
                shooter_timeout.Reset();
                shooter_timeout.Start();
                timeout_started = true;
            }
        } else {
            if(__builtin_expect(timeout_started, 0)){
                OUT("Stop Wait");
                shooter_timeout.Stop();
                timeout_started = false;
            }
            //openarms = false;
            shootball = false;
            passball = false;
        }
    }
    
//    // Reset
//    openarms = false;
//        
//    // Arm open/close/latch
//    if(btns->button5){
//        openarms = true;
//        lockarms = false;
//    } else {
//        if(btns->button3){
//            if(lockarms || psensor->Get() == 0){
//                openarms = false;
//                lockarms = true;
//                mainLights->setModeBallHere();
//            } else {
//                openarms = true;
//                mainLights->setModeWaitCatch();
//            }
//        } else {
//            openarms = false;
//            lockarms = false;
//            mainLights->setModeTeleop();
//        }
//    }
//    
//    // Reset
//    shootball = false;
//    passball = false;
//    
//    // Piston shoot/pass/delay
//    if(btns->button4){
//        shootball = true;
//        
//        // cancel any timeout
//        shooter_timeout.Stop();
//        timeout_started = false;
//    } else if(btns->button6){
//        passball = true;
//        
//        shooter_timeout.Stop();
//        timeout_started = false;
//    } else {
//        
//        // Shooter timeout logic
//        if(axii->trigger >= 0.5){
//            openarms = true;
//            // Check if timeout has started
//            if(timeout_started){
//                // Check if timeout has passed
//                if(shooter_timeout.HasPeriodPassed(shooter_delay)){
//                    //OUT("Shoot!");
//                    // Shoot ball
//                    shootball = true;
//                }
//            } else {
//                //OUT("Wait to shoot...");
//                // Start timeout
//                shooter_timeout.Reset();
//                shooter_timeout.Start();
//                timeout_started = true;
//            }
//        } else {
//            if(timeout_started){
//                //OUT("Stop Wait");
//                shooter_timeout.Stop();
//                timeout_started = false;
//            }
//            //openarms = false;
//        }
//    }
    
    // Publish control logic
    if(openarms)
        airsys->openArm();
    else
        airsys->closeArm();
    
    if(shootball)
        airsys->shootBall();
    else if(passball)
        airsys->shootCenter();
    else
        airsys->unShootBall();
        
    // Arm tilt
    if(drivesys->isNotDead()){
        if(absf(axii->rightStick.y) > 0.1){
            handstilt->Set(axii->rightStick.y * axii->rightStick.y * (axii->rightStick.y > 0 ? 1 : -1));
        } else {
            handstilt->Set(0);
        }
    }
    
    //SD_PN("Proximity Sensor", psensor->Get());
    
    //mainLights->setFlat();

    int pretcptime = GetFPGATime();
//    char *tcpdata;
//    sprintf(tcpdata, "Run lag %d %d %d\n", inputtime - starttime, jagtime - inputtime, pretcptime - jagtime);
//    tcpc->send(tcpdata, strlen(tcpdata));
    // This will crash the robot code.
    
    uint32_t diff1 = inputtime - starttime;
    uint32_t diff2 = jagtime - inputtime;
    uint32_t diff3 = pretcptime - jagtime;
    uint32_t diff4 = GetFPGATime() - pretcptime;
//    if(diff1 > 55 || diff2 > 20000 || diff3 > 600){ // These are the low cutoffs
//    if(diff1 > 200 || diff2 > 25000 || diff3 > 3700){ // These are the medium cutoffs aka the 'more than one other task have been scheduled during this time mark, or something went wrong...'
    if(diff1 > 200 || diff2 > 25000 || diff3 > 3700 || diff4 > 40){
        if(showlag)
            printf("Run lag %d %d %d %d\n", (int)diff1, (int)diff2, (int)diff3, (int)diff4);
    }
    
}
void ModeTeleoperated::end(){
    // clear output to other things
    drivesys->tchunk();
    
    if(drivesys->isNotDead())
        handstilt->Set(0.0);
    
    compressor->Stop();
    OUT("Teleop End");
    m_ds->InOperatorControl(false);
}

const char *ModeTeleoperated::typeString(){
    return "Teleoperated";
}
