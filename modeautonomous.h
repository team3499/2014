#ifndef MODEAUTONOMOUS_H
#define MODEAUTONOMOUS_H

#include "modebase.h"
#include "jaglog.h"

#include <Timer.h>

class ModeAutonomous : public ModeBase {
public:
	ModeAutonomous(DriverStation *ds);
	~ModeAutonomous();
	
	void begin();
	void run();
	void end();
	
	const char *typeString();
private:
	int step;
	Timer *drivetime;

};

#endif
