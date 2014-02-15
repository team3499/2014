#include "RERRobot.h"
#include "solenoidbreakout.h"

#include <DriverStation.h>
#include <LiveWindow/LiveWindow.h>
#include <NetworkCommunication/UsageReporting.h>
#include <networktables/NetworkTable.h>
#include <Timer.h>
#include <WPILib.h>s

RERRobot::RERRobot(){
    // Initialize all of the members
    dsLCD = DriverStationLCD::GetInstance();

    compressor = new Compressor(2, 2);
    proximityLight = new DigitalOutput(1, 8);
    psensor = new DigitalInput(1, 5);

    cmp = new Relay(1, 5, Relay::kForwardOnly);

    jagFR = new CANJaguar(3, CANJaguar::kSpeed);
    jagFL = new CANJaguar(4, CANJaguar::kSpeed);
    jagRR = new CANJaguar(2, CANJaguar::kSpeed);
    jagRL = new CANJaguar(5, CANJaguar::kSpeed);

    handstilt = new CANJaguar(63, CANJaguar::kPercentVbus);

    airsys = new SolenoidBreakout();
    teststick = new Joystick(1);

    mainLights  = new ArduinoControl(7);

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
}

RERRobot::~RERRobot(){
    delete compressor;
    delete proximityLight;
    delete psensor;

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
    dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "BD: "BUILD_DATE);
    dsLCD->UpdateLCD();
    
    m_watchdog.SetEnabled(true);

    setupSmartDashboard();

    compressor->Stop();

    while(true){
        // Determine mode
    	bool newdisabled;
        mode_type newmode;
        if(IsDisabled()){
        	newdisabled = true;
        } else {
        	newdisabled = false;
        }
        
		if(IsTest()){
			newmode = test;
		} else if(IsOperatorControl()){
			newmode = teleop;
		} else if(IsAutonomous()){
			newmode = autonomous;
		} else {
			m_ds->WaitForData();
		}

        // Run end / init mode functions
        if(disabled != newdisabled){
        	disabled = newdisabled;
        	if(disabled){
                dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "DISABLED");
                m_ds->InDisabled(true);
                modeCode = new ModeDisabled();
                modeCode->start();
        	} else {
                modeCode->end();
                delete modeCode;
                m_ds->InDisabled(false);
        	}
        }
		
        if(mode != newmode){
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
            mode = newmode;
            if(newmode == disable){

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
        
        dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, "%d %d %d %d", IsDisabled(), IsOperatorControl(), IsAutonomous(), IsTest());
        // Update Driver Station LCD
        dsLCD->UpdateLCD();
        
        m_watchdog.Feed();
    }
}

// Disabled
void RERRobot::initDisabled(){

}
void RERRobot::modeDisabled(){
	
}
void RERRobot::endDisabled(){

}

// Teleop
void RERRobot::initTeleoperated(){

}

void RERRobot::modeTeleoperated(){

}
void RERRobot::endTeleoperated(){

}

// Autonomous
void RERRobot::initAutonomous(){

}
void RERRobot::modeAutonomous(){

}
void RERRobot::endAutonomous(){

}

// Test
void RERRobot::initTest(){

}

void RERRobot::modeTest(){

}
void RERRobot::endTest(){

}

void RERRobot::setupSmartDashboard(){
    SD_PN("TEST_MODE", 3);

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
