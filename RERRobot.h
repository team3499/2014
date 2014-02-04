//#include <WPILib.h>
#include <RobotBase.h>
#include <Compressor.h>
#include <Solenoid.h>
#include <CANJaguar.h>
#include <Timer.h>
#include <DigitalOutput.h>
#include <DriverStationLCD.h>

class RERRobot : public RobotBase {
public:
    RERRobot();
    ~RERRobot();
    void StartCompetition(); // basically the entry point
    void init();
    void modeAutonomous();
    void modeTeleoperated();
    void modeTest();
    void modeDisabled();
private:
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
