#ifndef MODEAUTONOMOUS_H
#define MODEAUTONOMOUS_H

#include "modebase.h"

class ModeAutonomous : public ModeBase {
public:
	ModeAutonomous(DriverStation *ds);
	~ModeAutonomous();
	
	void begin();
	void run();
	void end();
	
	const char *typeString();
};

#endif
