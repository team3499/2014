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

#include "arduino.h"
#include "drivesys.h"
#include "input/operator.h"
#include "solenoidbreakout.h"

#include "const.h"

class OutputCommon {
protected:
    void initCommon();
    void destroyCommon();

    static DriverStationLCD *dsLCD;

    static Operator *op;
    
    static DigitalInput *psensor; // Digital I/O 5
    static ArduinoControl *mainLights;

    static DriveSys *drivesys;
    
    static CANJaguar *handstilt; // For tilting the arm up and down. #63

    static Compressor *compressor; // Relay 2, Digital I/O 2
    static SolenoidBreakout *airsys; // Solenoids 1-8
};

#endif // OUTPUTCOMMON_H
