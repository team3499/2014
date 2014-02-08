#include "RERRobot.h"
#include <DriverStation.h>
#include <NetworkCommunication/UsageReporting.h>
#include <Timer.h>
#include <LiveWindow/LiveWindow.h>
#include <networktables/NetworkTable.h>
#include <csignal>
#include <unistd.h>

RERRobot::RERRobot(){
    // Initialize all of the members
    dsLCD = DriverStationLCD::GetInstance();

    compressor = new Compressor(2, 2);
    iotest = new DigitalOutput(1, 8);
    pstest = new DigitalInput(1, 5);

    jagFR = new CANJaguar(3, CANJaguar::kSpeed);
    jagFL = new CANJaguar(4, CANJaguar::kSpeed);
    jagRR = new CANJaguar(2, CANJaguar::kSpeed);
    jagRL = new CANJaguar(5, CANJaguar::kSpeed);

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

    airsys = new SolenoidBreakout();
    teststick = new Joystick(1);
}

RERRobot::~RERRobot(){
    delete compressor;
    delete iotest;
    delete pstest;

    delete jagFR;
    delete jagFL;
    delete jagRR;
    delete jagRL;

    delete airsys;
    delete teststick;
}

void RERRobot::StartCompetition(){
    LiveWindow *lw = LiveWindow::GetInstance();
    nUsageReporting::report(nUsageReporting::kResourceType_Framework, nUsageReporting::kFramework_Simple);
    SmartDashboard::init();
    NetworkTable::GetTable("LiveWindow")->GetSubTable("~STATUS~")->PutBoolean("LW Enabled", false);
    lw->SetEnabled(false);

    // Init stuff
    dsLCD->Clear();
    dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "BD: "BUILD_DATE);
    dsLCD->UpdateLCD();

    setupSmartDashboard();

    compressor->Stop();

    while(true){
        if(IsOperatorControl()){ // teleop mode
            m_ds->InOperatorControl(true);
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Teleop Mode");
            dsLCD->UpdateLCD();
            initTeleoperated();
            while(IsOperatorControl() && IsEnabled())
                modeTeleoperated();
            endTeleoperated();
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
            dsLCD->UpdateLCD();
            m_ds->InOperatorControl(false);
            while(IsOperatorControl() && IsEnabled()){
                m_ds->WaitForData();
            }
        } else if(IsAutonomous()){ // autonomous mode
            m_ds->InAutonomous(true);
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Autonomous Mode");
            dsLCD->UpdateLCD();
            initAutonomous();
            while(IsAutonomous() && IsEnabled())
                modeAutonomous();
            endAutonomous();
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
            dsLCD->UpdateLCD();
            m_ds->InAutonomous(false);
            while(IsAutonomous() && IsEnabled()){
                m_ds->WaitForData();
            }
        } else if(IsTest()){ // test mode
            lw->SetEnabled(true);
            m_ds->InTest(true);
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Test Mode");
            dsLCD->UpdateLCD();
            initTest();
            while(IsTest() && IsEnabled())
                modeTest();
            endTest();
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
            dsLCD->UpdateLCD();
            m_ds->InTest(false);
            while(IsTest() && IsEnabled()){
                m_ds->WaitForData();
            }
            lw->SetEnabled(false);
        } else { // disabled mode
            m_ds->InDisabled(true);
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Disabled Mode");
            dsLCD->UpdateLCD();
            initDisabled();
            while(IsDisabled())
                modeDisabled();
            endDisabled();
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Unknown Mode");
            dsLCD->UpdateLCD();
            m_ds->InDisabled(false);
            while(IsDisabled()){
                m_ds->WaitForData();
            }
        }
    }
}

// Disabled
void RERRobot::initDisabled(){
    compressor->Stop();
}
void RERRobot::modeDisabled(){
    Wait(0.005);
}
void RERRobot::endDisabled(){

}

// Teleop
void RERRobot::initTeleoperated(){
    compressor->Start();
    //SetSafetyEnabled(false); //on a dev board
}
void RERRobot::modeTeleoperated(){
    if(teststick->GetTrigger())
        airsys->shootBall();
    else
        airsys->unShootBall();

    SD_PN("Proximity Sensor", pstest->Get());

    Wait(0.005);
}
void RERRobot::endTeleoperated(){
    compressor->Stop();
}

// Autonomous
void RERRobot::initAutonomous(){
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
    compressor->Start();

//    SD_PB("Testing i eh", false);
//    SD_PN("Testing i eh?", 0.0);

//    SD_PN("IsOperatorControl eh?", IsOperatorControl());
//    SD_PN("IsEnabled eh?", IsEnabled());
}
void RERRobot::modeTest(){
    switch((int)SD_GN("TEST_MODE")){
    case 1:
        SD_PB("LED eh ", false);
        iotest->Set(0);
        sleep(1);
        SD_PS("String! ", "String 1");
        SD_PB("LED eh ", true);
        iotest->Set(1);
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
