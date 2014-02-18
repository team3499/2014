#ifndef OUTPUTCOMMON_H
#define OUTPUTCOMMON_H

#include <CANJaguar.h>
#include <Compressor.h>
#include <DigitalOutput.h>
#include <DigitalInput.h>
#include <DriverStation.h>
#include <DriverStationLCD.h>
#include <Jaguar.h>

#include <Joystick.h>
#include <PWM.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Solenoid.h>

#include "solenoidbreakout.h"
#include "arduino.h"
#include "input/operator.h"
#include "tcpconnection.h"

// SmartDashboard macros: n = name, x = value
#define SD_PN(n, x) SmartDashboard::PutNumber(n, x)
#define SD_GN(n)    SmartDashboard::GetNumber(n)

#define SD_PB(n, x) SmartDashboard::PutBoolean(n, x)
#define SD_GB(n)    SmartDashboard::GetBoolean(n)

#define SD_PS(n, x) SmartDashboard::PutString(n, x)
#define SD_GS(n)    SmartDashboard::GetString(n)

#define OUT(A) printf("$$FRC3499$$ - " A "\n"); \
	           fflush(stdout);

class OutputCommon {
protected:
	void initCommon();
	void destroyCommon();
	
    static DriverStationLCD *dsLCD;
    static TCPConnection *tcpc;

    static Operator *op;
    
    static DigitalInput *psensor; // Digital I/O 5
    static ArduinoControl *mainLights;

    static CANJaguar *jagFR; // Jaguar #3
    static CANJaguar *jagFL; // Jaguar #4
    static CANJaguar *jagRR; // Jaguar #2
    static CANJaguar *jagRL; // Jaguar #5
    
    static CANJaguar *handstilt; // For tilting the arm up and down. #63

    static Compressor *compressor; // Relay 2, Digital I/O 2
    static SolenoidBreakout *airsys; // Solenoids 1-8
    //static Relay *auxpwoer; // Relay 5
};

#endif
