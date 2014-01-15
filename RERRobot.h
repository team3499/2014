#include "WPILib.h"

class RERRobot : public RobotBase {
public:
	RERRobot();
	void StartCompetition(); // basically the entry point
	void init();
	void modeAutonomous();
    void modeTeleoperated();
    void modeTest();
	void modeDisabled();
private:
	Compressor *compressor;
}
