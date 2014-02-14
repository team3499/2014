#include "RERRobot.h"
#include <DriverStation.h>
#include <NetworkCommunication/UsageReporting.h>
#include <Timer.h>
#include <LiveWindow/LiveWindow.h>
#include <networktables/NetworkTable.h>
#include <csignal>
#include <unistd.h>

#include <WPILib.h>

#include "solenoidbreakout.h"

#define abs(x) (x < 0 ? -x : x) 

RERRobot::RERRobot(){
    // Initialize all of the members
    dsLCD = DriverStationLCD::GetInstance();

    compressor = new Compressor(2, 2);
    proximityLight = new DigitalOutput(1, 8);
    pstest = new DigitalInput(1, 5);

    jagFR = new CANJaguar(3, CANJaguar::kSpeed);
    jagFL = new CANJaguar(4, CANJaguar::kSpeed);
    jagRR = new CANJaguar(2, CANJaguar::kSpeed);
    jagRL = new CANJaguar(5, CANJaguar::kSpeed);

    handstilt = new CANJaguar(63, CANJaguar::kPercentVbus);

    airsys = new SolenoidBreakout();
    teststick = new Joystick(1);

    mainLights  = new ArduinoControl(7);
    mainLights1 = new ArduinoControl(1);
    mainLights2 = new ArduinoControl(3);
    mainLights3 = new ArduinoControl(5);
    mainLights4 = new ArduinoControl(10);

    j2 = new Jaguar(2);
    j4 = new Jaguar(4);
    j6 = new Jaguar(6);
    j9 = new Jaguar(9);

    // Set up the members
    jagFR->SetExpiration(0.1);
    jagFL->SetExpiration(0.1);
    jagRR->SetExpiration(0.1);
    jagRL->SetExpiration(0.1);

    jagFR->ConfigEncoderCodesPerRev(1024);
    jagFL->ConfigEncoderCodesPerRev(1024);
    jagRR->ConfigEncoderCodesPerRev(1024);
    jagRL->ConfigEncoderCodesPerRev(1024);

    jagFR->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
    jagFL->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
    jagRR->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
    jagRL->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

    jagFR->EnableControl();
    jagFL->EnableControl();
    jagRR->EnableControl();
    jagRL->EnableControl();

    handstilt->SetExpiration(0.1);
    handstilt->EnableControl();
    m_watchdog.SetEnabled(false);
}

RERRobot::~RERRobot(){
    delete compressor;
    delete proximityLight;
    delete pstest;

    delete jagFR;
    delete jagFL;
    delete jagRR;
    delete jagRL;

    delete handstilt;

    delete airsys;
    delete teststick;
}

bool RERRobot::modeChange(mode_type newmode){
    if(mode != newmode){
        switch(mode){
        case disable:
            endDisabled();
            break;
        case test:
            endTest();
            break;
        case teleop:
            endTeleoperated();
            break;
        case autonomous:
            endAutonomous();
            break;
        }
        mode = newmode;
        return true;
    }
    return false;
}

void RERRobot::StartCompetition(){
    printf("$$FRC3499$$ - Starting 2014 Robot Code\n");

    LiveWindow *lw = LiveWindow::GetInstance();
    nUsageReporting::report(nUsageReporting::kResourceType_Framework, nUsageReporting::kFramework_Simple);
    SmartDashboard::init();
    NetworkTable::GetTable("LiveWindow")->GetSubTable("~STATUS~")->PutBoolean("LW Enabled", false);
    lw->SetEnabled(false);

    // Init stuff
    dsLCD->Clear();
    dsLCD->UpdateLCD();

    setupSmartDashboard();

    compressor->Stop();

    while(true){
        // Determine mode
        mode_type newmode;
        if(IsDisabled()){
            newmode = disable;
        } else if(IsTest()){
            newmode = test;
        } else if(IsOperatorControl()){
            newmode = teleop;
        } else if(IsAutonomous()){
            newmode = autonomous;
        } else {
            // Report problem...
            //raise(SIGABRT);
            m_ds->WaitForData();
            return;
        }

        // Run end / init mode functions
        if(mode != newmode){
            if(mode == disable){
                endDisabled();
                m_ds->InDisabled(false);
            } else {
                if(mode == teleop){
                    endTeleoperated();
                    m_ds->InOperatorControl(false);
                    m_ds->WaitForData();
                } else if(mode == autonomous){
                    endAutonomous();
                    m_ds->InAutonomous(false);
                    m_ds->WaitForData();
                } else if(mode == test){
                    endTest();
                    m_ds->InTest(false);
                    m_ds->WaitForData();
                }
            }
            mode = newmode;
            if(newmode == disable){
                dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "DISABLED");
                m_ds->InDisabled(true);
                initDisabled();
            } else {
                dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "ENABLED");
                if(mode == teleop){
                    m_ds->InOperatorControl(true);
                    dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Teleop Mode");
                    initTeleoperated();
                } else if(mode == autonomous){
                    m_ds->InAutonomous(true);
                    dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Autonomous Mode");
                    initAutonomous();
                } else if(mode == test){
                    m_ds->InTest(true);
                    dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Test Mode");
                    initTest();
                }
            }
            dsLCD->UpdateLCD();
        }

        // Run mode loop function
        if(mode == disable){
            modeDisabled();
        } else if(mode == teleop){
            modeTeleoperated();
        } else if(mode == autonomous){
            modeAutonomous();
        } else if(mode == test){
            modeTest();
        }
    }

//    while(true){
//        if(IsOperatorControl()){ // teleop mode
//            m_ds->InOperatorControl(true);
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Teleop Mode");
//            dsLCD->UpdateLCD();
//            if(IsEnabled()){
//                initTeleoperated();
//                while(IsOperatorControl() && IsEnabled())
//                    modeTeleoperated();
//                endTeleoperated();
//            }
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
//            dsLCD->UpdateLCD();
//            m_ds->InOperatorControl(false);
//            while(IsOperatorControl() && IsEnabled()){
//                m_ds->WaitForData();
//            }
//        } else if(IsAutonomous()){ // autonomous mode
//            m_ds->InAutonomous(true);
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Autonomous Mode");
//            dsLCD->UpdateLCD();
//            if(IsEnabled()){
//                initAutonomous();
//                while(IsAutonomous() && IsEnabled())
//                    modeAutonomous();
//                endAutonomous();
//            }
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
//            dsLCD->UpdateLCD();
//            m_ds->InAutonomous(false);
//            while(IsAutonomous() && IsEnabled()){
//                m_ds->WaitForData();
//            }
//        } else if(IsTest()){ // test mode
//            lw->SetEnabled(true);
//            m_ds->InTest(true);
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Test Mode");
//            dsLCD->UpdateLCD();
//            if(IsEnabled()){
//                initTest();
//                while(IsTest() && IsEnabled())
//                    modeTest();
//                endTest();
//            }
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
//            dsLCD->UpdateLCD();
//            m_ds->InTest(false);
//            while(IsTest() && IsEnabled()){
//                m_ds->WaitForData();
//            }
//            lw->SetEnabled(false);
//        } else { // disabled mode
//            m_ds->InDisabled(true);
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Disabled Mode");
//            dsLCD->UpdateLCD();
//            if(IsDisabled()){
//                initDisabled();
//                while(IsDisabled())
//                    modeDisabled();
//                endDisabled();
//            }
//            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
//            dsLCD->UpdateLCD();
//            m_ds->InDisabled(false);
//            while(IsDisabled()){
//                m_ds->WaitForData();
//            }
//        }
//    }
}

// Disabled
void RERRobot::initDisabled(){
    printf("$$FRC3499$$ - Disabled Init\n");
    compressor->Stop();
}
void RERRobot::modeDisabled(){
    Wait(0.005);
}
void RERRobot::endDisabled(){

}

// Teleop
void RERRobot::initTeleoperated(){
    printf("$$FRC3499$$ - Teleop Init\n");
    compressor->Start();
//    SetSafetyEnabled(false); //on a dev board
}
void RERRobot::modeTeleoperated(){
    if(teststick->GetTrigger())
        airsys->shootBall();
    else
        airsys->unShootBall();

    if(teststick->GetRawButton(3))
        airsys->closeArm();
    else
        airsys->openArm();

    if(teststick->GetRawButton(10))
        compressor->SetRelayValue(Relay::kOn);
    else
        compressor->SetRelayValue(Relay::kOff);

    SD_PN("Joystick Y", teststick->GetAxis(Joystick::kYAxis));
    if(abs(teststick->GetAxis(Joystick::kYAxis)) > 0.01){
        handstilt->Set(teststick->GetAxis(Joystick::kYAxis) * 30);
    }

    SD_PN("Proximity Sensor", pstest->Get());
    proximityLight->Set(pstest->Get());

    dsLCD->PrintfLine(DriverStationLCD::kUser_Line4, "IO %d", compressor->GetPressureSwitchValue());

    j2->Set(.6);
    j4->Set(.2);
    j6->Set(-.6);
    j9->Set(-.4);

    mainLights->setFlat();
    mainLights1->setFlat();
    mainLights2->setFlat();
    mainLights3->setFlat();
    mainLights4->setFlat();

    Wait(0.005);
}
void RERRobot::endTeleoperated(){
    compressor->Stop();
    // Turn everything off.
}

// Autonomous
void RERRobot::initAutonomous(){
    printf("$$FRC3499$$ - Autonomous Init\n");
    compressor->Start();
}
void RERRobot::modeAutonomous(){
    Wait(0.005);
}
void RERRobot::endAutonomous(){
    compressor->Stop();
}

// Test
void RERRobot::initTest(){
    printf("$$FRC3499$$ - Test Init\n");
    compressor->Start();
    setupSmartDashboard();
}

void RERRobot::modeTest(){
    switch((int)SD_GN("TEST_MODE")){
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
    }
}
void RERRobot::endTest(){
    compressor->Stop();
}

void RERRobot::setupSmartDashboard(){
    SD_PN("TEST_MODE", 1);

    SD_PN("2P", 0.20);
    SD_PN("2I", 0.001);
    SD_PN("2D", 0.00);

    SD_PN("3P", 0.20);
    SD_PN("3I", 0.001);
    SD_PN("3D", 0.00);

    SD_PN("4P", 0.20);
    SD_PN("4I", 0.001);
    SD_PN("4D", 0.00);

    SD_PN("5P", 0.20);
    SD_PN("5I", 0.001);
    SD_PN("5D", 0.00);

    SD_PN("3 SetSpeed", 50);
    SD_PN("4 SetSpeed", 50);
    SD_PN("2 SetSpeed", 50);
    SD_PN("5 SetSpeed", 50);

    SD_PB("TestEh() == ", IsTest());
    SD_PB("EnabledEh() == ", IsEnabled());

    SD_PN("Proximity Sensor", 1337);
}


START_ROBOT_CLASS(RERRobot) // Off we gooooooo!!!
