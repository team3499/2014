#include "RERRobot.h"
#include "DriverStation.h"
#include "NetworkCommunication/UsageReporting.h"
#include "Timer.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "networktables/NetworkTable.h"

RERRobot::RERRobot(){
    dsLCD = DriverStationLCD::GetInstance();

    compressor = new Compressor(2, 2);
    valve1 = new Solenoid(1);
    iotest = new DigitalOutput(1, 8);

    jagFR = new CANJaguar(3, CANJaguar::kSpeed);
    jagFL = new CANJaguar(4, CANJaguar::kSpeed);
    jagRR = new CANJaguar(2, CANJaguar::kSpeed);
    jagRL = new CANJaguar(5, CANJaguar::kSpeed);

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

    relayTest = new Relay(3);
}

RERRobot::~RERRobot(){
    delete compressor;
    delete valve1;

    delete jagFR;
    delete jagFL;
    delete jagRR;
    delete jagRL;
}

void RERRobot::StartCompetition(){
    LiveWindow *lw = LiveWindow::GetInstance();
    nUsageReporting::report(nUsageReporting::kResourceType_Framework, nUsageReporting::kFramework_Simple);
    SmartDashboard::init();
    NetworkTable::GetTable("LiveWindow")->GetSubTable("~STATUS~")->PutBoolean("LW Enabled", false);
    lw->SetEnabled(false);

    init();

    while(true){
        if(IsOperatorControl()){ // teleop mode
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Teleop Mode");
            dsLCD->UpdateLCD();
            m_ds->InOperatorControl(true);
            modeTeleoperated();
            m_ds->InOperatorControl(false);
            while(IsOperatorControl() && IsEnabled()){
                m_ds->WaitForData();
            }
        } else if(IsAutonomous()){ // autonomous mode
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Autonomous Mode");
            dsLCD->UpdateLCD();
            m_ds->InAutonomous(true);
            modeAutonomous();
            m_ds->InAutonomous(false);
            while(IsAutonomous() && IsEnabled()){
                m_ds->WaitForData();
            }
        } else if(IsTest()){ // test mode
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Test Mode");
            dsLCD->UpdateLCD();
            lw->SetEnabled(true);
            m_ds->InTest(true);
            modeTest();
            m_ds->InTest(false);
            while(IsTest() && IsEnabled()){
                m_ds->WaitForData();
            }
            lw->SetEnabled(false);
        } else { // disabled mode
            dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Disabled Mode");
            dsLCD->UpdateLCD();
            m_ds->InDisabled(true);
            modeDisabled();
            m_ds->InDisabled(false);
            while(IsDisabled()){
                m_ds->WaitForData();
            }
        }
    }
}

START_ROBOT_CLASS(RERRobot) // Off we gooooooo!!!
