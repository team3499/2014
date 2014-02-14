//#include <WPILib.h>
#include <RobotBase.h>

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


//#include "tcpconnection.h"
#include "solenoidbreakout.h"
#include "arduino.h"

#ifndef BUILDING
    #include "generated.h"
#else
    #include "gen_out.h"
#endif


// SmartDashboard macros: n = name, x = value
#define SD_PN(n, x) SmartDashboard::PutNumber(n, x)
#define SD_GN(n)    SmartDashboard::GetNumber(n)

#define SD_PB(n, x) SmartDashboard::PutBoolean(n, x)
#define SD_GB(n)    SmartDashboard::GetBoolean(n)

#define SD_PS(n, x) SmartDashboard::PutString(n, x)
#define SD_GS(n)    SmartDashboard::GetString(n)

#define OUT(A) printf("$$FRC3499$$ - " A);

class RERRobot : public RobotBase {
private:
    enum mode_type {
        disable = 1,
        test = 2,
        teleop = 3,
        autonomous = 4
    };

public:
    RERRobot();
    ~RERRobot();
    void StartCompetition(); // The entry point

    //void init();
    bool modeChange(mode_type newmode);

    void initDisabled();
    void modeDisabled();
    void endDisabled();

    void initTest();
    void modeTest();
    void endTest();

    void initTeleoperated();
    void modeTeleoperated();
    void endTeleoperated();

    void initAutonomous();
    void modeAutonomous();
    void endAutonomous();

    void setupSmartDashboard();

private:
    mode_type mode;

    DriverStationLCD *dsLCD;

    Compressor *compressor; // Relay 2, Digital I/O 2
    DigitalOutput *proximityLight; // Digital I/O 8
    DigitalInput *pstest; // Digital I/O 5

    CANJaguar *jagFR; // Jaguar #3
    CANJaguar *jagFL; // Jaguar #4
    CANJaguar *jagRR; // Jaguar #2
    CANJaguar *jagRL; // Jaguar #5

    Relay *cmp; // Relay 5
    
    CANJaguar *handstilt; // For tilting the arm up and down. #63

    SolenoidBreakout *airsys; // Solenoids 1-8

    Joystick *teststick; // Joystick 1

    ArduinoControl *mainLights;
};