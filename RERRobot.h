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

    Compressor *compressor;
    Solenoid *valve1;
    DigitalOutput *iotest;

    CANJaguar *jagFR; // Jaguar #3
    CANJaguar *jagFL; // Jaguar #4
    CANJaguar *jagRR; // Jaguar #2
    CANJaguar *jagRL; // Jaguar #5
};
