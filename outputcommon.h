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

// SmartDashboard macros: n = name, x = value
#define SD_PN(n, x) SmartDashboard::PutNumber(n, x)
#define SD_GN(n)    SmartDashboard::GetNumber(n)

#define SD_PB(n, x) SmartDashboard::PutBoolean(n, x)
#define SD_GB(n)    SmartDashboard::GetBoolean(n)

#define SD_PS(n, x) SmartDashboard::PutString(n, x)
#define SD_GS(n)    SmartDashboard::GetString(n)

#define OUT(A) printf("$$FRC3499$$ - " A "\n");

class OutputCommon {
protected:
    static DriverStationLCD *dsLCD;

    static Compressor *compressor; // Relay 2, Digital I/O 2
    static DigitalOutput *proximityLight; // Digital I/O 8
    static DigitalInput *psensor; // Digital I/O 5

    static CANJaguar *jagFR; // Jaguar #3
    static CANJaguar *jagFL; // Jaguar #4
    static CANJaguar *jagRR; // Jaguar #2
    static CANJaguar *jagRL; // Jaguar #5

    static Relay *cmp; // Relay 5
    
    static CANJaguar *handstilt; // For tilting the arm up and down. #63

    static SolenoidBreakout *airsys; // Solenoids 1-8

    static Joystick *teststick; // Joystick 1
    static Operator *op;

    static ArduinoControl *mainLights;
};

#endif
