#include "RERRobot.h"

#include "DriverStation.h"
#include "NetworkCommunication/UsageReporting.h"
#include "Timer.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "networktables/NetworkTable.h"

START_ROBOT_CLASS(RERRobot); // Off we gooooooo!!!

RERRobot::RERRobot(){
	compressor = new Compressor(4, 2);
	compressor->Start();
	valve1 = new Solenoid(1);
	//myRobot.SetExpiration(0.1);
}

RERRobot::~RERRobot(){
	delete compressor;
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
			m_ds->InOperatorControl(true);
			modeTeleoperated();
			m_ds->InOperatorControl(false);
			while (IsOperatorControl() && IsEnabled()){
				m_ds->WaitForData();
			}
		} else if(IsAutonomous()){ // autonomous mode
			m_ds->InAutonomous(true);
			modeAutonomous();
			m_ds->InAutonomous(false);
			while (IsAutonomous() && IsEnabled()){
				m_ds->WaitForData();
			}
		} else if(IsTest()){ // test mode
			lw->SetEnabled(true);
			m_ds->InTest(true);
			modeTest();
			m_ds->InTest(false);
			while (IsTest() && IsEnabled()){
				m_ds->WaitForData();
			}
			lw->SetEnabled(false);
		} else { // disabled mode
			m_ds->InDisabled(true);
			modeDisabled();
			m_ds->InDisabled(false);
			while(IsDisabled()){
				m_ds->WaitForData();
			}
		}
	}
}
