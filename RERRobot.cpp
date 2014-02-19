#include "RERRobot.h"
#include "solenoidbreakout.h"
#include "input/jsbase.h"

#include <DriverStation.h>
#include <LiveWindow/LiveWindow.h>
#include <NetworkCommunication/UsageReporting.h>
#include <networktables/NetworkTable.h>
#include <Timer.h>
#include <WPILib.h>

RERRobot::RERRobot(){
	OUT("Initializing 2014 Robot Code");
	
	// Initialize class members
	mode = unknown;
    disabled = false;
    enabledMode = NULL;
    disabledMode = new ModeDisabled(m_ds);
    
    initCommon();
}

void RERRobot::setup(){
    handstilt->SetExpiration(0.1);
    handstilt->EnableControl();
    
    compressor->Stop();
}

RERRobot::~RERRobot(){
	delete disabledMode;
	delete enabledMode;
	destroyCommon();
}

void RERRobot::StartCompetition(){
    OUT("Starting 2014 Robot Code");

    LiveWindow *lw = LiveWindow::GetInstance();
    nUsageReporting::report(nUsageReporting::kResourceType_Framework, nUsageReporting::kFramework_Simple);
    SmartDashboard::init();
    NetworkTable::GetTable("LiveWindow")->GetSubTable("~STATUS~")->PutBoolean("LW Enabled", false);
    lw->SetEnabled(false);

    setup();
    
    // Init output stuff
    dsLCD->Clear();
    dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "BD: "BUILD_DATE);
    dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "INIT");
    dsLCD->UpdateLCD();
    
    setupSmartDashboard();
    
    m_watchdog.SetEnabled(true);
    m_watchdog.SetExpiration(1);
    
    try {
		while(true){
			if(IsDisabled() != disabled){
				disabled = IsDisabled();
				if(disabled){
					if(enabledMode != NULL){
						enabledMode->stop();
					} else {
						OUT("Warning: NULL enabledMode on stop()");
					}
					if(disabledMode != NULL){
						disabledMode->start();
					} else {
						OUT("Warning: NULL disabledMode on start()");
					}
					dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "DISABLED");
				} else {
					if(disabledMode != NULL){
						disabledMode->stop();
					} else {
						OUT("Warning: NULL disabledMode on stop()");
					}
					if(enabledMode != NULL){
						enabledMode->start();
					} else {
						OUT("Warning: NULL enabledMode on start()");
					}
					dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, " ENABLED");
				}
			}
			
			mode_type newmode;
			if(IsTest()){
				newmode = test;
			} else if(IsOperatorControl()){
				newmode = teleop;
			} else if(IsAutonomous()){
				newmode = autonomous;
			} else {
				m_ds->WaitForData();
			}
			
			if(mode != newmode){
				mode = newmode;
				if(enabledMode != NULL){
					delete enabledMode;
					enabledMode = NULL;
				} else {
					OUT("Warning: NULL enabledMode on delete");
				}
				if(mode == teleop){
					enabledMode = new ModeTeleoperated(m_ds);
				} else if(mode == autonomous){
					enabledMode = new ModeAutonomous(m_ds);
				} else if(mode == test){
					enabledMode = new ModeTest(m_ds);
				} else {
					OUT("Warning: mode unknown");
				}
				dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, enabledMode->typeString());
			}
	
			if(disabled){
				if(disabledMode != NULL){
					disabledMode->run();
				} else {
					OUT("Warning: NULL disabledMode on run()");
				}
			} else {
				if(enabledMode != NULL){
					enabledMode->run();
				} else {
					OUT("Warning: NULL enabledMode on run()");
				}
			}
			
			dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, "%d %d", handstilt->GetForwardLimitOK(), handstilt->GetReverseLimitOK());
			
			dsLCD->UpdateLCD();
			m_watchdog.Feed();
		}
    } catch(std::exception e){
    	printf("ERROR: %s\n", e.what());
    }
}

void RERRobot::setupSmartDashboard(){
    SD_PN("TEST_MODE", 4);

    SD_PN("2P", 0.200);
    SD_PN("2I", 0.001);
    SD_PN("2D", 0.000);

    SD_PN("3P", 0.200);
    SD_PN("3I", 0.001);
    SD_PN("3D", 0.000);

    SD_PN("4P", 0.200);
    SD_PN("4I", 0.001);
    SD_PN("4D", 0.000);

    SD_PN("5P", 0.200);
    SD_PN("5I", 0.001);
    SD_PN("5D", 0.000);

    SD_PN("3 SetSpeed", 50);
    SD_PN("4 SetSpeed", 50);
    SD_PN("2 SetSpeed", 50);
    SD_PN("5 SetSpeed", 50);

    SD_PB("TestEh() == ", IsTest());
    SD_PB("EnabledEh() == ", IsEnabled());

    SD_PN("Proximity Sensor", 1337);
    
    SD_PS("JAGLOG_LABEL_OVERRIDE", "");
}


START_ROBOT_CLASS(RERRobot) // Off we gooooooo!!!
