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
	
    // Initialize all of the members
    dsLCD = DriverStationLCD::GetInstance();

    compressor = new Compressor(2, 2);
    proximityLight = new DigitalOutput(1, 8);
    psensor = new DigitalInput(1, 5);

    cmp = new Relay(1, 5, Relay::kForwardOnly);

//    jagFR = new CANJaguar(3, CANJaguar::kSpeed);
//    jagFL = new CANJaguar(4, CANJaguar::kSpeed);
//    jagRR = new CANJaguar(2, CANJaguar::kSpeed);
//    jagRL = new CANJaguar(5, CANJaguar::kSpeed);
    jagFR = new CANJaguar(3, CANJaguar::kPercentVbus);
    jagFL = new CANJaguar(4, CANJaguar::kPercentVbus);
    jagRR = new CANJaguar(2, CANJaguar::kPercentVbus);
    jagRL = new CANJaguar(5, CANJaguar::kPercentVbus);

    handstilt = new CANJaguar(63, CANJaguar::kPercentVbus);

    airsys = new SolenoidBreakout();
    teststick = new Joystick(3);

    mainLights  = new ArduinoControl(7);

    // Set up the members
    jagFR->SetExpiration(0.1);
    jagFL->SetExpiration(0.1);
    jagRR->SetExpiration(0.1);
    jagRL->SetExpiration(0.1);

//    jagFR->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
//    jagFL->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
//    jagRR->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
//    jagRL->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
//    
//    jagFR->ConfigEncoderCodesPerRev(1024);
//    jagFL->ConfigEncoderCodesPerRev(1024);
//    jagRR->ConfigEncoderCodesPerRev(1024);
//    jagRL->ConfigEncoderCodesPerRev(1024);

    jagFR->EnableControl();
    jagFL->EnableControl();
    jagRR->EnableControl();
    jagRL->EnableControl();

    handstilt->SetExpiration(0.1);
    handstilt->EnableControl();
    
    op = new Operator();
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
    //delete teststick;
}

void RERRobot::StartCompetition(){
    OUT("Starting 2014 Robot Code");

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
    m_watchdog.SetExpiration(1);

    setupSmartDashboard();

    compressor->Stop();
    
    disabled = false;
    
    try {
        	
#if SUICIDAL == 1
    	enabledMode = new ModeDisabled(m_ds);
    	
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
                m_ds->WaitForData();
            }

            // Run end / init mode functions
            if(mode != newmode){
                if(mode == disable){
                	enabledMode->end();
                	delete enabledMode;
                } else {
                    if(mode == teleop){
                    	enabledMode->end();
                    	delete enabledMode;
                        m_ds->WaitForData();
                    } else if(mode == autonomous){
                    	enabledMode->end();
                    	delete enabledMode;
                        m_ds->WaitForData();
                    } else if(mode == test){
                    	enabledMode->end();
                    	delete enabledMode;
                        m_ds->WaitForData();
                    }
                }
                mode = newmode;
                if(newmode == disable){
                    dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "DISABLED");
                    enabledMode = new ModeDisabled(m_ds);
                    enabledMode->init();
                } else {
                    dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "ENABLED");
                    if(mode == teleop){
                        dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Teleop Mode");
                        enabledMode = new ModeTeleoperated(m_ds);
                        enabledMode->init();
                    } else if(mode == autonomous){
                        dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Autonomous Mode");
                        enabledMode = new ModeAutonomous(m_ds);
                        enabledMode->init();
                    } else if(mode == test){
                        dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Test Mode");
                        enabledMode = new ModeTest(m_ds);
                        enabledMode->init();
                    }
                }
            }

            // Run mode loop function
            enabledMode->run();
            
            // Update Driver Station LCD
            dsLCD->UpdateLCD();
        }
#elif SUICIDAL == 2
        enabledMode = new ModeTeleoperated(m_ds);
        disabledMode = new ModeDisabled(m_ds);
        
		while(true){
			if(IsDisabled() != disabled){
				disabled = IsDisabled();
				if(disabled){
					enabledMode->stop();
					dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "DISABLED");
					disabledMode = new ModeDisabled(m_ds);
					disabledMode->start();
				} else {
					disabledMode->stop();
					delete disabledMode;
					enabledMode->start();
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
				//enabledMode->stop();
				delete enabledMode;
				
				mode = newmode;
	
				dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "ENABLED");
				if(mode == teleop){
					enabledMode = new ModeTeleoperated(m_ds);
					dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Teleop Mode");
				} else if(mode == autonomous){
					enabledMode = new ModeAutonomous(m_ds);
					dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Autonomous Mode");
				} else if(mode == test){
					enabledMode = new ModeTest(m_ds);
					dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Test Mode");
				}
				
				//enabledMode->start();
			}
	
			if(disabled){
				disabledMode->run();
			} else {
				enabledMode->run();
			}
			
			dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, "%d %d %d %d", IsDisabled(), IsOperatorControl(), IsAutonomous(), IsTest());
			
			// Update Driver Station LCD
			dsLCD->UpdateLCD();
			
			m_watchdog.Feed();
		}
#else
	#error Enter a valid SUICIDAL level
#endif
    
    } catch(std::exception e){
    	printf("ERROR: %s\n", e.what());
    }
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
