//#include <WPILib.h>
#include <RobotBase.h>
#include <Compressor.h>
#include <Solenoid.h>
#include <CANJaguar.h>
#include <Timer.h>
#include <DigitalOutput.h>
#include <DriverStationLCD.h>
#include <SmartDashboard/SmartDashboard.h>
#include <DriverStation.h>

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
    void StartCompetition(); // basically the entry point

    void init();
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

private:
    mode_type mode;

    DriverStationLCD *dsLCD;

    Compressor *compressor; // Relay port 2, digital I/O 2
    Solenoid *valve1; // Solenoid port 1
    DigitalOutput *iotest; // Digital I/O port 8

    CANJaguar *jagFR; // Jaguar #3
    CANJaguar *jagFL; // Jaguar #4
    CANJaguar *jagRR; // Jaguar #2
    CANJaguar *jagRL; // Jaguar #5

    Relay *relayTest; // Relay port 3
};
